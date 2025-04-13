#include "WifiConnect.h"

// Timezone settings (adjust to your timezone)
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -18000; // Example: -5 hours for GMT-5
const int daylightOffset_sec = 3600; // Adjust for daylight savings if applicable

unsigned long previousMillisW = 0;  // Variable to store the last time we updated
const long interval = 1000;  // Interval for updating time (in milliseconds)

unsigned long wifitime = 0;
const unsigned long timeout = 20000;

void Wifisetup(String WIFIusername, String WIFIPassword) {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);

    WiFi.begin(WIFIusername.c_str(), WIFIPassword.c_str());
    tft.setCursor(10, 10);
    tft.print("Connecting to Wi-Fi...");
    wifitime = millis();

    // Wait for Wi-Fi connection or timeout
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        tft.print(".");
        if ((millis() - wifitime >= timeout)) {
            tft.setCursor(10, 100);
            tft.print("WiFi couldn't connect");
            menu = 1;
            connect = false;
            return;
        }
    }

    // Wi-Fi connected
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(70, 10);
    tft.println("WiFi connected!");
    tft.setCursor(70, 30);
    tft.print("Synchronizing time...");
    
    // Configure time
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    // Wait for NTP time sync with a timeout
    unsigned long syncStart = millis();
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        if (millis() - syncStart >= timeout) {
            tft.setCursor(10, 100);
            tft.print("Time sync failed!");
            menu = 1;
            connect = false;
            return;
        }
        delay(500);
    }

    tft.fillScreen(TFT_BLACK);
    tft.setCursor(70, 10);
    tft.println("Time synchronized!");
    menu = 1;
    connect = true;
}


void displayWifi() {
    tft.setTextSize(2);
    if (!connect) {
        tft.setCursor(10, 10);
        tft.print("WiFi not connected!");
        return;
    }

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        tft.setCursor(10, 10);
        tft.print("Failed to fetch time");
        return;
    }

    // Convert time to 12-hour format
    int hour = timeinfo.tm_hour;
    int displayHour = hour % 12;
    if (displayHour == 0) displayHour = 12;
    const char* period = (hour >= 12) ? "PM" : "AM";

    const char* daysOfWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    tft.setCursor(10, 10);
    tft.printf("%s %s %02d", daysOfWeek[timeinfo.tm_wday], months[timeinfo.tm_mon], timeinfo.tm_mday);
    tft.setCursor(10, 50);
    tft.printf("Time: %02d:%02d:%02d %s", displayHour, timeinfo.tm_min, timeinfo.tm_sec, period);
}
