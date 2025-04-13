#ifndef HOMEMENU_H
#define HOMEMENU_H

#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library

extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;
extern int menu;
extern bool state;

extern int mappedX;
extern int mappedY;

void Position();

void displayHomeMenu();

void initStartup();
void displayStartup();


#endif 