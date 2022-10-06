
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

//int width = 32000; //X-axis (rail)
//int height = 28000; //Y-axis (board)

int width = 25000;
int height = 18000;
int spacing = 300;

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

  perimeter();
 //moveToPointAcc(2000,2000);
  int red = 0;
  for(int q=0;q<500;q++){
    random(0,15);
  }

  int margin = height*0.15;
  int w = (width-(margin*2))/spacing;
  int h = (height-(margin*2))/spacing;


  for(int i=0; i<h; i++){
    for(int e=0; e<w; e++){
      int x = margin+e*spacing+random(-100,100);
      int y = margin+i*spacing+random(-100,100);
      if(printAborted ==false){
        bool hitInner = collideCircle(x,y,width*0.5,height*0.5,width*0.15,width*0.075);
        bool hitOuter = collideCircle(x,y,width*0.5,height*0.5,width*0.3,width*0.15);
        
        if(hitInner==true){
          grass(x,y,900,1100);
        }else if(hitOuter==true){
          grass(x,y,50,100);
        }else{
          grass(x,y,900,1100);
        } 
      }
    }
  }
  
 returnToHome();
}

bool collideCircle(int X, int Y,int CIR_X,int CIR_Y,int CIR_W, int CIR_H){

  int x_diff = CIR_X-X;
  int y_diff = CIR_Y-Y;

//  int x_space = sqrt(pow(CIR_R,2)-pow(y_diff,2))*SQUASH;
  int x_space = (pow(x_diff,2)/pow(CIR_W,2))+(pow(y_diff,2)/pow(CIR_H,2));

  
  if( x_space<1){
    return true;
   }else{
    return false;
   }
}


void loop() {

}
