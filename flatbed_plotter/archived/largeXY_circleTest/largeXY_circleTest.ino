
#include <Servo.h>

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3


Servo servo;
bool pen_engaged = false;

int pen_x = 0;
int pen_y = 0;
int r = 100;


void setup() {
  Serial.begin(9600);

  servo.attach(9);
  servo.write(150);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);
  
}


void loop() {

  for(int e=1;e<360;e++){
    if(e==2){
       toggle_pen();
    }
    float d = e/360.00*TWO_PI;

    int target_x = floor(sin(d)*r)+(r);
    int target_y = floor(cos(d)*r)+(r);

    int x_dist = pen_x-target_x;
    int y_dist = pen_y-target_y;

    int x_distance = sqrt(pow(pen_x-target_x,2));
    int y_distance = sqrt(pow(pen_y-target_y,2));
    
    pen_x = target_x;
    pen_y = target_y;

    if(x_dist>0){
      digitalWrite(x_dir,HIGH);
    }else{
      digitalWrite(x_dir,LOW);
    }
    for(int q=0;q<x_distance;q++){
      move(x_step,500);
    }
    
    if(y_dist>0){
      digitalWrite(y_dir,HIGH);
    }else{
      digitalWrite(y_dir,LOW);
    }
    for(int q=0;q<y_distance;q++){
      move(y_step,500);
    }
  }
  toggle_pen();
  delay(500);
  r+=100;
}

void toggle_pen(){
  if(pen_engaged==false){
    servo.write(180);
    pen_engaged = true;
  }else{
    servo.write(150);
    pen_engaged = false;
  }
}

void move(int pin, int sp){
    digitalWrite(pin, HIGH);
    delayMicroseconds(sp);
    digitalWrite(pin, LOW);
    delayMicroseconds(sp);
}
