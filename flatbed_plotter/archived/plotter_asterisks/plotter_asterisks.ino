
#include <Servo.h>

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3


Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;
float r = 100.00;
int w = 3000;

void setup() {
  //Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);
  
}

void loop() {
  //toggle_pen();
//  moveToPoint(random(-w,w),random(-w,w));
//  toggle_pen();
//  plotLine(random(-w,w),random(-w,w),random(-w,w),random(-w,w));
    for(int d=0; d<20; d++){
      for(int f=0; f<20; f++){
        plotLine(d*500,f*500,d*500+500,f*500+500);
      }
    }
}

void plotLine(int X1,int Y1,int X2,int Y2){
  moveToPoint(X1,Y1);
  toggle_pen();
//  for(int s=0; s<5; s++){
//     
//  }
  moveToPoint(X2,Y2);
  toggle_pen();
}

void moveToPoint(int X,int Y){
  
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,HIGH);
    }else{
      digitalWrite(x_dir,LOW);
    }
    for(int q=0;q<x_distance;q++){
      stepPen(x_step,300);
    }
    
    int target_y = Y;
    int y_diff = pen_y-target_y;
    int y_distance = sqrt(pow(pen_y-target_y,2));
    pen_y = target_y;
    
    if(y_diff>0){
      digitalWrite(y_dir,HIGH);
    }else{
      digitalWrite(y_dir,LOW);
    }
    for(int q=0;q<y_distance;q++){
      stepPen(y_step,300);
    }
}

void toggle_pen(){
  if(pen_engaged==false){
    servo.write(180);
    pen_engaged = true;
  }else{
    servo.write(160);
    pen_engaged = false;
  }
  delay(300);
}

void stepPen(int pin, int sp){
    digitalWrite(pin, HIGH);
    delayMicroseconds(sp);
    digitalWrite(pin, LOW);
    delayMicroseconds(sp);
}
