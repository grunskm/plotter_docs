
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
int interval = 300;

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


  int thickness = width/6;
  
  int off = 0;
  int space = 50;

  while(off<thickness && printAborted==false){
    count=0;
    off+=space;

    arcDashedQ(width*0.66, height*0.5-thickness*2,off,off, TWO_PI*0.25, 0,-1);
    lineDashed(width*0.66, height*0.5-thickness*2+off, width*0.33, height*0.5-thickness*2+off);
    arcDashed(width*0.33, height*0.5-thickness,thickness-off,thickness-off, PI, 0,1);
    lineDashed(width*0.33, height*0.5-off, width*0.66, height*0.5-off);
    arcDashed(width*0.66, height*0.5,off,off, PI, 0,-1);
    lineDashed(width*0.66, height*0.5+off, width*0.33, height*0.5+off);
    arcDashedQ(width*0.33, height*0.5+thickness,thickness-off,thickness-off, TWO_PI*0.5, TWO_PI*0.75,-1);
    
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
    }else{break;}
  }


}

void arcDashedQ(int X,int Y,int W, int H, float START, float END,int DIR){
  
  int steps = PI*(W+H)/4;
  float a = (START-END)/steps*DIR;
  
  for(int g=0;g<steps;g++){
    count++;
    if(count%interval==0 && printAborted==false){
      toggle_pen();
    }
    float cir_x = X+sin(START+a*g)*W;
    float cir_y = Y+cos(START+a*g)*H;
    if(count==1){
      raise_pen();
      moveToPointAcc(cir_x,cir_y);
      lower_pen();
    }else if(printAborted==false){
      moveToPoint(cir_x,cir_y,150);
    }else{break;}
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
    if(count==1){
      raise_pen();
      moveToPointAcc(cir_x,cir_y);
      lower_pen();
    }else if(printAborted==false){
      moveToPoint(cir_x,cir_y,150);
    }else{break;}
  }
  
}


void loop() {

}
