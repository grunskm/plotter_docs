
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

int width = 20000; //X-axis (rail)
int height = 20000; //Y-axis (board)
int x_margin = 4000;
int y_margin = 4000;

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
//
  int red = 0;
  for(int q=0;q<100;q++){
    random(0,15);
  }

  perimeter();

  int w = width-(x_margin*2);
  int h = height-(y_margin*2);

  int xnum = 64;
  int ynum = 64;
  int xspace = w/xnum;
  int yspace = h/ynum;


    for(int i=0;i<=xnum;i++){
      if(printAborted==false){
          moveToPoint(i*xspace+x_margin,y_margin);
          lower_pen();
          moveToPoint(i*xspace+x_margin,h+y_margin);
          raise_pen();
      }else{break;}
    }
    for(int i=0;i<=ynum;i++){
      if(printAborted==false){
          moveToPoint(x_margin,i*yspace+y_margin);
          lower_pen();
          moveToPoint(w+x_margin,i*yspace+y_margin);
          raise_pen();
      }else{break;}
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
