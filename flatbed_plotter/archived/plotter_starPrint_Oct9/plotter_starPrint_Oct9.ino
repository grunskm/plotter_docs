
#include <Servo.h>
Servo servo;

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3

const int buttonPin = 10;
int buttonState = 0;
bool printAborted = false;

bool pen_engaged;

int pen_x = 0;
int pen_y = 0;


//max width: 32000
//max height: 28000

int width = 15000; //X-axis (rail)
int height = 10000; //Y-axis (board)

int x1; 
int y1;

void setup() {
  //Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

 // perimeter(0,0,width,height);
//  for( int i=1;i<6;i++){
//    for(int e=1;e<4;e++){
//      int xpos = i*(width/6);
//      int ypos = e*(height/4);

     flower(5000,2000,1000,6);
 
//    }
//  }
  
  //flower(1000,1000,1000,6);
  returnToHome();
}


void cross(int X, int Y, int L){
  if(printAborted==false){
    plotLine(X+L,Y,X-L,Y);
    plotLine(X,Y+L,X,Y-L);
  }
}


void loop() {

}
