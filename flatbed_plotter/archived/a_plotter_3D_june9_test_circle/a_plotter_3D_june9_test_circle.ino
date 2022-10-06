
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

long width = 16000; //X-axis (rail)
int height = 16000; //Y-axis (board)

int x1;
int y1;

float n = 0;
//float scale = 0.000035;
float rad = 5000.00;
float n_step = TWO_PI/360;

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
  
  for(int i=0; i<360; i++){
      if(printAborted==false){
      int x2 = sin(n)*rad+6000;
      int y2 = cos(n)*rad+6000;
  
        if(n==0){
          moveToPointAcc(x2,y2);
          lower_pen();
          x1 = x2;
          y1 = y2;
        }
        plotLineCont(x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
        n += n_step;
      }
    }
 
  returnToHome();
}



void loop() {

}
