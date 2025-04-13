#ifndef USERREGISTRATION_H
#define USERREGISTRATION_H

#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library
#include <Arduino.h> // Include Arduino library for String
#include "UserStats.h"  // Include User.h so users[] is accessible



extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;
extern int menu;
extern bool state;
extern bool shift;
extern int tab;
extern String temp;
extern String username;
extern String password;

extern int currentUser;

bool registerUser(String newUsername, String newPassword);
void checkLogin(String enteredUsername, String enteredPassword);

#endif 