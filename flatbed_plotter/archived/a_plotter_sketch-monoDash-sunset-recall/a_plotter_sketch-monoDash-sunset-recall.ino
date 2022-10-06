
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
bool hit;
bool in_circle1 = false;
bool in_circle2 = false;

// max width: 32000
// max height: 28000

int width = 8000; //X-axis (rail)
int height = 8000; //Y-axis (board)

int count = 0;

void setup() {
 // Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

  perimeter();

  int w = width*0.8;
  int margin = (height-w)/2;
  int h = height-(margin*2);
 
  int space = 100;
  int n = h/space; 
  int y = 0;

  int inc = 267;

  while(printAborted==false && y<h ){
    
    hoLine(margin,y+margin,w,inc);
    y+=space;
  }

  returnToHome();
}

void hoLine(int X,int Y,int W,int INC){
  servo.write(120); //pen up
  delay(100);
  moveToPointAcc(X,Y);
  if(pen_engaged==true){
    servo.write(145); //pendown
    delay(100);
  }
  int i = 0;
  while(i<W && printAborted==false){
    count++;
    moveToPointAcc(X+i,Y,100);
    if(count%INC==0){
      toggle_pen();
    }
    i++;
  }
  
}


void loop() {

}
