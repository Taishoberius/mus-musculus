#include <IRremote.h>
#include "Mouse.h"
#define X_N_RANGE 0xA00
#define Y_RANGE 0xB00
#define Y_N_RANGE 0xC00

int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

decode_results results;

int decode_x(int code) {
  if(code < 0xA00) return code;
  return (code & 0x0FF) * - 1;
}

int decode_y(int code) {
  if(code > 0xA00 && code < 0xC00) return code & 0x0FF;
  return (code & 0x0FF) * - 1;
}

int decode(int code) {
  if(code < 0xB00) return decode_x(code);
  return decode_y(code);
}

void setup()
{
  Serial.begin(9600);
  Mouse.begin();
  while(!Serial);
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("IR Receiver... Started");
}

void loop() {
  //single threaded nature seems to break below 
  int x = 0;
  int y = 0;
  // i want to start receiver here
  if (irrecv.decode(&results)) {
    if (results.decode_type == NEC) {
      if (results.value < Y_RANGE) {
        x = decode(results.value);
      } else {
        y = decode(results.value);
      }
    }
    if(x || y) Mouse.move(x, y, 0);
    
    irrecv.resume(); // Receive the next value
  }
} 
