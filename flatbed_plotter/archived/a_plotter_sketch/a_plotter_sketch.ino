
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

int width = 32000; //X-axis (rail)
int height = 28000-4000; //Y-axis (board)

//int width = 5000;
//int height = 5000;

void setup() {
  Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

 //perimeter();
 //moveToPointAcc(1000,1000);
  int red = 0;
  for(int q=0;q<500;q++){
    random(0,15);
  }

  int w = width/300;
  int h = height/300;
  
  for(int e=0; e<(w-1); e++){
    for(int i=0; i<h; i++){
      if( printAborted ==false){
       grass(i*300,e*300+1100,900,1100);
      }
    }
  }
  
  returnToHome();
}


void loop() {

}
