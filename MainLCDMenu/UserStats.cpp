#include "UserStats.h"

// Define the 'users' array
User users[5];  // Define the array of users, with space for 5 users

void StatSetup(){
if(!state){
    tft.fillScreen(TFT_BLACK);  // Clear the screen
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(170, 10);  // Position the question at the top
    tft.println("User Stats");
    ExitButton();
}
state = true;
}
void displayUserStats() {
    
    if (touch.touched()){
    Position();
  }
  if (mappedX <= 80 && mappedY >= 260) {
    state = false;
    menu = 6;
    return;
  }
//Display all user set data here VVVVV
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); // Overwrite previous value with background
    tft.drawRect(0, 70, 480, 250, TFT_WHITE);
tft.setCursor(10,80);
tft.print("Username: ");
tft.print(users[currentUser].F_username);
tft.setCursor(10,110);
tft.print("Password: ");
tft.print(users[currentUser].F_password);
tft.setCursor(10,140);
tft.print("Average BPM: ");
tft.print(users[currentUser].avg_BPM);
tft.setCursor(10,170);
tft.print("Total Rotations: ");
tft.print(users[currentUser].Rotation_Total);
tft.setCursor(10,200);
tft.print("Distance Measured: ");
tft.print(users[currentUser].Distance_Total);
tft.setCursor(10,230);
tft.print("Average RPM: ");
tft.print(users[currentUser].RPM);


}

