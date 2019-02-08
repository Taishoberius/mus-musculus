#include <IRremote.h>
#include "PS2Mouse.h"

#define P_DATA 10
#define P_CLK 11
#define X_RANGE 0xA00
#define X_N_RANGE 0xA00
#define Y_RANGE 0xB00
#define Y_N_RANGE 0xC00
PS2Mouse mouse(P_CLK, P_DATA);
IRsend irsend;

void setup() {
  Serial.begin(9600);
  while(!Serial);

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
