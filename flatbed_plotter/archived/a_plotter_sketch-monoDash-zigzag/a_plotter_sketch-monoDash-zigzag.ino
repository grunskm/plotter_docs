
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
int interval = 15;
int dashLen = 533;
int dash;

// max width: 32000
// max height: 28000

int width = 28000; //X-axis (rail)
int height = 28000; //Y-axis (board)

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

  int red = 0;
  for(int q=0;q<900;q++){
    random(0,15);
  }

  perimeter();

  int w = height*0.8;
  int margin = (height-w)/2;

  int weight = 75;
  int n = w/weight;
  

  for(int i=0; i<n; i++){
    if(printAborted==false){

      int x1 = margin;
      int y1 = margin+i*weight;
      int x2 = x1+w;
      int y2 = margin+i*weight;
  
       if(i%interval==0){
        interval = random(20,50);
        dashLen = random(530,540);
       }
      dash = (sin(i*0.005)*50.00)+dashLen;
      plotLineDashed(x1,y1,x2,y2,i,n);
    }
  }

  
  returnToHome();
}


void loop() {

}
