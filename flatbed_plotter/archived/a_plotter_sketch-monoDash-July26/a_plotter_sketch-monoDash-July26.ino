
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

int width = 25000; //X-axis (rail)
int height = 25000; //Y-axis (board)

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
  
  int weight = 30;
  int w_space = width/weight;
  int h_space = height/weight; 

  int grid_w = width/5000;
  int grid_h = height/5000;

  for(int q=0;q<grid_w;q++){
    for(int t=0;t<grid_h;t++){
      int x = q*5000;
      int y = t*5000;
      rect(x,y,5000,5000);
    }
  }

//
//  for(int e=0; e<h_space; e++){
//    for(int i=0; i<width; i++){
//      if(printAborted==false){
//        
//        int n = (i+(e*width));
//        
//        float frqA = sin(n/100.00);
//        float frqB = sin(n/67.00);
//        float frqC = sin(n/29.00);
//
//        float mod = frqA+frqB+frqC;
//        
//        int x = i+8000;
//        int y = e*weight+11000;
//        //ellipse(x,y,500,500);
//        if(i==0 && pen_engaged == true){
//          raise_pen();
//          moveToPointAcc(x,y);
//        }else 
//        if(i==0){
//          moveToPointAcc(x,y);
//        }
//       
//        if(i>0 && mod>=0 && pen_engaged == false){
//          lower_pen();
//          moveToPointAcc(x,y);
//          }else 
//        if(i>0 && mod<0 && pen_engaged == true){
//          raise_pen();
//          moveToPointAcc(x,y);
//          }
//        }else{
//          break;
//        }
 //   }
//  }
//
//  
//  returnToHome();
}


void loop() {

}
