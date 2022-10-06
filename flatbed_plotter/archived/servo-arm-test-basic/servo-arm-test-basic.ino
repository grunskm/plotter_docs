
#include <Servo.h>

Servo servo1; 


void setup() {
  servo1.attach(9);
  Serial.begin(9600); 
}

void loop() {

  servo1.write(170);

  delay(100);

  servo1.write(130);

  delay(100);

  
}
