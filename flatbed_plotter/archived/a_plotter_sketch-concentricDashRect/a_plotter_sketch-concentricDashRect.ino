
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

// max width: 32000
// max height: 28000

int width = 32000; //X-axis (rail)
int height = 28000; //Y-axis (board)

int count = 0;

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

//  int red = 0;
//  for(int q=0;q<900;q++){
//    random(0,15);
//  }

  perimeter();

  int margin = height*0.1;
  int weight = 50;
  int n = (height*0.33)/weight;

  for(int i=0; i<n; i++){
    int dash = 337;
    int x = (i*weight)+margin;
    int y = (i*weight)+margin;
    int w = width-(2*x);
    int h = height-(2*y);
    
    rectDashed(x,y,w,h,dash);
  }

  
  returnToHome();
}


void loop() {

}
