
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

int width = 30000; //X-axis (rail)
int height = 25000; //Y-axis (board)

int margin = width*0.1;


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
  
  int w = (width-(margin*2))/300;
  int h = (height-(margin*2))/300;

  for(int i=3; i<=h; i++){
    for(int e=0; e<=w; e++){
      int x = margin+e*300+random(-100,100);
      int y = margin+i*300+random(-100,100); 
   
      if(printAborted ==false){
        if(x>width*0.2 && x<width*0.8 && y>height*0.75 && y<height*0.85){
          grass(x,y,10,12);
        }else{
          grass(x,y,900,1100);
        }
      }
    }
  }
  
 returnToHome();
}




void loop() {

}
