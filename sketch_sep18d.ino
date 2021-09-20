#include <SPI.h>

#include <RF24Network.h>
#include <RF24Network_config.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const int ledPin = 6;

RF24 radio(7, 8); //CE, CSN
RF24Network network(radio);

const uint16_t thisNode = 00;

bool state[2] = {false, false};

void setup() {
  pinMode(ledPin, OUTPUT);

  SPI.begin();
  radio.begin();
  network.begin(thisNode);
}

void loop() {
  network.update();

  while(network.available()) {
    RF24NetworkHeader h;
    network.read(h, &state, sizeof(state));
  }

  bool val = state[0] || state[1];
  digitalWrite(ledPin, val);
}
