#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>
#include <PulseSensorPlayground.h>
#include <Arduino.h>

#include "HomeMenu.h"
#include "StartingAnimation.h"  // Only include the header file, not .cpp
#include "UserMenus.h"
#include "UserRegistration.h"
#include "BPM.h"
#include "FreeRun.h"
#include "WifiConnect.h"
#include "UserStats.h"

TFT_eSPI tft = TFT_eSPI();
XPT2046_Touchscreen touch(TOUCH_CS);

const int wheelRadius = 34;
const int rotationSpeed = 10;
const int numSpokes = 8;

int mappedX, mappedY = 0;
int menu = 0;
int tab = 1;
bool state = false;
bool shift = true;
String temp = "";

const int pulsePin = A0;      // Analog pin for Pulse Sensor
// Replace with your Wi-Fi credentials
char* ssid = "";
char* Wifipassword = "";
bool connect = false;
int currentUser = -1;


void setup() {
  Serial.begin(115200);
  initStartup();  // Call the initialization function for the startup animation
}

// void Position(){
//         TS_Point p = touch.getPoint();

//     // Map raw touch values to the screen size
//     mappedX = map(p.x, 200, 4000, 0, tft.width());
//     mappedY = map(p.y, 200, 4000, 0, tft.height());
// }

void Position() {
    int stableThreshold = 5; // Maximum allowed change between stable readings
    int numSamples = 10;     // Number of samples to collect
    int debounceDelay = 10;  // Delay between samples in milliseconds
    
    int tempX, tempY;
    int lastMappedX = -1;
    int stableCount = 0;

    // Continuously sample until values stabilize
    for (int i = 0; i < numSamples; i++) {
        TS_Point p = touch.getPoint();

        // Map raw touch values to the screen size
        tempX = map(p.x, 200, 4000, 0, tft.width());
        tempY = map(p.y, 200, 4000, 0, tft.height());

        // Check if X has stabilized
        if (lastMappedX == -1 || abs(tempX - lastMappedX) <= stableThreshold) {
            stableCount++;
        } else {
            stableCount = 0; // Reset stable count if value fluctuates
        }

        lastMappedX = tempX;

        // If X is stable for enough readings, break early
        if (stableCount >= 3) {
            break;
        }

        delay(debounceDelay);
    }

    // Final stabilized values
    mappedX = tempX;
    mappedY = tempY;
}


//Case 0 is startup animation, Case 1 is main Menu, Case 5 is for the New User setup
void loop() {
     switch (menu) {
      case 0: //Starting Animation
        displayStartup();
        break;
      case 1: //First Menu Screen (New User/Existing User/Guest/Settings)
        displayHomeMenu();
        break;
      case 2:
        MenuSetup(); //Setup Wifi settings 
        displayMenuSelect();
        break;
      case 3: //Guest
        menu = 6;
        currentUser = -1;
        break;
      case 4: //Existing User
        MenuSetup();
        displayMenuSelect();
        break;
      case 5:
        MenuSetup(); //New User
        displayMenuSelect();
        break;
      case 6: //Second Menu Screen (Free Run/Timed/BPM Reader/Log out)
        displayHomeMenu();
        break;
      case 7: //Logout
          menu = 1;
          tab = 1;
          temp = "";
          state = false;
          shift = true;
          break;
      case 9: //User stats
        StatSetup();
        displayUserStats();
        if (connect){
          displayWifi();
        }
        break;
      case 8: //BPM Reader
        BPMsetup();
        displayBPM();
        break;
      case 10: //Home
        FreeRunSetup();
        displayFreeRun();
        if (connect){
        displayWifi();
        }
        break;

    }
  
}

