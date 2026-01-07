#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library
#include <Wire.h>                      // Include Wire library for I2C communication
#include <LiquidCrystal_I2C.h>         // Include the LiquidCrystal_I2C library

// Variables
const int PulseWire = A0;             // PulseSensor PURPLE WIRE connected to ANALOG PIN A0
const int LED = LED_BUILTIN;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 360;                  // Threshold value for detecting heartbeat

PulseSensorPlayground pulseSensor;    // Creates an instance of the PulseSensorPlayground object
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Initialize LCD object with I2C address 0x27, 16 columns, and 2 rows

void setup() {   
  Serial.begin(115200);               // Start serial communication
  lcd.init();                         // Initialize the LCD
  lcd.backlight();                    // Turn on the backlight

  // Configure the PulseSensor object
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.blinkOnPulse(LED);      // Blink built-in LED with heartbeat
  pulseSensor.setThreshold(Threshold);

  // Check if pulseSensor object was created and began seeing a signal
  if (pulseSensor.begin()) {
    Serial.println("PulseSensor object created successfully!");
    lcd.setCursor(0, 0);
    lcd.print("  PulseSensor  ");
  } else {
    Serial.println("Error initializing PulseSensor!");
    lcd.setCursor(0, 0);
    lcd.print("PulseSensor Error");
  }
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {  // Check if a beat happened
    int bpm = pulseSensor.getBeatsPerMinute();  // Get BPM value
    bpm = bpm / 2.8;  // Adjust BPM value if needed
    Serial.print(" Heartbeat BPM: ");     // Print BPM label to serial monitor
    Serial.println(bpm);                  // Print BPM value to serial monitor
    lcd.clear();                          // Clear the LCD
    lcd.setCursor(0, 0);                  // Set cursor to the first row
    lcd.print("  BPM: ");                   // Print BPM label on LCD
    lcd.print(bpm);                       // Print BPM value on LCD
    delay(2000);                          // Delay for 2 seconds
  }
}
