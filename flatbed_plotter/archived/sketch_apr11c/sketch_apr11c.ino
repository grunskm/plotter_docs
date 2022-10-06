
#include <Servo.h>

#define x_stepper 4
#define x_dir 5
#define y_stepper 2
#define y_dir 3


Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;

void setup() {
  //Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;

  pinMode(x_stepper, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_stepper, OUTPUT);
  pinMode(y_dir, OUTPUT);
  
  togglePen();
  movePen(500,500);
  togglePen();
    
}

void loop() {
  
 // plotLine(100,100,400,400);
  Serial.println("line here");
}



void plotLine(int X1,int Y1,int X2,int Y2){
  movePen(X1,Y1);
  togglePen();
  movePen(X2,Y2);
  togglePen();
}

void movePen(int X,int Y){
  
  int xd = X-pen_x;
  Serial.println(xd);
  if(xd>0){
    digitalWrite(x_dir,HIGH);
  }else{
    digitalWrite(x_dir,LOW);
  }
  
  int yd = Y-pen_y;
  Serial.println(yd);
  if(yd>0){
    digitalWrite(y_dir,HIGH);
  }else{
    digitalWrite(y_dir,LOW);
  }
  
  //int hypo = sqrt(pow(xd,2)+pow(yd,2));

  while(pen_x < 
    stepPen(x_stepper,100); 
  }
  for(int u=0;u<yd;u++){
    stepPen(y_stepper,1000);
  }
}

void togglePen(){
  if(pen_engaged==false){
    servo.write(180);
    pen_engaged = true;
  }else{
    servo.write(160);
    pen_engaged = false;
  }
}

void stepPen(int pin, int sp){
    digitalWrite(pin, HIGH);
    delayMicroseconds(sp);
    digitalWrite(pin, LOW);
    delayMicroseconds(sp);
}
