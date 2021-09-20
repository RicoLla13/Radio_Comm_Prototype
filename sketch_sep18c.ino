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

const uint16_t thisNode = 01;
const uint16_t masterNode = 00;

bool buttonState, buttonState011;

void setup() {
  pinMode(buttonPin, INPUT);

  SPI.begin();
  radio.begin();
  network.begin(thisNode);
}

void loop() {
  network.update();

  while(network.available()) {
    RF24NetworkHeader h;
    network.read(h, &buttonState011, sizeof(buttonState011));
  }

  buttonState = digitalRead(buttonPin);

  bool data[2] = {false, false};
  data[0] = buttonState;
  data[1] = buttonState011;

  RF24NetworkHeader masterHeader(masterNode);
  bool ok = network.write(masterHeader, &data, sizeof(data));
  delay(1);
}
