
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

// max width: 32000
// max height: 28000

int width = 16000; //X-axis (rail)
int height = 16000; //Y-axis (board)
int x_margin = width*0.1;
int y_margin = height*0.1;

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

//  perimeter();

  

  int r = 0;
  int r_max = width*0.4;
  while(r<=r_max && printAborted==false){
    r+=35;
    int x = r+width*0.1;
    int y = r+width*0.1;
    int w = r;
    int h = r;
    
    ellipse(x,y,w,h);
  }

//  ellipse(7000,10000,5000,6000);
//  

  returnToHome();
}


void loop() {

}
