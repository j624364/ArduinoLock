/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-door-lock-system-using-password
 */

#include "Config.h"
#include <Keypad.h>

char keys[ROW_NUM][COLUMN_NUM] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

static String input_password;

void setup() {
	Serial.begin(9600);

	if constexpr (DebugMode) {
		Serial.println("Debug mode");

		pinMode(9, INPUT);
		pinMode(8, INPUT);
		pinMode(7, INPUT);
		pinMode(6, INPUT);
		pinMode(5, INPUT);
		pinMode(4, INPUT);
		pinMode(3, INPUT);
		pinMode(2, INPUT);

		pinMode(12, OUTPUT);
		digitalWrite(12, HIGH);
	}
	else {
		input_password.reserve(32); // maximum input characters is 32, change if needed
		pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
		digitalWrite(RELAY_PIN, LOW); // lock the door
	}
}

void printPin(int pinNumber)
{
	volatile auto val = digitalRead(pinNumber);

	if (val == HIGH)
		Serial.print("1");
	else if (val == LOW)
		Serial.print("0");
	else
		Serial.print("?");

	val = digitalRead(pinNumber);
}

void loop() {
	if constexpr (DebugMode) {
		printPin(9);
		printPin(8);
		printPin(7);
		printPin(6);
		printPin(5);
		printPin(4);
		printPin(3);
		printPin(2);

		Serial.println();
	}
	else {
		char key = keypad.getKey();

		if (key) {
			Serial.print("Key: ");
			Serial.print(key);
			Serial.println();

			if (key == '*') {
				input_password = ""; // reset the input password
			} else if (key == '#') {
				if (input_password == password) {
					Serial.println("Correct password");
					digitalWrite(RELAY_PIN, HIGH);  // unlock the door for 20 seconds
					delay(WaitTime);
					digitalWrite(RELAY_PIN, LOW); // lock the door
				} else {
					Serial.println("Incorrect Password");
				}

				input_password = ""; // reset the input password
			} else {
				input_password += key; // append new character to input password string
			}
		}
	}
}

