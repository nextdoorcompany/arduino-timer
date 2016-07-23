/* 7 segment + to 5V, - to GND, D to A4, C to A5 
 * switch D9 to GND
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
int buttonPin = 9;
int counter = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  matrix.begin(0x70);  
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    matrix.print(counter);
    matrix.writeDisplay();
    counter++;
    delay(1000);
  } else {
    matrix.clear();
    matrix.writeDisplay();
    counter = 0;
  }

}
