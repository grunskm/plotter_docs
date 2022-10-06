
#include <Servo.h>

#define x_stepper 4
#define x_dir 5
#define y_stepper 2
#define y_dir 3


Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;
float r = 100.00;

void setup() {
  //Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;

  pinMode(x_stepper, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_stepper, OUTPUT);
  pinMode(y_dir, OUTPUT);

}

void loop() {

  for(int q=0;q<10;q++){
    randomLine();
  }
}

void randomLine(){

  
  plotLine(x1,y1,x2,y2);
}

void plotLine(int X1,int Y1,int X2,int Y2){
  movePen(X1,Y1);
  togglePen();
  movePen(X2,Y2);
  togglePen();
}

void movePen(int X,int Y){
  
  int xd = pen_x-X;
  if(xd>0){
    digitalWrite(x_dir,HIGH);
  }else{
    digitalWrite(x_dir,LOW);
  }
  
  int yd = pen_y-Y;
  if(yd>0){
    digitalWrite(y_dir,HIGH);
  }else{
    digitalWrite(y_dir,LOW);
  }
  
  //int hypo = sqrt(pow(xd,2)+pow(yd,2));
  int hypo = 100; // number of points per line
  
  int y_steps = yd/hypo; // get number of pulses per section
  int x_steps = xd/hypo;
  
  for(int h=0;h<hypo;h++){//draw "L" for each point on line
    for(int k=0;k<x_steps;k++){ // issue: x_steps is float or less than 1
      stepPen(x_stepper,500); //potential fix: update position independent of stepper, update stepper as integers are reached. 
    }
    for(int k=0;k<y_steps;k++){
      stepPen(y_stepper,500);
    }
  }
  
  pen_x = X; //update current pen position // seems like there might be potential rounding errors here => x-step could be non integer
  pen_y = Y;
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
