#include <Arduino.h>

#define FASTLED_FORCE_SOFTWARE_SPI


#include <FastLED.h>


#define NUM_LEDS 35
#define DATA_PIN 6

CRGB leds[NUM_LEDS];


void setup() {
  // put your setup code here, to run once:
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);  // GRB ordering is typical
    //FastLED.setMaxPowerInVoltsAndMilliamps(5,3000); 
    FastLED.setBrightness(255);  // Set the brightness to a value between 0 and 255
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0; i< NUM_LEDS; i++){
    leds[i] = CRGB::Red;
    FastLED.show();
    delay(100);
    
  }
  for(int i = 0; i< NUM_LEDS; i++){
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(100);
    
  }
  
  // Now turn the LED off, then pause

  
  
}

