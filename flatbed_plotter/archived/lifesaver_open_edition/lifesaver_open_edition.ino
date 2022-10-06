
#include <Servo.h>

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3

const int buttonPin = 10;
int buttonState = 0;
bool printAborted = false;

Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;

int width = 5000; //X-axis (rail)
int height = 5000; //Y-axis (board)

int margin = 0;

int w = width-(margin*2);
int h = height-(margin*2);


void setup() {
//  Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

 // perimeter();

  int x_pos = margin;
  int y_pos = margin;

  long inc = 0;
  int vSpace = 40;
  float inc_step = TWO_PI/w;

  moveToPointAcc(x_pos,y_pos);
  
  while(y_pos<=h && printAborted==false){
          
    inc+=5;
    x_pos = (inc % w) + margin;
    y_pos = (vSpace*(inc/w)) + margin;

    float xfrq = 3+(sin(x_pos*0.001)*0.2);
  
    float mod = sin(x_pos*inc_step*xfrq)*10.000;

//    float pulse1 = sin(y_pos*0.0017);
//    float pulse2 = sin(y_pos*0.00023);
//    float pulse3 = sin(y_pos*0.0003);
    
    float pulse = sin(y_pos*inc_step*5.000)*6.000;
    
    if(mod<pulse && pen_engaged==false){
      if(x_pos<pen_x){
        lower_pen();
        moveToPoint(margin+w,y_pos-vSpace, 500, 40);
        raise_pen();
        moveToPoint(margin,y_pos, 500, 40);
      }
      lower_pen();
      moveToPoint(x_pos, y_pos, 500, 40);
    }else if(mod>=pulse && pen_engaged==true){
      raise_pen();
      moveToPoint(x_pos,y_pos, 500, 40);
    }
  }
  
  returnToHome();
}

void loop() {

}
