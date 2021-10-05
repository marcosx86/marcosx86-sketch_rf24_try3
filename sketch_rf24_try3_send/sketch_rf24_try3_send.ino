//#include "Arduino.h"

#include <SPI.h>
#include <RF24.h>

#define LED 13
//#define LED 5

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

	radio.openWritingPipe(addresses[1]);
}

void loop() {
	Serial.println("Loop!");
	byte b = rand() % 256;
	radio.write(&b, 1);
	Serial.print("Sent ");
	uint32_t t = b * 4;
	Serial.print(t);
	Serial.println("ms delay, waiting...");
	delay(t);
	Serial.println("Wait more 100ms...");
	delay(100);
}
