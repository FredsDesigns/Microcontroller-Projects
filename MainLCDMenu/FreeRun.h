#ifndef FREERUN_H
#define FREERUN_H

#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library
#include "UserStats.h"  // Include User.h so users[] is accessible


extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;
extern int menu;
extern bool state;

extern int mappedX;
extern int mappedY;

extern const int wheelRadius;
extern const int rotationSpeed;
extern const int numSpokes;
extern int wheelAngle;

extern int currentUser;

extern TFT_eSprite RIM;

void Position();

void drawBicycleWheel(int angle);
void FreeRunSetup();
void displayFreeRun();

void ExitButton();

void displayWifi();



#endif 