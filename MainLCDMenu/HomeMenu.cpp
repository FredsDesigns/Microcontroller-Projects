#include "HomeMenu.h"

// Define arrays for each menu case
const char* menuItemsCase1[] = {
    "New User",
    "Existing User",
    "Guest",
    " Wifi Settings"
};

const char* menuItemsCase6[] = {
    "Home",
    "User Stats",
    "BPM Reader",
    "Log out"
};

int itemHeight = 60;            // Height of each menu item block
int padding = 10;               // Padding between items

// Define the number of items in each menu
const int numItemsCase1 = sizeof(menuItemsCase1) / sizeof(menuItemsCase1[0]);
const int numItemsCase6 = sizeof(menuItemsCase6) / sizeof(menuItemsCase6[0]);

const char** menuItems;

void displayHomeMenu() {
    if (!state) { // Only draw the menu if the state is false
        // Clear the screen and set the state to true
        tft.fillScreen(TFT_BLACK);
        state = true;

        // Assign menuItems based on the current menu
        switch (menu){
          case 1:
            menuItems = menuItemsCase1;
            break;
          case 6:
            menuItems = menuItemsCase6;
            break;
          default:
            menuItems = nullptr; // In case of an unexpected menu value
            break;
        }

        // Determine the number of items based on the selected menu
        int numItems = (menu == 1) ? numItemsCase1 : numItemsCase6;

        // Set text properties for larger text
        tft.setTextColor(TFT_WHITE, TFT_BLACK);
        tft.setTextSize(3);

        // Calculate vertical starting point to center the menu
        int startY = (tft.height() - (numItems * (itemHeight + padding))) / 2;

        // Draw each menu item with a rectangle outline
        for (int i = 0; i < numItems; i++) {
            // Calculate the y position for each menu item
            int posY = startY + i * (itemHeight + padding);

            // Draw the outline rectangle for each menu item
            tft.drawRect((tft.width() - 260) / 2, posY, 260, itemHeight, TFT_WHITE);  // Centered 260px width box

            // Display the text centered inside each rectangle
            tft.drawString(menuItems[i], (tft.width() - tft.textWidth(menuItems[i])) / 2, posY + (itemHeight / 4));
        }
    }

    delay(150);
    if (touch.touched()) {
      Position();
   
        // TS_Point p = touch.getPoint();
        // int mappedX = map(p.x, 0, 4095, 0, tft.width());
        // int mappedY = map(p.y, 0, 4095, 0, tft.height());

        // Calculate the y positions for each item and check if the touch point falls within one
        int startY = (tft.height() - (menu == 1 ? numItemsCase1 : numItemsCase6) * (itemHeight + padding)) / 2; 
        for (int i = 0; i < (menu == 1 ? numItemsCase1 : numItemsCase6); i++) {
            int posY = startY + i * (itemHeight + padding); // Calculate the top of each item block
            if (mappedX >= (tft.width() - 200) / 2 && mappedX <= (tft.width() + 200) / 2 &&
                mappedY >= posY && mappedY <= posY + itemHeight) {
                
                // Change menu based on selection
                switch(menu){
                  case 1:
                  menu = i + 2;  // menu 2 for New User, 3 for Existing User, etc.
                  break;
                  case 6:
                  menu = i + 7;
                  break;
                }
                state = false; // Reset state so the next menu can be drawn
                //tft.fillScreen(TFT_BLACK); // Clear the screen for the new menu
                break;
            }
        }  // Check for touch input and determine which menu item was tapped
    }
  }



