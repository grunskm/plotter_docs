
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
  
  int weight = 25;
  int w = width/weight;
  int h = height/weight;  



  for(int i=0; i<width; i++){
    for(int e=0; e<h; e++){
      if(printAborted==false){

        float x_freq = 4.00;
        float y_freq = 100.00;
        
        float x_mod = sin(i/x_freq);
        float y_mod = sin(e/y_freq)*1000;

        int x = i*weight;
        int y = e+y_mod;
        
        if(e==0 && pen_engaged == true){
          raise_pen();
          moveToPointAcc(x,y);
          lower_pen();
        }else if(i==0){
          moveToPointAcc(x,y);
        }

        if(e>0 && x_mod>y_mod && pen_engaged == false){
          lower_pen();
          moveToPointAcc(x,y);
          
          }else if(e>0 && x_mod<y_mod && pen_engaged == true){
          raise_pen();
          moveToPointAcc(x,y);
        }else{
          break;
        }
      }
    }
  }

  
  returnToHome();
}


void loop() {

}
