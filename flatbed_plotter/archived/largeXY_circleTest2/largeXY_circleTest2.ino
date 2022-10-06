
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

void setup() {
  Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);
  
}

void loop() {
  plotCircle(r);
  r +=100;
}

void plotCircle(int R){
  int count = 0;
  int circumference = R*TWO_PI;
  
  for(int e=1;e<circumference/2;e++){
    if(e%40==0){
      toggle_pen();
    }
    float d = e/r*2;
    Serial.println(d);

    int target_x = floor(sin(d)*r*2)+(r);
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,HIGH);
    }else{
      digitalWrite(x_dir,LOW);
    }
    for(int q=0;q<x_distance;q++){
      movePen(x_step,200);
    }
    
    int target_y = floor(cos(d)*r*2)+(r);
    int y_diff = pen_y-target_y;
    int y_distance = sqrt(pow(pen_y-target_y,2));
    pen_y = target_y;
    
    if(y_diff>0){
      digitalWrite(y_dir,HIGH);
    }else{
      digitalWrite(y_dir,LOW);
    }
    for(int q=0;q<y_distance;q++){
      movePen(y_step,200);
    }
    count++;
    if(count==1){
     toggle_pen(); 
    }
  }
  toggle_pen();
  delay(500);
}

void toggle_pen(){
  if(pen_engaged==false){
    servo.write(180);
    pen_engaged = true;
  }else{
    servo.write(160);
    pen_engaged = false;
  }
}

void movePen(int pin, int sp){
    digitalWrite(pin, HIGH);
    delayMicroseconds(sp);
    digitalWrite(pin, LOW);
    delayMicroseconds(sp);
}
