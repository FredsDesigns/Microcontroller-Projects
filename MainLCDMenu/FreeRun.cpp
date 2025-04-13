#include "FreeRun.h"

const int hallPin = 27;      // Pin connected to the Hall-effect sensor
int magnetCount = -1;        // Counter to track detections
int Temp_Count = -1;
bool previousState = LOW;   // To store the previous state of the sensor
const float distance = 0.0012; // 0.0012 miles covered in one full rotation
int BestBPM = 0;
float NuDistance;

unsigned long startTime = 0;
unsigned long endTime = 3000;

unsigned long RPM_TimerStart = 0; // Holds the elapsed time
unsigned long RPM_TimerEnd = 0; // Tracks the last time the timer was reset
const unsigned long resetInterval = 60000; // 60 seconds in milliseconds

void FreeRunSetup(){
if(!state){
    tft.fillScreen(TFT_BLACK);  // Clear the screen
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(200, 10);  // Position the question at the top
    tft.println("Home");
    pinMode(hallPin, INPUT);
    RIM.createSprite(wheelRadius * 2, wheelRadius * 2);
    ExitButton();
}
state = true;
}

void displayFreeRun(){
  if (touch.touched()){
    Position();
  }
  if (mappedX <= 80 && mappedY >= 260) {
    state = false;
    menu = 6;
    RIM.deleteSprite();
    return;
  }

  int sensorState = digitalRead(hallPin);  // Read the current state of the sensor
  // Check for a rising edge: LOW to HIGH transition

    // Hall effect sensor check
    if (sensorState == HIGH && previousState == LOW) {
        startTime = millis();  // Reset the 3-second timer on new detection
        magnetCount++;  // Increment the counter on detection
        Temp_Count++;
        users[currentUser].Rotation_Total = magnetCount;
        NuDistance = distance * magnetCount;
        users[currentUser].Distance_Total = NuDistance;


        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setCursor(70, 220);
        tft.print("Total Rotation Count: ");
        tft.println(magnetCount);  // Display magnet count
        tft.setCursor(70, 260);
        tft.print("Distance covered in Miles: ");
        tft.println(NuDistance, 4);
    }
    // Calculate the elapsed time
RPM_TimerStart = millis() - RPM_TimerEnd;
        if (RPM_TimerStart < resetInterval && magnetCount == Temp_Count) {
            users[currentUser].RPM = Temp_Count;
        }

        // Check if 60 seconds have passed
        if (RPM_TimerStart >= resetInterval) {
            if (Temp_Count > BestBPM){
              BestBPM = Temp_Count;
              users[currentUser].RPM = BestBPM; // Update RPM

            }
            RPM_TimerStart = 0;                  // Reset the timer
            Temp_Count = 0;                      // Reset temporary counter
            RPM_TimerEnd = millis();             // Reset the previous time
        }

    // If 3 seconds have passed without a new detection, stop updating wheel
    if (millis() - startTime <= endTime) {
        wheelAngle += rotationSpeed;  // Update wheel angle
        drawBicycleWheel(wheelAngle);  // Draw the bicycle wheel
    } else {
        // No new detection after 3 seconds, so don't update the wheel
    }

    // Update previous state for next loop
    previousState = sensorState;


  RIM.pushSprite(200,80);
  delay(10);  // Small delay to stabilize the reading
}



