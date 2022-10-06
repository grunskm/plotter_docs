
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

int width = 15000; //X-axis (rail)
int height = 10000; //Y-axis (board)
int x_margin = 0;
int y_margin = 0;


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

 // grid( 5000, 1000, 100, 16, 32);

  for( int i=0; i<4; i++){
    for( int e=0; e<4; e++){
      int x = i*(4000);
      int y = e*(2400);
      int space = 200;
      
      grid( x, y, space, 16, 8);
        
    }  
  }
  



  
//    for(int i=1;i<xnum;i++){
//      if(printAborted==false){
//        if(i%2==0){
//          moveToPoint(i*xspace+x_margin,y_margin);
//          lower_pen();
//          moveToPoint(i*xspace+x_margin,h+y_margin);
//          raise_pen();
//        }else{
//          moveToPoint(i*xspace+x_margin,h+y_margin);
//          lower_pen();
//          moveToPoint(i*xspace+x_margin,y_margin);
//          raise_pen();
//        }
//      }else{break;}
//    }
//    for(int i=1;i<ynum;i++){
//      if(printAborted==false){
//        if(i%2==0){
//          moveToPoint(x_margin,i*yspace+y_margin);
//          lower_pen();
//          moveToPoint(w+x_margin,i*yspace+y_margin);
//          raise_pen();
//        }else{
//          moveToPoint(w+x_margin,i*yspace+y_margin);
//          lower_pen();
//          moveToPoint(x_margin,i*yspace+y_margin);
//          raise_pen();
//        }
//      }else{break;}
//    }

  returnToHome();
}


void loop() {

}
