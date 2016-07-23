/* 7 segment + to 5V, - to GND, D to A4, C to A5 
 * switch D9 to GND
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
int buttonPin = 9;
int seconds = 0;
int minutes = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  matrix.begin(0x70);  
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    matrix.drawColon(true);
    matrix.writeDigitNum(4, seconds % 10);
    matrix.writeDigitNum(3, seconds / 10);
    matrix.writeDigitNum(1, minutes % 10);
    matrix.writeDigitNum(0, minutes / 10);
    matrix.writeDisplay();
    seconds++;
    if (seconds == 60) {
      seconds = 0;
      minutes++;
    }
    delay(1000);
  } else {
    matrix.clear();
    matrix.writeDisplay();
    seconds = 0;
    minutes = 0;
  }

}
