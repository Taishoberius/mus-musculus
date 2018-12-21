//#include <ps2.h>
#include "PS2Mouse.h"
#include "Mouse.h"

/*
* an arduino sketch to interface with a ps/2 mouse.
* Also uses serial protocol to talk back to the host
* and report what it finds.
*/

/*
* Pin 5 is the mouse data pin, pin 6 is the clock pin
* Feel free to use whatever pins are convenient.
*/
#define P_DATA 10
#define P_CLK 9
PS2Mouse mouse(P_CLK, P_DATA);

/*
* initialize the mouse. Reset it, and place it into remote
* mode, so we can get the encoder data on demand.
*/
void mouse_init() {
    /*
    mouse.write(0xff);  // reset
    mouse.read();  // ack byte
    mouse.read();  // blank
    mouse.read();  // blank
    mouse.write(0xf0);  // remote mode
    mouse.read();  // ack
    delayMicroseconds(100);
    */
}


void setup() {
    Serial.begin(9600);
    while(!Serial);
    mouse_init();
    Mouse.begin();
}

/*
* get a reading from the mouse and report it back to the
* host via the serial line.
*/
void loop() {
    /*
    char mstat;
    char mx;
    char my;

    /* get a reading from the mouse
    mouse.write(0xeb);  // give me data!
    mouse.read();      // ignore ack
    mstat = mouse.read();
    mx = mouse.read();
    my = mouse.read();

    /* send the data back up
    Serial.print(mstat, BIN);
    Serial.print("\tX=");
    Serial.print(mx, DEC);
    Serial.print("\tY=");
    Serial.print(my, DEC);
    Serial.println();
    //  delay(20);  /* twiddle */

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
