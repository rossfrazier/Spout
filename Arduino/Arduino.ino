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

#define BUFFER_SIZE 8

//default command: takes an array of drink ingredients
void newDrinkCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  static const byte bufferSize = BUFFER_SIZE;
  if (type == WebServer::POST) {
    bool hasMoreParams;
    byte poursCount = 0;
    
    /* potentially a problem: this is a dynamic array of arbitrary size.
     * it won't be completely filled, but the poursCount should keep the
     * system from accessing things that are actually out of bounds */
    Pour * allPours = new Pour [Machine::bottleCount()];
    
    //buffers originally lengths of 16, but 4 should be more than fine.
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
        byte bottle = name[1]-'0'; //converts ascii char to byte
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
        P(failureMessage)= "Fail: You probably asked for a bottle that doesn't exist.";
        server.printP(failureMessage);
      }
      //deallocate memory for objects
      delete[] allPours;
      allPours = NULL;
    }

    return;
  }
}

//testing methods: can be used to arbitrarily control air pumps, conveyers, etc.
//reads POST params in the same way as in the default command.
void testCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
  Serial.println("test command!");
  static const byte bufferSize = BUFFER_SIZE;
  if (type == WebServer::POST) {
    bool hasMoreParams;
    char name[bufferSize], value[bufferSize];
    Machine machine;

    do {
      hasMoreParams = server.readPOSTparam(name, bufferSize, value, bufferSize);
      int millisecondsRunning = atoi(value);

      //p prefix on post param name means the user wants to run the pump
      if (strncmp(name, "p", 1) == 0) {
        machine.runPumpForTime(millisecondsRunning);
      }
      //c prefix on post param name means the user wants to run the conveyer motor
      else if (strncmp(name, "c", 1) == 0) {
        machine.runConveyerForTime(millisecondsRunning);
      }
    } while (hasMoreParams);

    server.httpSuccess();
  }
  else {
    server.httpFail();
  }

  return;
}

void setup() {
  Serial.begin(9600);
  Serial.println("program initialized");
  
  Machine::setPins();

  //initialize the ethernet shield with mac address
  static uint8_t mac[6] = { 0x90, 0xA2, 0xDA, 0x00, 0xA9, 0xFE };
  Ethernet.begin(mac);
  Serial.println("ethernet active");
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
  
  //web routes
  /* register our webserver default command (activated with the request of
   * http://x.x.x.x/spout */
  webserver.setDefaultCommand(&newDrinkCmd);
  //test commands use POST url of http://x.x.x.x/spout/test
  webserver.addCommand("test",&testCmd);
  
  // start the server to wait for connections
  webserver.begin();
}

void loop() {
  // process incoming connections one at a time forever
  webserver.processConnection();
}
