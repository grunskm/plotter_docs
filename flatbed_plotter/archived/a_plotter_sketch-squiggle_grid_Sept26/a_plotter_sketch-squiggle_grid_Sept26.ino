
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

int width = 22000; //X-axis (rail)
int height = 18000; //Y-axis (board)

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

 // perimeter(0,0,width,height);

  int x1;
  int y1;

  int space = 2000;
  int wid = space/2;
  int x_num = width/space;
  int y_num = height/space;

  float s1 = 0.034;
  float s2 = 0.167;
  float s3 = 0.278;
  float s4 = 0.124;
  float s5 = 0.065;
  float s6 = 0.173;
  float s7 = 0.113;
  float s8 = 0.187;

  int seed = 4300+315;

  
  for(int q=0;q<y_num-2;q++){
    for(int e=0;e<x_num-2;e++){

      int posX = e*space*1.05+space/4;
      int posY = q*space*1.05+space/4;
      perimeter(posX,posY,space,space);
      
     seed += 5;

     for(int h=0;h<100;h++){
      if(printAborted==false){
  
        float sx = (sin((h+seed)*s1)+sin((h+seed)*s2)+sin((h+seed)*s3)+sin((h+seed)*s4))/4.00;
        float sy = (sin((h+seed)*s5)+sin((h+seed)*s6)+sin((h+seed)*s7)+sin((h+seed)*s8))/4.00;
        
        int x2 = (sx*wid)+posX+(space/2);
        int y2 = (sy*wid)+posY+(space/2);
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




void loop() {

}
