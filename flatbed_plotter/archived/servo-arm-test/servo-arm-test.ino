
#include <Servo.h>

Servo servo1; 
Servo servo2;  

int angle1 = 1;
int angle2 = 1;

float oneInc = 1.3;
int twoInc = 10;


void setup() {
  servo1.attach(9);
  servo2.attach(10);
  Serial.begin(9600); 
}

void loop() {

  if(angle1<=0 || angle1>=180){
    oneInc*=-1; 
    delay(100);
  }
    if(angle2<=0 || angle2>=180){
    twoInc*=-1; 
    delay(100);
  }
 
  angle1 += oneInc;
  angle2 += twoInc;

  //Serial.print(angle1);

  servo1.write(angle1);

  servo2.write(angle2);
  delay(200);

  
}
