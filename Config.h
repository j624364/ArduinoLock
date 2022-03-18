#pragma once

constexpr int RELAY_PIN  = A0; // the Arduino pin, which connects to the IN pin of relay
constexpr int ROW_NUM    = 4; //four rows
constexpr int COLUMN_NUM = 4; //four columns

constexpr byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
constexpr byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

const char* password = "1234"; // change your password here

constexpr bool DebugMode { true };
constexpr int WaitTime { 20 * 1000 };
