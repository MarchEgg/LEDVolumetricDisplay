#include <Arduino.h>
#include <FastLED.h>



#define NUM_LEDS 10
#define DATA_PIN 50

CRGB leds[NUM_LEDS];


void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(255);  // Set brightness to 50 out of 255

}

void loop() {
  // put your main code here, to run repeatedly:
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Green;
  leds[7] = CRGB::Blue;
  leds[8] = CRGB::White;
  leds[9] = CRGB::Yellow;
  FastLED.show();
  delay(500);
}

