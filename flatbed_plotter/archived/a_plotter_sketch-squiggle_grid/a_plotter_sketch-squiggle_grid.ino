
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

//max width: 32000
//max height: 28000

int width = 28000; //X-axis (rail)
int height = 24000; //Y-axis (board)

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

  int red = 0;
  for(int q=0;q<900;q++){
    random(0,15);
  }

  perimeter();

  int x1;
  int y1;

  int space = 2000;
  int wid = space/2;
  int x_num = width/space;
  int y_num = height/space;

  
  for(int q=2;q<y_num-1;q++){
    for(int e=2;e<x_num-1;e++){
      
      float s1 = 1.00/random(100.00,200.00);
      float s2 = 1.00/random(100.00,200.00);
      float s3 = 1.00/random(100.00,200.00);
      float s4 = 1.00/random(100.00,200.00);
      float s5 = 1.00/random(100.00,200.00);
      float s6 = 1.00/random(100.00,200.00);
      float s7 = 1.00/random(100.00,200.00);
      float s8 = 1.00/random(100.00,200.00);
      
     for(int h=0;h<1000;h++){
      if(printAborted==false){
        int hh = h+1000;
        float sx = (sin(hh*s1)+sin(hh*s2)+sin(hh*s3)+sin(hh*s4))/4.00;
        float sy = (sin(hh*s5)+sin(hh*s6)+sin(hh*s7)+sin(hh*s8))/4.00;
        int x2 = (sx*wid)+(e*space);
        int y2 = (sy*wid)+(q*space);
        if(h==0){
          moveToPointAcc(x2,y2);
          toggle_pen();
          x1 = x2;
          y1 = y2;
        }
        plotLineCont(x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
      }
     }
     if(printAborted==false){
      toggle_pen();
     }
    }
  }

  
  returnToHome();
}

bool collideCircle(int X, int Y,int CIR_X,int CIR_Y,int CIR_R, float SQUASH){

  int x_diff = CIR_X-X;
  int y_diff = CIR_Y-Y;

  int x_space = sqrt(pow(CIR_R,2)-pow(y_diff,2))*SQUASH;

  int x_min = CIR_X-x_space;
  int x_max = CIR_X+x_space;
  
  if( Y>CIR_Y-CIR_R 
   && Y<CIR_Y+CIR_R 
   && X>x_min
   && X<x_max){
    return true;
   }else{
    return false;
   }
}


void loop() {

}
