#include "UserRegistration.h"


const int maxUsers = 5;               // Max number of users the system can hold
String usernames[maxUsers];            // Array to hold usernames
String passwords[maxUsers];            // Array to hold passwords
int currentUserCount = 0;              // Tracks the number of registered users

// Function to register a new user
bool registerUser(String newUsername, String newPassword) {
  if (currentUserCount < maxUsers) {
    usernames[currentUserCount] = newUsername;
    passwords[currentUserCount] = newPassword;
    currentUser = currentUserCount;
    users[currentUser].F_username = newUsername;
    users[currentUser].F_password = newPassword;
    currentUserCount++;
    return true;  // Registration successful
  } else {
    return false; // Registration failed (no more space)
  }
}

// Function to check login
bool login(String enterUsername, String enterPassword) {
  for (int i = 0; i < currentUserCount; i++) {
    if (usernames[i] == enterUsername && passwords[i] == enterPassword) {
      currentUser = i;
      return true;  // Login successful
    }
  }
  currentUser = -1;
  return false;  // Login failed
}

void checkLogin(String enteredUsername, String enteredPassword) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(100, 160);

  // Check login
  if (login(enteredUsername, enteredPassword)) {
    tft.println("Login successful, Welcome!");
    delay(1000);
    menu = 6;        // Navigate to the next menu
    temp = "";      // Clear temp variable (if needed)
    state = false;  // Set the state
    shift = true;   // Set the shift
  } else {
    tft.println("Login failed, please try again.");
    delay(1000);
    tab = 1;        // Reset the tab or handle UI logic
  }
}


