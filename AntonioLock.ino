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
	}
	else {
		input_password.reserve(32); // maximum input characters is 32, change if needed
		pinMode(RELAY_PIN, OUTPUT); // initialize pin as an output.
		digitalWrite(RELAY_PIN, HIGH); // lock the door
	}
}

void loop() {
	if constexpr (DebugMode) {
		digitalWrite(RELAY_PIN, HIGH);
		delay(2000);
		digitalWrite(RELAY_PIN, LOW);
		delay(2000);
	}
	else {
		char key = keypad.getKey();

		if (key) {
			if constexpr (DebugMode)
				Serial.println("Key: " + key);

			if (key == '*') {
				input_password = ""; // reset the input password
			} else if (key == '#') {
				if (input_password == password) {
					Serial.println("Correct password");
					digitalWrite(RELAY_PIN, LOW);  // unlock the door for 20 seconds
					delay(WaitTime);
					digitalWrite(RELAY_PIN, HIGH); // lock the door
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

