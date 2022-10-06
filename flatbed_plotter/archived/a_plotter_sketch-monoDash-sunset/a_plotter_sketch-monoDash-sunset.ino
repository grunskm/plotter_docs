
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

int width = 15000; //X-axis (rail)
int height = 15000; //Y-axis (board)

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

  int space = 30;
  int n = w/space;

  for(int i=0; i<n; i++){
    if(printAborted==false){
      int x1 = margin;
      int y1 = margin+i*space;
      int x2 = margin+w;
      int y2 = y1;
      
      plotLineDashed(x1,y1,x2,y2,i,n);
    }
  }

  returnToHome();
}


void loop() {

}
