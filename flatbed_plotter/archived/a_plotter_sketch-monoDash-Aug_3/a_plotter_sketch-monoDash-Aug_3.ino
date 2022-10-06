
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

int width = 10000; //X-axis (rail)
int height = 10000; //Y-axis (board)

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

  for(int w=0;w<15;w++){
    int k = random();
  }

  //perimeter();
  
  int section_w = 8000;
  int y_spacing = 25;
  int x_spacing = 10;
  
  int h_space = section_w/y_spacing;
  int w_space = section_w/x_spacing; 


  int x = 0;
  int y = 0;
  int dash_x = 0;
  int dash_y = 0;
  int last_y = 0;
  
  float f1 = random(100.00,200.00);
  float f2 = random(100.00,200.00);
  float f3 = random(100.00,200.00);

  int saved_e = 0;
  int ii;
  
  raise_pen();
  moveToPointAcc(x,y);
        
  for(int e=0; e<h_space; e++){
    for(int i=0; i<w_space; i++){
      if(printAborted==false){

        if(e%2!=0){
          ii = w_space-i;
        }else{
          ii = i;
        }
        
        int n = (ii*x_spacing)+(e*w_space);
        
        float modA = sin(e/12.00);
        float modB = sin(i/15.00);
        
        float frqA = sin(n/f1);
        float frqB = sin(n/f2);
        float frqC = sin(e/f3);

        float mod = modB+modA+frqA+frqB+frqC;
        
        last_y = dash_y;
        dash_x = x+(ii*x_spacing);
        dash_y = y+(e*y_spacing);
       
        if(mod>=0 && pen_engaged == false){
          lower_pen();
          moveToPointAcc(dash_x,dash_y);
        }else 
        if(mod<0 && pen_engaged == true){
          raise_pen();
          moveToPointAcc(dash_x,dash_y);
        }
      }else{
        break;
      }
    }
  }
  returnToHome();

}


void loop() {

}
