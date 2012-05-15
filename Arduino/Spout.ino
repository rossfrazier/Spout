#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "Pour.h"
#include "Drink.h"

// MAC ADDRESS
static uint8_t mac[6] = { 0x90, 0xA2, 0xDA, 0x00, 0xC2, 0xB3 };

// IP ADDRESS
static uint8_t ip[4] = { 192, 168, 1, 10 };

/* all URLs on this server will start with "/spout" because of how we
 * define the PREFIX value. */
#define PREFIX "/spout"
WebServer webserver(PREFIX, 80);  //second param is port value

#define MAX_INGREDIENTS 8
void newDrinkCmd(WebServer &server, WebServer::ConnectionType type, char *, bool) {
    static const byte bufferSize = 4;
    if (type == WebServer::POST) {
        bool hasMoreParams;
        byte poursCount = 0;
        
        /* potentially a problem: this is a dynamic array of arbitrary size.
         * it won't be completely filled, but the poursCount should keep the
         * system from accessing things that are actually out of bounds */
        Pour * allPours = new Pour [MAX_INGREDIENTS];
        
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
             * example: name=p2, value=3 is first pour, from bottle 2, for 3 sec. */
            
            if (strncmp(name, "p", 1) == 0) {
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
                //deallocate memory for objects
                delete[] allPours;
                delete drink;
                allPours = NULL;
                drink = NULL;

                server.httpSuccess();
            }
        }
        return;
    }
}

void setup() {
    //setup pins as input/output; sizeOf works for counting elements because it's an array of bytes
    for (byte i = 0; i < sizeOf(Drink::valveTransistorPins[]); i++) {
        pinMode(Drink::valveTransistorPins[i], OUTPUT);
    }

    //initialize the ethernet shield 
    Ethernet.begin(mac);
    Serial.begin(9600);
    Serial.println("program initialized");
    
    /* register our webserver default command (activated with the request of
     * http://x.x.x.x/spout */
    webserver.setDefaultCommand(&newDrinkCmd);
    
    // start the server to wait for connections
    webserver.begin();
}

void loop() {
    // process incoming connections one at a time forever
    webserver.processConnection();
}
