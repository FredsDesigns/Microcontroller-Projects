#ifndef STARTINGANIMATION_H
#define STARTINGANIMATION_H

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

extern TFT_eSPI tft;
extern XPT2046_Touchscreen touch;
extern int menu;

// Wheel properties and animation variables
extern bool isRotating;
extern bool wheelInPosition;
extern bool set;

extern const int wheelRadius;
extern const int rotationSpeed;
extern const int numSpokes;

// Functions for initializing and displaying startup animation
void initStartup();
void displayStartup();

#endif

