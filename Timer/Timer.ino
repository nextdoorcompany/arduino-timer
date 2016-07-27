/* 7 segment + to 5V, - to GND, D to SDA, C to SCL, IO jump to +
 * switch 1 D9 to GND
 * switch 2 D8 to GND
 */

#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
int switchOne = 9;
int switchTwo = 8;
int seconds = 0;
int minutes = 0;

void setup() {
  pinMode(switchOne, INPUT_PULLUP);
  pinMode(switchTwo, INPUT_PULLUP);
  matrix.begin(0x70);  
}

void loop() {
  if ((digitalRead(switchOne) == LOW) || (digitalRead(switchTwo) == LOW)) {
    matrix.drawColon(true);
    matrix.writeDigitNum(4, seconds % 10);
    matrix.writeDigitNum(3, seconds / 10);
    matrix.writeDigitNum(1, minutes % 10);
    matrix.writeDigitNum(0, minutes / 10);
    matrix.writeDisplay();
    seconds++;
    if (seconds > 59) {
      seconds = 0;
      minutes++;
    }
    if (minutes > 99) {
      minutes = 0;
    }
    delay(1000);
  } else {
    matrix.clear();
    matrix.writeDisplay();
    seconds = 0;
    minutes = 0;
  }

}
