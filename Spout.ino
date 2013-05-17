// Arduino initialization code

/* Commands: (all are POST)
 * http://x.x.x.x/spout 
 * [{key:"b2", value: 5}, {key:"b1", value: 2}]
 * Pour a drink with two ingredients.  The first ingredient is from bottle #3,
 * pouring for 5 seconds. The second ingredient is from bottle #2, pouring for 2
 * seconds. Bottle numbers are zero-indexed (the first bottle is bottle #0)
 * 
 * http://x.x.x.x/spout/test
 * [{key:"p", value: 5}, {key:"c", value: 2}]
 * Run the pump for 5 seconds, and run the conveyer motor for 2 seconds. */

//send null file for favicon in responses
#define WEBDUINO_FAVICON_DATA ""
#define WEBDUINO_SERIAL_DEBUGGING 1

#include "SPI.h"
#include "Ethernet.h"
#include "SD.h"
#include "WebServer.h"
#include "Machine.h"
#include "Pour.h"
#include "Drink.h"

/* all URLs on this server will start with "/spout" because of how we
 * define the PREFIX value. */
#define PREFIX "/spout"
WebServer webserver(PREFIX, 80);  //second param is port value

void indexCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  if (type != WebServer::GET) {
    server.httpFail();
    return;
  }

  File dataFile = SD.open("index.html");
  if (dataFile) {
    while (dataFile.available()) {
      server.httpSuccess();
      server.print(dataFile.read());
    }
    dataFile.close()
  }
  else {
    server.httpFail();
    P(failureMessage) = "HTML file didn't load from SD card";
    server.printP(failureMessage);
  }
}

#define BUFFER_SIZE 16

//default command: takes an array of drink ingredients
void newDrinkCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  static const byte bufferSize = BUFFER_SIZE;
  if (type == WebServer::POST) {
    bool hasMoreParams;
    byte poursCount = 0;
    
    /* this is an array of arbitrary size. it may not be completely filled, 
     * but the poursCount should keep the system from accessing things that are actually out of bounds */
    Pour allPours [Machine::bottleCount()];
    
    char name[bufferSize], value[bufferSize];
    do {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those buffers. */
      hasMoreParams = server.readPOSTparam(name, bufferSize, value, bufferSize);
      
      /* b as the first character in the POST request name signifies a bottle
       * the second character in the name is the bottle number the value is the pouring time (in seconds).
       * example: name=b2, value=3 is first pour, from bottle #3, for 3 sec. */
      
      if (strncmp(name, "b", 1) == 0) {
        byte bottle = name[1]-'0'; //converts ascii char (2nd character) to byte
        int secondsPouring = strtoul(value, NULL, 10);
        allPours[poursCount].setBottleAndSeconds(bottle, secondsPouring);
        poursCount++;
      }
    } while (hasMoreParams); //keeps adding Pour objects to the array until it runs out of params
    
    if (poursCount > 0) {
      Drink drink(allPours, poursCount);
      drink.beginPouring();
      if (drink.isComplete()) {
        server.httpSuccess();
      }
      else { //validation error
        server.httpFail();
        P(failureMessage)= "Fail: Validation error.";
        server.printP(failureMessage);
      }
    }

    return;
  }
}

#define VALUELEN 32

void loadImageCmd(WebServer &server, WebServer::ConnectionType type, char** url_path, char *url_tail, bool tail_complete) {
  if (!tail_complete) {
    server.httpFail();
    return;
  }

  URLPARAM_RESULT paramResult;
  char name[VALUELEN];
  char value[VALUELEN];

  while (strlen(url_tail)) {
    paramResult = server.nextURLparam(&url_tail, name, NAMELEN, value, VALUELEN);
    if (paramResult == URLPARAM_EOS) {
      File imageFile = SD.open(name, FILE_READ);
      if (imageFile) {
        server.httpSuccess("image/png");
        int16_t imageByte;
        while ((c = imageFile.read()) >= 0) {
          server.print((char)imageByte);
        }
        imageFile.close();
      }
      else {
        server.httpFail();
      }    
    }
  } 
}

void initializeSDCardReader() {
  Serial.println("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);
  // see if the card is present and can be initialized:
  const int chipSelect = 4;
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void setup() {
  //SERIAL SETUP
  Serial.begin(9600);
  Serial.println("Spout initialized");

  initializeSDCardReader();
  
  //PIN SETUP
  Machine::setPins();

  //ETHERNET SETUP
  static uint8_t mac[6] = { 0x90, 0xA2, 0xDA, 0x00, 0xA9, 0xFE };
  static IPAddress ip_address(192,168,1,30);
  Ethernet.begin(mac, ip_address);
  Serial.println("Ethernet active");
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  
  //WEB ROUTES
  /* register our webserver default command (activated with the request of
   * http://x.x.x.x/spout */
  webserver.setDefaultCommand(&indexCmd);
  webserver.addCommand("img", &loadImageCmd);
  webserver.addCommand("pour", &newDrinkCmd);

  // start the server to wait for connections
  webserver.begin();
}

void loop() {
  // process incoming connections one at a time forever
  webserver.processConnection();
}
