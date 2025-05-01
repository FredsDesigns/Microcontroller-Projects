// Arduino code to interface with AT93C46 EEPROM
// This code writes the first 128 ASCII characters to the chip and reads them back
// Written from scratch without external libraries
// Please refer to the README for circuit setup help and debugging tips!

// Pin definitions
#define EEPROM_CS_PIN 10    // Chip Select pin
#define EEPROM_DI_PIN 11    // Data Input pin (MOSI)
#define EEPROM_DO_PIN 12    // Data Output pin (MISO)
#define EEPROM_SK_PIN 13    // Serial Clock pin (SCK)

// AT93C46 Commands (8-bit mode)
#define EEPROM_CMD_READ  0b110      // Start bit (1) followed by READ opcode (10)
#define EEPROM_CMD_WRITE 0b101      // Start bit (1) followed by WRITE opcode (01)
#define EEPROM_CMD_EWEN  0b10011    // Start bit (1) followed by EWEN opcode (00) + address bits (11)
#define EEPROM_CMD_EWDS  0b10000    // Start bit (1) followed by EWDS opcode (00) + address bits (00)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  // Setup pins
  pinMode(EEPROM_CS_PIN, OUTPUT);
  pinMode(EEPROM_SK_PIN, OUTPUT);
  pinMode(EEPROM_DI_PIN, OUTPUT);
  pinMode(EEPROM_DO_PIN, INPUT);
  
  // Initial state
  digitalWrite(EEPROM_CS_PIN, LOW);
  digitalWrite(EEPROM_SK_PIN, LOW);
  digitalWrite(EEPROM_DI_PIN, LOW);
  
  Serial.println("AT93C46 EEPROM Interface Test");
  
  // Enable writing to the EEPROM
  enableWrite();
  
  // Write the first 128 ASCII characters to the EEPROM
  writeASCIIChars();
  
  // Read and display the 128 ASCII characters
  readASCIIChars();
  
  // Disable writing to the EEPROM
  disableWrite();
  
  Serial.println("Test completed!");
}

void loop() {
  // Nothing to do in the loop
}

// Generic helper function to send bits serially
void sendBits(byte data, int bit_count) {
  for (int i = bit_count - 1; i >= 0; i--) {
    digitalWrite(EEPROM_DI_PIN, (data >> i) & 1);
    delay(1);
    
    // Clock pulse
    digitalWrite(EEPROM_SK_PIN, HIGH);
    delay(1);
    digitalWrite(EEPROM_SK_PIN, LOW);
    delay(1);
  }
}

// Function to enable writing to the EEPROM
void enableWrite() {
  Serial.println("Enabling write...");
  
  // Select the chip
  digitalWrite(EEPROM_CS_PIN, HIGH);
  delay(1);
  
  // Send the EWEN command (Write Enable)
  sendBits(EEPROM_CMD_EWEN, 5); // 5 bits for the complete command
  sendBits(0, 5); // 5 dummy bits
  
  // Deselect the chip
  digitalWrite(EEPROM_CS_PIN, LOW);
  delay(1);
  
  Serial.println("Write enabled");
}

// Function to disable writing to the EEPROM
void disableWrite() {
  Serial.println("Disabling write...");
  
  // Select the chip
  digitalWrite(EEPROM_CS_PIN, HIGH);
  delay(1);
  
  // Send the EWDS command (Write Disable)
  sendBits(EEPROM_CMD_EWDS, 5); // 5 bits for the complete command
  sendBits(0, 5); // 5 dummy bits
  
  // Deselect the chip
  digitalWrite(EEPROM_CS_PIN, LOW);
  delay(1);
  
  Serial.println("Write disabled");
}

// Function to write the first 128 ASCII characters to the EEPROM
void writeASCIIChars() {
  Serial.println("Writing ASCII characters...");
  
  for (int i = 0; i < 128; i++) {
    writeEEPROM(i, i); // Write ASCII value to the corresponding address
    
    // Print progress every 16 characters
    if (i % 16 == 15) {
      Serial.print("Written up to character: ");
      Serial.println(i);
    }
    
    delay(20); // Small delay between writes, can be adjusted to be quicker, but will require a logical analyzer to view if timings occur correctly
  }
  
  Serial.println("All ASCII characters written");
}

// Function to read and display the 128 ASCII characters
void readASCIIChars() {
  Serial.println("Reading ASCII characters:");
  
  for (int i = 0; i < 128; i++) {
    byte value = readEEPROM(i);
    
    // Print the address, decimal, and hex values
    Serial.print("Address ");
    Serial.print(i);
    Serial.print(": Dec=");
    Serial.print(value);
    Serial.print(", Hex=0x");
    if (value < 16) Serial.print("0");
    Serial.print(value, HEX);
    
    // Print the actual character only for printable values
    if (value >= 32 && value < 127) {
      Serial.print(", Char='");
      Serial.write(value);
      Serial.print("'");
    }
    
    Serial.println();
    delay(5); // Small delay between reads
  }
}

// Function to write a byte to the EEPROM
void writeEEPROM(byte address, byte data) {
  // Check if address is within range (0-127 for this task)
  if (address > 127) {
    Serial.println("Error: Address out of range");
    return;
  }
  
  // Select the chip
  digitalWrite(EEPROM_CS_PIN, HIGH);
  delay(1);
  
  // Send the WRITE command (3 bits: start bit + 2 opcode bits)
  sendBits(EEPROM_CMD_WRITE, 3);
  
  // Send the address (7 bits in 8-bit mode)
  sendBits(address, 7);
  
  // Send the data (8 bits)
  sendBits(data, 8);
  
  // Deselect the chip
  digitalWrite(EEPROM_CS_PIN, LOW);
  
  // Wait for the write cycle to complete
  delay(10);
}

// Function to read a byte from the EEPROM
byte readEEPROM(byte address) {
  byte data = 0;
  // Select the chip
  digitalWrite(EEPROM_CS_PIN, HIGH);
  delay(1);
  
  // Send the READ command
  sendBits(EEPROM_CMD_READ, 3); // 3 bits for the command (start bit + 2 opcode bits)
  
  // Send the address (7 bits in 8-bit mode)
  sendBits(address, 7);
  
  // Read the data (8 bits)
  for (int i = 7; i >= 0; i--) {
    // Clock pulse
    digitalWrite(EEPROM_SK_PIN, HIGH);
    delay(1);
    
    // Read bit
    if (digitalRead(EEPROM_DO_PIN)) {
      data |= (1 << i);
    }
    
    digitalWrite(EEPROM_SK_PIN, LOW);
    delay(1);
  }
  
  // Deselect the chip
  digitalWrite(EEPROM_CS_PIN, LOW);
  
  return data;
}