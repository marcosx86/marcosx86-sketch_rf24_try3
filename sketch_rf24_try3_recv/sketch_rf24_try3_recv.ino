//#include "Arduino.h"

#include <SPI.h>
#include <RF24.h>

//#define LED 13
#define LED 5

RF24 radio(10, 9);
uint8_t addresses[][6] = { "Prime", "21234", "3ABCD", "49876", "5ABCD", "6FFFF" };

void setup() {
	pinMode(LED, OUTPUT);

	Serial.begin(9600);

	if (!radio.begin()) {
		Serial.println(F("radio hardware not responding!"));
		radio.powerDown();
		while (1) {
			digitalWrite(LED, HIGH);
			delay(50);
			digitalWrite(LED, LOW);
			delay(50);
		} // hold program in infinite loop to prevent subsequent errors
	}
	Serial.println("Initialized!");

	radio.setRetries(15, 15);
	radio.setPayloadSize(1);
	radio.setAutoAck(true);

	radio.openReadingPipe(1, addresses[1]);
	radio.startListening();
}

void loop() {
	if (radio.available()) {
		Serial.println("Available!");
		byte b;
		bool ok = radio.read2(&b, 1);
		if (ok) {
			uint32_t t = b * 4;
			Serial.print("Received! Waiting for ");
			Serial.print(t+50);
			Serial.println("ms...");
			digitalWrite(LED, LOW);
			delay(t);
			digitalWrite(LED, HIGH);
			delay(100);
		}
	}
}
