/*
  Ohm Meter Project
  Author: Basem ElSharkawy
  Repository: https://github.com/basem-elsharkawy/
  Description: Arduino-based digital ohmmeter using a 128×64 OLED (I2C).
  Hardware: Arduino Uno/Nano, 0.96" OLED, resistor divider.
  Features:
    • Measures unknown resistance.
    • Displays readings with unit scaling (Ω, KΩ).
    • Uses bitmap graphics for icons.
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "bitmaps.h"  // Bitmap definitions

// OLED display configuration
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Hardware / measurement configuration
const int analogPin = A0;
const float referenceResistor = 1600.0;  // in ohms

// Function prototypes
float readAverageADC(int sampleCount = 10);
float calculateResistance();
void showResistanceOnDisplay(float resistance);

void setup() {
  Serial.begin(9600);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println(F("SSD1306 init failed"));
    for (;;) ;  // Halt
  }
  display.clearDisplay();
  display.display();
  delay(500);
}

void loop() {
  float resistance = calculateResistance();
  showResistanceOnDisplay(resistance);
  delay(500);
}

/**
 * Reads multiple samples from the ADC and returns their average.
 */
float readAverageADC(int sampleCount) {
  long sum = 0;
  for (int i = 0; i < sampleCount; i++) {
    sum += analogRead(analogPin);
    delay(2);
  }
  return sum / (float) sampleCount;
}

/**
 * Calculates the unknown resistance based on the voltage divider formula.
 * Returns:
 *   -1.0 if open circuit,
 *    0.0 if short circuit,
 *    measured resistance otherwise.
 */
float calculateResistance() {
  float adcValue = readAverageADC();

  if (adcValue >= 1020.0) {
    return -1.0;  // open circuit
  }
  if (adcValue <= 3.0) {
    return 0.0;  // short circuit
  }

  float voltage = (adcValue * 5.0) / 1023.0;
  float resistance = referenceResistor * voltage / (5.0 - voltage);
  return resistance;
}

/**
 * Renders the resistance value (or error states) on the OLED display.
 * Display format kept identical to your original layout.
 */
void showResistanceOnDisplay(float resistance) {

  if (resistance < 0) {
    display.clearDisplay();
    display.drawBitmap(37, 1, image_HEADER_bits, 55, 13, 1);
    display.setTextSize(2);
    display.setTextColor(1);
    display.setCursor(23, 24);
    display.print("OPEN");
    display.setCursor(23, 40);
    display.print("CIRCUIT");
    display.drawBitmap(72, 23, image_link_bits, 15, 16, 1);
    display.display();
  }
  else if (resistance == 0) {
    display.clearDisplay();
    display.drawBitmap(37, 1, image_HEADER_bits, 55, 13, 1);
    display.setTextColor(1);
    display.setTextSize(2);
    display.setTextWrap(false);
    display.setCursor(23, 24);
    display.print("SHORT");
    display.setCursor(23, 40);
    display.print("CIRCUIT");
    display.drawBitmap(84, 23, image_link_bits, 15, 16, 1);
    display.display();
  }
  else {
    if (resistance >= 1000.0) {
    float kiloOhmValue = (int)resistance / 1000.0;
    kiloOhmValue = round(kiloOhmValue * 10) / 10.0;
    display.clearDisplay();
    display.drawBitmap(37, 1, image_HEADER_bits, 55, 13, 1);
    display.setTextColor(1);
    display.setTextSize(2);
    display.setTextWrap(false);
    display.setCursor(23, 32);
    display.print(kiloOhmValue,1);
    display.drawBitmap(76, 32, image_KOHM_bits, 28, 14, 1);
    display.display();
    }
    else {
    int roundedResistorValue = (int)resistance;
    display.clearDisplay();
    display.drawBitmap(37, 1, image_HEADER_bits, 55, 13, 1);
    display.setTextColor(1);
    display.setTextSize(2);
    display.setTextWrap(false);
    display.setCursor(36, 32);
    display.print(roundedResistorValue);
    display.drawBitmap(74, 32, image_OHM, 17, 14, 1);
    display.display();
    }
  }

}
