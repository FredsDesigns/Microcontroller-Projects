#include "STARTINGANIMATION.h"

TFT_eSprite RIM = TFT_eSprite(&tft);
TFT_eSprite Text = TFT_eSprite(&tft);
TFT_eSprite background = TFT_eSprite(&tft);

int wheelAngle = 0;
int wheelX = -100;
int wheelY;
bool isRotating = false;
bool wheelInPosition = false;
bool set = false;
bool TimeDelay = true;

void drawBicycleWheel(int angle) {
    RIM.fillCircle(wheelRadius, wheelRadius, wheelRadius, TFT_BLACK);
    RIM.drawCircle(wheelRadius, wheelRadius, wheelRadius - 1, TFT_WHITE);
    RIM.fillCircle(wheelRadius, wheelRadius, wheelRadius / 3, TFT_WHITE);

    float spokeLength = wheelRadius - 1;
    for (int i = 0; i < numSpokes; i++) {
        float spokeAngle = angle + (360.0 / numSpokes) * i;
        int endX = wheelRadius + spokeLength * cos(radians(spokeAngle));
        int endY = wheelRadius + spokeLength * sin(radians(spokeAngle));
        RIM.drawLine(wheelRadius, wheelRadius, endX, endY, TFT_WHITE);
    }
}

void initStartup() {
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_PURPLE);
    touch.begin();

    RIM.createSprite(wheelRadius * 2, wheelRadius * 2);
    background.createSprite(420, 130);
    Text.createSprite(360,80);
    Text.setTextColor(TFT_WHITE, TFT_BLACK);
    Text.setTextSize(6);
    wheelY = (tft.height() / 2) - 40;
}

void displayStartup() {
  background.fillSprite(TFT_PURPLE);
  Text.fillSprite(TFT_BLACK);
  Text.drawString("REV  LVE",0,0,2);

    if (wheelX >= 212) {
    wheelInPosition = true;
    }
    if (!wheelInPosition) {
        wheelX += 4;
        wheelAngle += rotationSpeed;
        drawBicycleWheel(wheelAngle);
    }

    if (wheelInPosition && TimeDelay ) {
      delay(800);
      TimeDelay = false;
    }
    if (wheelInPosition && !TimeDelay) {
      tft.setTextSize(1);
      tft.setTextColor(TFT_WHITE,TFT_PURPLE);
        tft.drawString("Tap anywhere to continue!", 80, 200, 4);
        wheelAngle += rotationSpeed;
        drawBicycleWheel(wheelAngle);
    }

    if (wheelInPosition && touch.touched() && !TimeDelay) {
        menu = 1;
        wheelAngle = 0;
        RIM.deleteSprite();
        Text.deleteSprite();
        background.deleteSprite();
        return;
    }
   RIM.pushToSprite(&background,wheelX, 40,TFT_BLACK);
   Text.pushToSprite(&background,70,30,TFT_BLACK);
   background.pushSprite(0,0);
}
