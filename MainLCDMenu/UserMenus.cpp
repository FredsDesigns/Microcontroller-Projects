#include "UserMenus.h"

const int rows = 3;  // Updated to 3 rows
const int cols = 10; // Number of columns in keyboard
bool Numb = false;
const char keyboard[rows][cols] = {
  {'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P'},
  {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', '^'},
  {'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' ', ' ', '<'}
};

const char keyboardLower[rows][cols] = {
  {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p'},
  {'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', '^'},
  {'z', 'x', 'c', 'v', 'b', 'n', 'm', ' ', ' ', '<'}
};

const char numbers[rows][cols] = {
  {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
  {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')'},
  {'?', '~', '/', '-', '_', '+', '=', ' ', ' ', '<'}
};

String username = "";  // String to store the username
String password = "";
bool cursorVisible = true;
unsigned long previousMillisU = 0;
const long interval = 500;  // Cursor blink interval in milliseconds

// Draw the username tab where input will be displayed
void drawUsernameTab() {

  // Clear the username display area
  tft.fillRect(0, 40, tft.width(), 40, TFT_BLACK);  // Clear the username area
  tft.setCursor(10, 50);  // Set cursor just below the prompt
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.print(temp);  // Display the current username
 }


void drawKeyboard() {
  int keyWidth = tft.width() / cols;
  int keyHeight = tft.height() / (rows + 3);
  int margin = 0.5;
tft.setTextColor(TFT_BLACK);

tft.fillRect(0,0,60,40,0x8410);
tft.setCursor(10,10);
tft.print("Back");

tft.fillRect(0,130,60,30,0x8410);
tft.setCursor(10,140);
tft.print("123");

tft.fillRect(400,0,80,40,0x8410);
tft.setCursor(410,10);
tft.print("Enter");

  int keyboardYStart = tft.height() / 2;
  for (int row = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++) {
      int x = col * keyWidth;
      int y = keyboardYStart + row * keyHeight;

      // Special case: Spacebar on the last row
      if (row == 2 && col == 7) {  // Spacebar starts at col 7
        tft.fillRect(x, y, keyWidth * 2, keyHeight, TFT_WHITE);  // Spacebar spans columns 7 and 8
        tft.drawRect(x, y, keyWidth * 2, keyHeight, TFT_BLACK);
        tft.setCursor(x + keyWidth / 2, y + keyHeight / 3);
        tft.setTextSize(2);
        tft.setTextColor(TFT_BLACK);
        tft.print("Space");
        col++;  // Skip next column for space
        continue;  // Skip to the next iteration
      }

      // Draw regular keys
      tft.fillRect(x + margin, y + margin, keyWidth - margin * 2, keyHeight - margin * 2, TFT_WHITE);
      tft.drawRect(x + margin, y + margin, keyWidth - margin * 2, keyHeight - margin * 2, TFT_BLACK);
      tft.setCursor(x + keyWidth / 3, y + keyHeight / 3);
      tft.setTextColor(TFT_BLACK);
      tft.setTextSize(2);
      if (shift && !Numb)
        tft.print(keyboard[row][col]);
      if (!shift && !Numb) {
        tft.print(keyboardLower[row][col]);
      }
      if (Numb) {
        tft.print(numbers[row][col]);
       }
      }
    }
  }

void MenuSetup() {
  if (tab != 3){
  if (!state) {
    tft.fillScreen(TFT_BLACK);  // Clear the screen
      // Draw question at the top
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.setCursor(70, 10);  // Position the question at the top
    temp = "";
    if (menu != 2){
    switch (tab) {
      case 1 :
        tft.println("Please enter your username");
        break;
      case 2 :
        tft.println("Please enter your password");
        break;
     }
    } else{
      switch(tab) {
      case 1 :
        tft.println("Please enter your Wifi SSID");
        break;
      case 2 :
        tft.println("Please enter your password");
        break;
      }
    }
  
    drawUsernameTab();  // Draw an area for username
    drawKeyboard();
  }
    state = true;
 }
}

void TimeCheck() {
  unsigned long currentMillis = millis();
    // Calculate cursor position (end of the username)
  int cursorX = 10 + temp.length() * 12;  // Adjust width per character as needed
  int cursorY = 50;
  
  // Blink the cursor at regular intervals
  if (currentMillis - previousMillisU >= interval) {
    previousMillisU = currentMillis;
    cursorVisible = !cursorVisible;  // Toggle cursor visibility
  }
    // Clear the cursor area before drawing it
  if (cursorVisible) {
    tft.fillRect(cursorX, cursorY, 8, 20, TFT_WHITE);  // Draw cursor rectangle in white
  } else {
    // Clear the cursor area with background color when not visible
    tft.fillRect(cursorX, cursorY, 8, 20, TFT_BLACK);
  }
}

void handleTouch(int x, int y) {
  int keyWidth = tft.width() / cols;
  int keyHeight = tft.height() / (rows + 3);
  int keyboardYStart = tft.height() / 2;

  // Calculate which key was pressed
  if ( y >= 153 && y <= 180 && x >= 414){
    if (!Numb){
    Numb = true;
    } else {
      Numb = false;
    }
    drawKeyboard();
    return;
  }
  int row = (keyboardYStart - y) / keyHeight;  // Adjusted row calculation
  int col = (tft.width() - x) / keyWidth;

  // Handle spacebar
  if (row == 2 && col == 7) {  // Spacebar
    temp += ' ';
    drawUsernameTab();
    return;
  }

  // Handle '<' key
  if (row == 2 && col == 9) {  // '<' key
    if (temp.length() > 0) {
      temp.remove(temp.length() - 1);  // Remove last character
      drawUsernameTab();
    }
    return;
  }

  // Handle regular keys
  if (row >= 0 && row < rows && col >= 0 && col < cols) {
    char keyPressed;
    if (shift && !Numb)
    keyPressed = keyboard[row][col];
    if (!shift && !Numb)
    keyPressed = keyboardLower[row][col];
    if (Numb)
    keyPressed = numbers[row][col];
    if (keyPressed != '^') {
    temp += keyPressed;
    drawUsernameTab();
    } else if (keyPressed == '^'){
        switch(shift){
          case true:
            shift = false;
            break;
          case false:
            shift = true;
            break;
      }
      drawKeyboard();
    }
  }
}

void displayMenuSelect() {
  if (tab != 3) {
  TimeCheck();
  }
  if (touch.touched()) {
    Position();
    // TS_Point p = touch.getPoint();

    // // Map raw touch values to the screen size
    // int mappedX = map(p.x, 200, 4000, 0, tft.width());
    // int mappedY = map(p.y, 200, 4000, 0, tft.height());

    bool leftEdgeTouched = (mappedX >= 410 && mappedY >= 270);
    bool rightEdgeTouched = (mappedX <= 80 && mappedY >= 270);

    Serial.println("MappedY: ");
    Serial.println(mappedY);
    Serial.println(" MappedX: ");
        Serial.println(mappedX);


    // Handle left edge touch conditions
    if (leftEdgeTouched) {
      state = false;
      switch (tab) {
        case 1:
          menu = 1; 
          break;
        case 2:
          tab = 1;
          MenuSetup();
          break;
        case 3:
          tab = 2;
          MenuSetup(); 
          break;
        // case 4:
        //   tab = 3;
        //   MenuSetup();  
        //   break;       
      }
    } 
    // drawUsernameTab();  // Draw an area for username
    // drawKeyboard();
     
    // Handle right edge touch conditions
    else if (rightEdgeTouched) {
      state = false;
      switch (tab) {
        case 1:
          tab = 2;
          username = temp;
          break;
        case 2:
          tab = 3;
          password = temp;
          break;
        case 3:
        if (menu == 5){
          registerUser(username, password);
          tft.fillScreen(TFT_BLACK);
          tft.setTextSize(2);
          tft.setCursor(100, 160);
          tft.println("Account Successfully created!");
          delay(600);
          menu = 6;
          temp = "";
          state = false;
          shift = true;
        } else if (menu == 4){
          checkLogin(username, password);
        } else if (menu == 2) {
          Wifisetup(username, password);
          username = "";
          password = "";
          tab = 1;

         // displayWifi();
          return;
        }
          break;
        // case 4: Should be email registration if possible
        //   menu = 6;
        //   temp = "";
        //   state = false;
        //   shift = true;
        //   break;
      }

      if (tab != 3) {
        MenuSetup();
      }
    }

    // Display confirmation screen when tab == 4
    if (tab == 3 && menu != 6) {
      tft.fillScreen(TFT_BLACK);
      tft.fillRect(0, 0, 60, 40, 0x8410);
      tft.setCursor(10, 10);
      tft.print("Back");

      tft.fillRect(400, 0, 80, 40, 0x8410);
      tft.setCursor(410, 10);
      tft.print("Enter");
      
      tft.setTextColor(TFT_WHITE);
      tft.setTextSize(2);
      tft.setCursor(60, 10);  // Position the question at the top
      tft.println("Is this information correct?");
      
      // Display user information
      int y = 70;
      tft.setCursor(30, y);
      tft.print("Your username is: ");
      tft.println(username);
      
      y += 50;
      tft.setCursor(30, y);
      tft.print("Your password is: ");
      tft.println(password);

       y += 50; //This is also reserved for the email
      // tft.setCursor(30, y);
      // tft.print("Your email is: ");
      // tft.println(email);

    }
    
    // Handle general touch interactions
    else if (tab != 3) {
      handleTouch(mappedX, mappedY);  // Pass the mapped coordinates to handleTouch
    }

    delay(200);  // Delay to avoid overwhelming the serial monitor
  }
}


