#include "BPM.h"

const int PULSE_INPUT = A0;          // Analog pin for pulse sensor input
const int GRAPH_HEIGHT = 160;        // Height of the graph display area (160 pixels)
int graphX = 1;                      // Horizontal position for plotting on graph
int prevY = GRAPH_HEIGHT / 2;        // Initial y-coordinate for the previous point

const int MIN_ANALOG = 2800;         // Minimum analog value to show
const int MAX_ANALOG = 3300;         // Maximum analog value to show

TFT_eSprite graph = TFT_eSprite(&tft);

PulseSensorPlayground pulseSensor;

const int GRAPH_WIDTH = 480;   // Width of the graph display area (full width of the TFT screen)

int bpm = 0;                         // Variable to store BPM
unsigned long lastBeatTime = 0;      // Time when the last beat was detected
unsigned long beatInterval = 0;      // Time between beats
int beatCount = 0;                   // Number of beats detected in the current window

unsigned long lastBPMUpdate = 0;     // Timer for BPM calculation
const unsigned long BPM_INTERVAL = 1000; // 1 second for calculating BPM
int previousBPM = -1;  // Previous BPM value (initialized to -1 to ensure the first reading updates the display)

int prevAnalogValue = 0;  // Store the previous analog value for peak detection

unsigned long startMillis;
const unsigned long interval = 10000;

int avg_total = 0;
int temp_index = 0;

void ExitButton(){
tft.setTextColor(TFT_BLACK);
tft.fillRect(400,0,80,40,0x8410);
tft.setCursor(405,10);
tft.print("Exit");
}

void BPMsetup() {
if (!state) {
  tft.fillScreen(TFT_BLACK);

  // Initialize the graph sprite with the updated height
  graph.createSprite(GRAPH_WIDTH-2, GRAPH_HEIGHT-1);
  graph.fillSprite(TFT_BLACK);
  tft.setTextSize(4);
  // Display initial text to confirm setup
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString("BPM Reader",10 ,10);
  tft.setTextSize(2);
  tft.drawString("Place your finger onto the sensor", 10, 70);
  tft.drawString("to begin",10,110);
  

  // Initialize Pulse Sensor
  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.setThreshold(550);  // Adjust threshold if necessary
  ExitButton();

  // Start pulse sensor
  pulseSensor.begin();
  startMillis = millis();
}
state = true;
}

void drawAnalogGraph(int analogValue) {
  // Ignore values outside the desired range
  if (analogValue < MIN_ANALOG || analogValue > MAX_ANALOG) {
    return;
  }

  // Map the analog value within [MIN_ANALOG, MAX_ANALOG] to fit within the graph height
  int y = GRAPH_HEIGHT - map(analogValue, MIN_ANALOG, MAX_ANALOG, 0, GRAPH_HEIGHT);

  // Draw a line connecting the previous point to the current point for smoothness
  graph.drawLine(graphX - 1, prevY, graphX, y, TFT_GREEN);

  // Update the previous y-coordinate to the current one
  prevY = y;

  // Move to the next x position, and wrap around if at the edge
  graphX++;
  if (graphX > 479) {
    graphX = 1;
    graph.fillSprite(TFT_BLACK); // Clear the graph area when wrapping
    prevY = GRAPH_HEIGHT / 2;    // Reset the starting y position after clearing
  }

  // Push the updated sprite to the display
  graph.pushSprite(1, 50); // Position the graph below the title text
}

void drawGraphBorder() {
  // Draw a rectangular border around the graph area
  tft.drawRect(0, 49, GRAPH_WIDTH, GRAPH_HEIGHT+1, TFT_WHITE);
}

void updateBPM() {
  // Calculate BPM every second (based on beat count)
  if (millis() - lastBPMUpdate >= BPM_INTERVAL) {
    bpm = (beatCount * 60)/10;  // Calculate BPM based on beat count in the last second
    avg_total += bpm;
    temp_index += 1;
    if(temp_index > 10){
      users[currentUser].avg_BPM = avg_total / 10;
      avg_total = 0;
      temp_index = 0;
    }
    beatCount = 0;           // Reset beat count for the next interval
    lastBPMUpdate = millis(); // Reset the BPM update timer
  }
}

void updateBPMDisplay() {
  // Only update the display if the BPM value has changed
  if (bpm != previousBPM) {
    tft.setTextSize(3);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); // Overwrite previous value with background
    tft.setCursor(10, GRAPH_HEIGHT+60);
    tft.print("BPM: ");
   // tft.setCursor(80, GRAPH_HEIGHT + 60); // Set cursor position for BPM

    // Print BPM with extra space if it's a single digit
    if (bpm < 10) {
      tft.print(bpm);
      tft.print("   ");  // Extra space to overwrite old digits
    } else if (bpm < 100 && bpm >= 10) {
      tft.print(bpm);
      tft.print("  ");
    } else {
      tft.print(bpm);
      tft.print(" ");
    }

    previousBPM = bpm;  // Update the previous BPM value
  }
}

void displayBPM() {
  unsigned long currentMillis = millis();
  if (touch.touched()){
    Position();
  }
  if (mappedX <= 80 && mappedY >= 260) {
    state = false;
    menu = 6;
    graphX = 1;
    graph.deleteSprite();
    return;
  }
  // Read the raw analog value from the pulse sensor
  int analogValue = analogRead(PULSE_INPUT);

  // Debugging: Print the raw analog value to the serial monitor
 // Serial.println(analogValue);

  // Update the graph with the new analog value
    if (currentMillis - startMillis >= interval) {
  drawAnalogGraph(analogValue);
    }

  // Peak detection algorithm
  if (analogValue > prevAnalogValue) {
    // Value is increasing, so store it as the temporary value
    prevAnalogValue = analogValue;
  } else if (analogValue < prevAnalogValue) {
    // Detect peak when the value decreases after increasing
    beatCount++;  // Increment beat count when a peak is detected
    prevAnalogValue = analogValue;  // Reset temporary value to new value
    //Serial.println("Peak detected!");
  }

  // Update BPM calculation
  updateBPM();

  if (currentMillis - startMillis >= interval) {

  // Draw the graph border
  drawGraphBorder();
  }

  // Update BPM on the display
  static unsigned long lastBPMReadTime = 0;  // Track last BPM read time
  if (millis() - lastBPMReadTime >= 1000) {  // Read BPM every second
    lastBPMReadTime = millis();
      if (currentMillis - startMillis >= interval) {
    updateBPMDisplay();  // Update BPM display if it has changed
      }
  }

  // Short delay to control update speed
  delay(20);
}






