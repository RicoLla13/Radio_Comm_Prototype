#include <SPI.h>

#include <RF24Network.h>
#include <RF24Network_config.h>

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

const int buttonPin = 6;

RF24 radio(7, 8); //CE, CSN
RF24Network network(radio);

const uint16_t thisNode = 011;
const uint16_t masterNode = 01;

RF24NetworkHeader masterHeader(masterNode);

bool buttonState;

void setup() {
  pinMode(buttonPin, INPUT);

  SPI.begin();
  radio.begin();
  network.begin(thisNode);
}

void loop() {
  network.update();

  buttonState = digitalRead(buttonPin);

  network.write(masterHeader, &buttonState, sizeof(buttonState));
}
