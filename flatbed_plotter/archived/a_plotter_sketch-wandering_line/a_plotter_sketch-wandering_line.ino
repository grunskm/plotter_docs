
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

int width = 30000; //X-axis (rail)
int height = 26000; //Y-axis (board)
int margin = 2000;


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
  
  for(int i=0; i<30; i++){
    int t = random(0,10);
  }

  //perimeter();

  for(int i=0; i<100; i++){
    if(printAborted == false){
      
      int x = random(margin*2,width-margin*2);
      int y = random(margin*2,height-margin*2);
      
      int len = random(100,500);

      float frq = 0.02+random(-0.015,0.015);
      float ang = random(-TWO_PI,TWO_PI);
      float newAng = random(-TWO_PI,TWO_PI);
  
      moveToPoint(x,y);
      lower_pen();
      
      for( int e=0; e<len; e++){
          if(e%10==0){
            newAng = random(-TWO_PI,TWO_PI);
          }
          ang = lerp(ang, newAng, frq); 
          x += sin(ang)*40;
          y += cos(ang)*40;
          if(x>margin && x<width-margin && y>margin && y<height-margin && printAborted==false){
            plotLineCont(pen_x, pen_y, x, y);
          }else{break;}
      }
      raise_pen();
    }else{break;};
  }
  
  returnToHome();
}


void loop() {

}
