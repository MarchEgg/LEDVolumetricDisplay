#include <Arduino.h>

#define FASTLED_FORCE_SOFTWARE_SPI


#include <FastLED.h>


#define NUM_LEDS 160
#define DATA_PIN 6

int grid[9][9] = {
  {1, 2, 3, 4, 5, 6, 7, 8, 9},
  {19, 20, 21, 22, 23, 24, 25, 26, 27},
  {37, 38, 39, 40, 41, 42, 43, 44, 45},
  {55, 56, 57, 58, 59, 60, 61, 62, 63},
  {73, 74, 75, 76, 77, 78, 79, 80, 81},
  {91, 92, 93, 94, 95, 96, 97, 98, 99},
  {109, 110, 111, 112, 113, 114, 115, 116, 117},
  {127, 128, 129, 130, 131, 132, 133, 134, 135},
  {145, 146, 147, 148, 149, 150, 151, 152, 153} };


CRGB leds[NUM_LEDS];


void setup() {
  // put your setup code here, to run once:
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    //FastLED.setMaxPowerInVoltsAndMilliamps(5,3000); 
    FastLED.setBrightness(100);  // Set the brightness to a value between 0 and 255
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 9; i++) {
    for( int j = 0; j < 9; j++) {
      int ledIndex = grid[i][j]; // Convert to zero-based index
      leds[ledIndex] = CRGB::Green; // Set the LED to green
      FastLED.show(); // Update the LEDs
      delay(100); // Delay for visibility
    }
  }

  for (int i = 0; i < 9; i++) {
    for( int j = 0; j < 9; j++) {
      int ledIndex = grid[i][j]; // Convert to zero-based index
      leds[ledIndex] = CRGB::Black; // Set the LED to green
      FastLED.show(); // Update the LEDs
      delay(100); // Delay for visibility
    }
  }

  
  // Now turn the LED off, then pause

  
  
}

