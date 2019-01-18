#include "PS2Mouse.h"
#include "Mouse.h"

/*
* Pin 10 is the mouse data pin, pin 9 is the clock pin
* Feel free to use whatever pins are convenient.
*/
#define P_DATA 10
#define P_CLK 9
PS2Mouse mouse(P_CLK, P_DATA);

void setup() {
    Serial.begin(9600);
    while(!Serial);
    Mouse.begin();
}
void loop() {

    MouseData data = mouse.readData();

    Mouse.move(data.position.x * -1, data.position.y, data.wheel);

    Serial.print(data.status, BIN);
    Serial.print("\tx=");
    Serial.print(data.position.x);
    Serial.print("\ty=");
    Serial.print(data.position.y);
    Serial.print("\twheel=");
    Serial.print(data.wheel);
    Serial.println();
    delay(20);
}
