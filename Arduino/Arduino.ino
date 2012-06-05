// Arduino initialization code

/* Commands: (all are POST)
 * http://x.x.x.x/spout 
 * [{key:"b2", value: 5}, {key:"p1", value: 2}]
 * Pour a drink with two ingredients.  The first ingredient is from bottle #2,
 * pouring for 5 seconds. The second ingredient is from bottle #1, pouring for 2
 * seconds. 
 * 
 * http://x.x.x.x/spout/test
 * [{key:"p", value: 5}, {key:"c", value: 2}]
 * Run the pump for 5 seconds, and run the conveyer motor for 2 seconds. */

//send null file for favicon in responses
#define WEBDUINO_FAVICON_DATA ""

#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "Pour.h"
#include "Drink.h"
#include "Test.h"

// MAC ADDRESS
static uint8_t mac[6] = { 0x90, 0xA2, 0xDA, 0x00, 0xC2, 0xB3 };

// IP ADDRESS
//should test whether this is really necessary
static uint8_t ip[4] = { 192, 168, 1, 10 };

/* all URLs on this server will start with "/spout" because of how we
 * define the PREFIX value. */
#define PREFIX "/spout"
WebServer webserver(PREFIX, 80);  //second param is port value

#define BUFFER_SIZE 2

//default command: takes an array of drink ingredients
void newDrinkCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
    static const byte bufferSize = BUFFER_SIZE;
    if (type == WebServer::POST) {
        bool hasMoreParams;
        byte poursCount = 0;
        
        /* potentially a problem: this is a dynamic array of arbitrary size.
         * it won't be completely filled, but the poursCount should keep the
         * system from accessing things that are actually out of bounds */
        Pour * allPours = new Pour [Drink::numberOfBottles()];
        
        //buffers originally lengths of 16, but 8 should be more than fine.
        char name[bufferSize], value[bufferSize];
        do {
            /* readPOSTparam returns false when there are no more parameters
             * to read from the input.  We pass in buffers for it to store
             * the name and value strings along with the length of those
             * buffers. */
            hasMoreParams = server.readPOSTparam(name, bufferSize, value, bufferSize);
            
            /* p as the first character in the POST request name signifies a pour
             * the second character in the name is the bottle number
             * the value is the pouring time (in seconds).
             * example: name=b2, value=3 is first pour, from bottle 2, for 3 sec. */
            
            if (strncmp(name, "b", 1) == 0) {
                byte bottle = name[1]-'0';
                int secondsPouring = strtoul(value, NULL, 10);
                allPours[poursCount].setBottleAndSeconds(bottle, secondsPouring);
                poursCount++;
            }
        } while (hasMoreParams); //keeps adding Pour objects to the array until it runs out of params
        
        if (poursCount > 0) {
            Drink * drink = new Drink(allPours, poursCount);
            drink -> beginPouring();
            if (drink -> isComplete()) {
                server.httpSuccess();
            }
            else { //validation error
                server.httpSuccess();
                P(failureMessage)= "Fail: You probably asked for a bottle that doesn't exist.";
                server.printP(failureMessage);
            }
            //deallocate memory for objects
            delete[] allPours;
            delete drink;
            allPours = NULL;
            drink = NULL;
        }

        return;
    }
}

//testing methods: can be used to arbitrarily control air pumps, conveyers, etc.
//reads POST params in the same way as in the default command.
void testCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
    static const byte bufferSize = BUFFER_SIZE;
    if (type == WebServer::POST) {
        bool hasMoreParams;
        char name[bufferSize], value[bufferSize];

        do {
            hasMoreParams = server.readPOSTparam(name, bufferSize, value, bufferSize);
            int secondsRunning = strtoul(value, NULL, 10);
            //p prefix on post param name means the user wants to run the pump
            if (strncmp(name, "p", 1) == 0) {
                Test::runPumpForTime(secondsRunning);
            }
            //c prefix on post param name means the user wants to run the conveyer motor
            else if (strncmp(name, "c", 1) == 0) {
                Test::runConveyerForTime(secondsRunning);
            }
            else {
                server.httpFail();
                return;
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
  
    //setup pins as input/output; 
    //pinMode(Test::pumpTransistor, OUTPUT);
    for (byte i = 0; i < Drink::numberOfBottles(); i++) {
        pinMode(Drink::valveTransistorPins[i], OUTPUT);
    }
    
    Serial.println("pin mode selection complete");

    //initialize the ethernet shield 
    Ethernet.begin(mac);
    
    Serial.println("still here!");
    
    //web routes
    /* register our webserver default command (activated with the request of
     * http://x.x.x.x/spout */
    webserver.setDefaultCommand(&newDrinkCmd);
    //test commands use POST url of http://x.x.x.x/spout/test
    webserver.addCommand("/test",&testCmd);
    
    // start the server to wait for connections
    webserver.begin();
}

void loop() {
    // process incoming connections one at a time forever
    webserver.processConnection();
}
