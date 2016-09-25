#include <SPI.h>
#include <Ethernet2.h>
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment matrix = Adafruit_7segment();
int seconds = 1;
int minutes = 0;

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

IPAddress ip(192, 168, 10, 80);

IPAddress myDns(1, 1, 1, 1);

EthernetClient client;

IPAddress server(192, 168, 10, 230);
int port = 8080;

void setup() {
  matrix.begin(0x70);

  // give the ethernet module time to boot up:
  delay(1000);

  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  httpRequest();
}

void loop() {
  writeLED(seconds, minutes);
  seconds++;
  if (seconds > 59) {
    seconds = 0;
    minutes++;
  }
  if (minutes > 99) {
    minutes = 0;
  }
  delay(1000);
}

void writeLED(int seconds, int minutes) {
  matrix.drawColon(true);
  matrix.writeDigitNum(4, seconds % 10);
  matrix.writeDigitNum(3, seconds / 10);
  matrix.writeDigitNum(1, minutes % 10);
  matrix.writeDigitNum(0, minutes / 10);
  matrix.writeDisplay();
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, port)) {
    client.println("POST /andon/HMF HTTP/1.1");
    client.println("Host: 192.168.10.230:8080");
    client.println("User-Agent: arduino-ethernet");
    client.println("Connection: close");
    client.println();

  }

}


