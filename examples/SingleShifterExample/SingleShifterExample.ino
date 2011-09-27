#include <Serial2Parallel.h>

Serial2Parallel shifter;

void setup() {
  shifter.init(8,9,10);
}

byte pin = 0;
void loop() {
  
  shifter.clear();
  shifter.set( pin, true );
  shifter.sync();
  
  delay(100);
  
  pin = (++pin) % 8;
}
