#ifndef WIFICONNECT_H
#define WIFICONNECT_H

#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library
#include <WiFi.h>
#include <time.h>

extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;
extern int menu;
extern bool state;

extern int mappedX;
extern int mappedY;

extern char* ssid;
extern char* Wifipassword;

extern bool connect;


void Position();

void displayWifi();
void Wifisetup(String WIFIusername, String WIFIPassword);



#endif 