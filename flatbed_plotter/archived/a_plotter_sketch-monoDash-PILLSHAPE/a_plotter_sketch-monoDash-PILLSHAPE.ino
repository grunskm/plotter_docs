
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

int width = 10000; //X-axis (rail)
int height = 10000; //Y-axis (board)

int count = 0;
int interval = 250;

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


  int innerh = width*0.33;
  
  int off = 0;
  int space = 50;

  while(off<innerh && printAborted==false){
    count=0;
    off+=space;
    
    arcDashed( width*0.66, height*0.5, off, off, TWO_PI, TWO_PI*0.5,1);
    lineDashed( width*0.66, height*0.5-off, width*0.66-off, height*0.5-off);
    lineDashed( width*0.66-off, height*0.5-off, width*0.66-off, height*0.5+(innerh-off));
    lineDashed( width*0.66-off, height*0.5+(innerh-off), width*0.33, height*0.5+(innerh-off));
    arcDashed( width*0.33, height*0.5, innerh-off, innerh-off, TWO_PI,TWO_PI*0.5,-1);
  }


  returnToHome();
}

void lineDashed(int X1,int Y1,int X2,int Y2){
//  raise_pen();
//  moveToPointAcc(X1,Y1);
//  lower_pen();
  
  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(xdiff,2)+pow(ydiff,2));
  float x_space = xdiff/hypo;
  float y_space = ydiff/hypo;
  
  for(int s=1; s<hypo; s++){
    count++;    
    if(count%interval==0 && printAborted==false){
      toggle_pen();
    }
    int X = X1+(x_space*s);
    int Y = Y1+(y_space*s);
    if(printAborted==false){
      moveToPointAccDraw(X,Y);
    }
  }


}

void arcDashed(int X,int Y,int W, int H, float START, float END,int DIR){
  
  int steps = PI*(W+H)/2;
  float a = (START-END)/steps*DIR;
  
  for(int g=0;g<steps;g++){
    count++;
    if(count%interval==0 && printAborted==false){
      toggle_pen();
    }
    float cir_x = X+sin(START+a*g)*W;
    float cir_y = Y+cos(START+a*g)*H;
    if(g==0 && DIR==1){
      raise_pen();
      moveToPointAcc(cir_x,cir_y);
      lower_pen();
    }else if(printAborted==false){
      moveToPoint(cir_x,cir_y,150);
    }
  }
  
}


void loop() {

}
