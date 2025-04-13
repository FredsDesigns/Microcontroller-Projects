#ifndef USERSTATS_H
#define USERSTATS_H

#include <String.h>
#include <TFT_eSPI.h> // Include the TFT_eSPI library
#include <XPT2046_Touchscreen.h>      // Include the touch library

extern TFT_eSPI tft; // Create an instance of the TFT_eSPI class
extern XPT2046_Touchscreen touch;
extern int menu;
extern bool state;

extern int mappedX;
extern int mappedY;

extern int currentUser;

void Position();
void ExitButton();

void displayUserStats();
void StatSetup();

// Define the User struct
struct User {
    String F_username;
    String F_password;
    int avg_BPM;
    int Rotation_Total;
    float Distance_Total;
    int RPM; 

        //User() : username(""), password(""), age(0), avgBPM(0.0) {} Intialization if necessary
};

// Declare the 'users' array as extern
extern User users[5];  // Assume there are 5 users
//users[0].username = "john_doe";

#endif
