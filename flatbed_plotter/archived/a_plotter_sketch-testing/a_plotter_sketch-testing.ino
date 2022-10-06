#include <plotter_functions.h>


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
//
//int width = 32000; //X-axis (rail)
//int height = 28000; //Y-axis (board)

int width = 26500; //X-axis (rail)
int height = 26500; //Y-axis (board)

Paper paper(10,10);

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


  returnToHome();
}

void spiral(int X, int Y, int MAX_R, int MIN_R){
  
  int max_r = MAX_R;
  float r = MIN_R;
  int inc = 0;
  
  
  while(r<max_r && printAborted==false){
    inc++;
    r += 0.01;
    float a = TWO_PI/pow(PI*r,2);
    
    float cir_x = X+sin(a+inc*0.001)*r;
    float cir_y = Y+cos(a+inc*0.001)*r;
    
    if(inc==1){
      moveToPointAcc(cir_x,cir_y);
      toggle_pen();
    }else{moveToPointAcc(cir_x,cir_y);}
    
    if(inc%200==0){
      toggle_pen();
    }
  }
  toggle_pen();
}


void loop() {

}
