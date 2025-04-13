#ifndef USERMENUS_H
#define USERMENUS_H

#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library
#include <Arduino.h> // Include Arduino library for String


extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;

extern int menu;
extern bool state;
extern bool shift;
extern int tab;
extern int mappedX;
extern int mappedY;
extern String temp;

extern String username;
extern String password;

extern char* ssid;
extern char* Wifipassword;

void Position();

bool registerUser(String newUsername, String newPassword);
void checkLogin(String enteredUsername, String enteredPassword);

void MenuSetup();
void displayMenuSelect();

void Wifisetup(String WIFIusername, String WIFIPassword);


#endif 