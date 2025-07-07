#include <Arduino.h>


#include <Adafruit_DotStar.h>
#include <SPI.h>

#include <math.h>


#define NUMPIXELS 1200  // 8x8 matrix
#define DATAPIN   D5  // MOSI
#define CLOCKPIN  D10  // SCK

int rpm = 300;
double angle = 0;


int value = 0;
int oldValue = 0;
int oldTime = 0;
int mpr = 0;

// put function declarations here:
int grid[8][8] = {
  {0, 8, 16, 24, 32, 40, 48, 56},
  {1, 9, 17, 25, 33, 41, 49, 57},
  {2, 10, 18, 26, 34, 42, 50, 58},
  {3, 11, 19, 27, 35, 43, 51, 59},
  {4, 12, 20, 28, 36, 44, 52, 60},
  {5, 13, 21, 29, 37, 45, 53, 61},
  {6, 14, 22, 30, 38, 46, 54, 62},
  {7, 15, 23, 31, 39, 47, 55, 63},
};


Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

void setup() {
  strip.begin();
  strip.setBrightness(50);
  strip.show();  // Initialize all pixels to 'off'

  pinMode(D12, INPUT);

}

void loop() {
    
  strip.clear();

  oldValue = value;
  value = digitalRead(D12); // Read the value from pin 30
  if(value != oldValue) // Only print if the value has changed
  {
    if(value == 0){
      mpr = millis() - oldTime; // Print the value to the Serial Monitor
      oldTime = millis();
    }
  }
  //angle += (rpm/(60.0*1000) * 2 * PI) * (millis()-oldTime); // angle in radians
  //oldTime = millis();
  //angle = fmod(angle, (2 * PI));
  
  if( digitalRead(D12) == 0){
    angle = 0;
  }
  if(millis() - oldTime > mpr/2.0){
    angle = PI;
  }

  
  
  

  if(angle > (PI/2) && angle < (3*PI/2)) {
    for(int i = 0; i <4; i++ ){
      for(int j = 0; j < 4; j++){
        strip.setPixelColor(grid[i][j], strip.Color(0, 0, 255));  // Blue
      }
    }
    for(int i = 4; i <8; i++ ){
      for(int j = 4; j < 8; j++){
        strip.setPixelColor(grid[i][j], strip.Color(0, 255, 0 ));  // Blue
      }
    }
    
  }
  else{
    for(int i = 0; i <4; i++ ){
      for(int j = 4; j < 8; j++){
        strip.setPixelColor(grid[i][j], strip.Color(0, 0, 255));  // Blue
      }
    }
    for(int i = 4; i <8; i++ ){
      for(int j = 0; j < 4; j++){
        strip.setPixelColor(grid[i][j], strip.Color(0, 255, 0 ));  // Blue
      }
    }
  }
  strip.show();
  
}
