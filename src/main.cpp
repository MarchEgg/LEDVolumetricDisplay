#include <Arduino.h>
#include <Adafruit_DotStar.h>
#include <SPI.h>

#define NUMPIXELS 64  // 8x8 matrix
#define DATAPIN   51  // MOSI
#define CLOCKPIN  52  // SCK

int RPM = 2500;
float angle = 0;

Adafruit_DotStar strip(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

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

#define NUM_EDGE_POINTS 10
#define NUM_EDGES 12
#define NUM_VERTICES 8

// Base cube corners (X, Y, Z)
float baseVertices[NUM_VERTICES][3] = {
  {  2.8,  2.8, 5.6 },  // 0
  { -2.8,  2.8, 5.6 },  // 1
  {  2.8, -2.8, 5.6 },  // 2
  { -2.8, -2.8, 5.6 },  // 3
  {  2.8,  2.8, 0.0 },  // 4
  { -2.8,  2.8, 0.0 },  // 5
  {  2.8, -2.8, 0.0 },  // 6
  { -2.8, -2.8, 0.0 }   // 7
};

// Edge list as pairs of indices into baseVertices
int edgeList[NUM_EDGES][2] = {
  {0, 1}, {1, 3}, {3, 2}, {2, 0},  // Top face
  {4, 5}, {5, 7}, {7, 6}, {6, 4},  // Bottom face
  {0, 4}, {1, 5}, {2, 6}, {3, 7}   // Vertical edges
};

// Output: generated edge points
float points[NUM_EDGES * NUM_EDGE_POINTS][3];  // 12*5 = 60 points

void generateEdgePoints() {
  int index = 0;
  for (int e = 0; e < NUM_EDGES; e++) {
    int i0 = edgeList[e][0];
    int i1 = edgeList[e][1];
    for (int j = 0; j < NUM_EDGE_POINTS; j++) {
      float t = (float)j / (NUM_EDGE_POINTS - 1);  // 0.0 to 1.0
      for (int k = 0; k < 3; k++) {
        points[index][k] = (1 - t) * baseVertices[i0][k] + t * baseVertices[i1][k];
      }
      index++;
    }
  }
}

float polarPoints[NUM_EDGES * NUM_EDGE_POINTS][3];

float getDeltaAngle(unsigned long elapsedMs) {
  return elapsedMs * (2.0 * PI * RPM / 60000.0);
}

unsigned long lastUpdate = 0;

void setup() {
  generateEdgePoints();

for (int i = 0; i < NUM_EDGES * NUM_EDGE_POINTS; i++) {
    polarPoints[i][0] = sqrt(pow(points[i][0], 2) + pow(points[i][1], 2));
    float theta = atan2(points[i][1], points[i][0]);
    if (theta < 0) theta += 2 * PI;
    polarPoints[i][1] = theta;
    polarPoints[i][2] = points[i][2];
  }

  strip.begin();
  strip.show();
  lastUpdate = millis();
}

void loop() {
  
  unsigned long now = millis();
  unsigned long delta = now - lastUpdate;
  lastUpdate = now;

  angle += getDeltaAngle(delta);
  if (angle >= 2 * PI) angle -= 2 * PI;

  strip.clear();

  for (int i = 0; i < NUM_EDGES * NUM_EDGE_POINTS; i++) {
  float radius = polarPoints[i][0];
  float theta  = polarPoints[i][1];
  float z      = polarPoints[i][2];

  // Normalize angle difference to handle wraparound
  float deltaTheta = abs(theta - angle);
  if (deltaTheta > PI) deltaTheta = 2 * PI - deltaTheta;

  // Also check for the point on the opposite side (angle + π)
  float deltaThetaOpp = abs(theta - fmod(angle + PI, 2 * PI));
  if (deltaThetaOpp > PI) deltaThetaOpp = 2 * PI - deltaThetaOpp;

  // If either is within visible slice range
  if (deltaTheta < 0.2 || deltaThetaOpp < 0.2) {
    int x = (int)(radius + 3.5); // shift to center x in grid
    int y = 7 - (int)(z + 0.5);  // invert z-axis to match grid row
    if (x >= 0 && x < 8 && y >= 0 && y < 8) {
      strip.setPixelColor(grid[y][x], strip.Color(255, 0, 0));
    }
  }
}

  strip.show();

 /*

  uint32_t blue = strip.Color(0, 0, 255);

  strip.setPixelColor(grid[3][0], blue);
  strip.setPixelColor(grid[4][0], blue);
  
  strip.setPixelColor(grid[2][1], blue);
  strip.setPixelColor(grid[5][1], blue);
  
  strip.setPixelColor(grid[1][2], blue);
  strip.setPixelColor(grid[6][2], blue);
  
  strip.setPixelColor(grid[0][3], blue);
  strip.setPixelColor(grid[7][3], blue);
  
  strip.setPixelColor(grid[0][4], blue);
  strip.setPixelColor(grid[7][4], blue);
  
  strip.setPixelColor(grid[1][5], blue);
  strip.setPixelColor(grid[6][5], blue);
  
  strip.setPixelColor(grid[2][6], blue);
  strip.setPixelColor(grid[5][6], blue);
  
  strip.setPixelColor(grid[3][7], blue);
  strip.setPixelColor(grid[4][7], blue);
  strip.show();
  delay(50);

  
  for (int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      strip.setPixelColor(grid[i][j], strip.Color(0, 0, 255));  // Red
      strip.show();
      delay(50);
      strip.setPixelColor(grid[i][j], 0);  // Off
    } 
  } 
    */
}



