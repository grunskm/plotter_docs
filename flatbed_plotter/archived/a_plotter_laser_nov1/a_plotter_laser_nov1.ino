
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

//max width: 32000
//max height: 28000

long width = 8000; //X-axis (rail)
int height = 8000; //Y-axis (board)

void setup() {
  Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

  //perimeter(0,0,width,height);

  for(int a=0;a<20;a++){  
    if(printAborted==false){
      int x = width/2-(a*50+50);
      int y = height/2-(a*50+50);
      int w = a*100+100;
      int h = a*100+100;
      rect(x,y,w,h);
    }
  }

  returnToHome();
}

void loop() {

}
