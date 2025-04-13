#ifndef BPM_H
#define BPM_H

#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library
#include <Arduino.h>
#include <PulseSensorPlayground.h>
#include "UserStats.h"  // Include User.h so users[] is accessible


extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;
extern int menu;
extern bool state;

extern int mappedX;
extern int mappedY;

extern int currentUser;

void Position();

void BPMsetup();
void displayBPM();

#endif 