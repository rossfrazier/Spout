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
#define WEBDUINO_SERIAL_DEBUGGING 2

#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "Machine.h"
#include "Pour.h"
#include "Drink.h"

/* all URLs on this server will start with "/spout" because of how we
 * define the PREFIX value. */
#define PREFIX "/spout"
WebServer webserver(PREFIX, 80);  //second param is port value

//Machine machine;

#define BUFFER_SIZE 16

//default command: takes an array of drink ingredients
void newDrinkCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  static const byte bufferSize = BUFFER_SIZE;
  if (type == WebServer::POST) {
    bool hasMoreParams;
    byte poursCount = 0;
    
    /* potentially a problem: this is an array of arbitrary size.
     * it may not be completely filled, but the poursCount should keep the
     * system from accessing things that are actually out of bounds */
    Pour allPours [Machine::bottleCount()];
    
    //buffers originally lengths of 16, but 8 should be more than fine.
    char name[bufferSize], value[bufferSize];
    do {
      /* readPOSTparam returns false when there are no more parameters
       * to read from the input.  We pass in buffers for it to store
       * the name and value strings along with the length of those
       * buffers. */
      hasMoreParams = server.readPOSTparam(name, bufferSize, value, bufferSize);
      
      /* b as the first character in the POST request name signifies a bottle
       * the second character in the name is the bottle number
       * the value is the pouring time (in seconds).
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

void setup() {
  //SERIAL SETUP
  Serial.begin(9600);
  Serial.println("Spout initialized");
  
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
  webserver.setDefaultCommand(&newDrinkCmd);

  // start the server to wait for connections
  webserver.begin();
}

void loop() {
  // process incoming connections one at a time forever
  webserver.processConnection();
  //machine.isCupPresent();
}
