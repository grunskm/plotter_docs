
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

// max width: 32000
// max height: 28000

int width = 5000; //X-axis (rail)
int height = 5000; //Y-axis (board)

int count = 0;

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

//  int red = 0;
//  for(int q=0;q<900;q++){
//    random(0,15);
//  }

 // perimeter();



  int x = height*0.5;
  int y = width*0.5;
  int i = 0;
  float r = 50.00;

  moveToPointAcc(x,y);
  toggle_pen();

  while(printAborted==false){
    i++;
    
    r += 7.20*0.01;
    float circum = 0.01;
   // int dash = 200+(sin(i*(1.00/20.00))*20.00);
    int x_pos = sin(i*circum)*r+x;
    int y_pos = cos(i*circum)*r+y;
    
    if(r>height*0.4){
      printAborted = true;
    }
    moveToPointAcc(x_pos,y_pos);
  }

  
  returnToHome();
}


void loop() {

}
