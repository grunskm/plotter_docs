
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



//max width: 32000
//max height: 28000

long width = 15000; //X-axis (rail)
int height = 15000; //Y-axis (board)

int pen_x = 0;
int pen_y = 0;

int x1;
int y1;

void setup() {
  Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  lower_pen();
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

  perimeter(0,0,width,height);
  
  returnToHome();
}



void loop() {

}
