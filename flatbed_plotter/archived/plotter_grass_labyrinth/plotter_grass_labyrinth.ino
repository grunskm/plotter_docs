
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

int width = 25000+4000; //X-axis (rail)
int height = 20000+4000; //Y-axis (board)

int space = 1000;
int w = 25;
int h = 20;

int dataArray[] = {
1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,
1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,0,1,
1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,
1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,1,
1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,
1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,
1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,1,
1,0,1,0,1,0,0,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,0,1,
1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,
1,0,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,0,1,
1,0,1,1,0,1,0,1,0,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,1,
1,0,0,0,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,1,0,1,
1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,0,1,
1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

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

  for(int i = 0; i<h; i++){
    for(int e = 0; e<w; e++){
      
      int x = e*space+space*2;
      int y = i*space+space*2; 
      
      int index = (i*w)+e;
   
      if(printAborted ==false){
        if(dataArray[index] < 0.5){
          grassSquare(x,y,20,42);
        }else{
          grassSquare(x,y,500,800);
        }
      }
    }
  }
  
 returnToHome();
}

void grassSquare(int X, int Y, int MIN, int MAX){
  
  for(int e=0; e<5; e++){
    for(int i=0; i<5; i++){
      if(printAborted ==false){
      int x = X+(i*200)+random(-50,50);
      int y = Y+(e*200)+random(-50,50);
      
      grass(x,y,MIN,MAX);
      }
    } 
  }
}

void loop() {

}
