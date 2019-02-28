#include <IRremote.h>
#include "PS2Mouse.h"

#define P_DATA 2 //orange
#define P_CLK 4 //jaune
#define RIGHT_CLICK 7
#define LEFT_CLICK 8
#define X_RANGE 0xA00
#define X_N_RANGE 0xA00
#define Y_RANGE 0xB00
#define Y_N_RANGE 0xC00
PS2Mouse mouse(P_CLK, P_DATA);
IRsend irsend;
int left_button = 1;
int right_button = 1;

void setup() {
  Serial.begin(9600);
  pinMode(RIGHT_CLICK, INPUT_PULLUP);
  pinMode(LEFT_CLICK, INPUT_PULLUP);
}

void debugTrackPadValues(MouseData data) {
  Serial.print(data.status, BIN);
  Serial.print("\tx=");
  Serial.print(data.position.x);
  Serial.print("\ty=");
  Serial.print(data.position.y);
  Serial.print("\twheel=");
  Serial.print(data.wheel);
  Serial.println();
}

int encodeXCoordinate(int value) {
  if (value < 0){
    value = -value;
    return value | X_N_RANGE;
  } else if (value >= 0) {
    return value;
  }
}

int encodeYCoordinate(int value) {
  if (value < 0){
    value = -value;
    return value | Y_N_RANGE;
  } else if (value >= 0) {
    return value | Y_RANGE;
  }
}

void loop() {
  //Buttons
  int right = digitalRead(RIGHT_CLICK);
  int left = digitalRead(LEFT_CLICK);

  if (!right && right_button) {
    Serial.print("Send right click\n");
    irsend.sendNEC(0xFFF0, 32);
    delay(40);
    irsend.sendNEC(0xFFF0, 32);
  }
  right_button = right;

  if (!left && left_button) {
    Serial.print("Send left click\n");
    irsend.sendNEC(0xFF00, 32);
    delay(40);
    irsend.sendNEC(0xFF00, 32);
  }
  left_button = left;
  
  //Read the data from the trackPad
  MouseData data = mouse.readData();
  int x = data.position.x;
  int y = data.position.y;
  if (x != 0 || y != 0) {
    debugTrackPadValues(data);
    irsend.sendNEC(encodeXCoordinate(x), 32);
    delay(40);
    irsend.sendNEC(encodeYCoordinate(y), 32);
  }
}
