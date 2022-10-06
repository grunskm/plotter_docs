
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

int width = 8000; //X-axis (rail)
int height = 8000; //Y-axis (board)

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

//  for(int w=0;w<165;w++){
//    int k = random();
//  }

  perimeter();
  
  int w = width*0.8;
  int margin = (width-w)/2;
  
  int y_spacing = 50;
  int x_spacing = 10;
  
  int h_div = w/y_spacing;
  int w_div = w/x_spacing; 

  int dash_x = 0;
  int dash_y = 0;
  
  
  raise_pen();
  moveToPointAcc(margin,margin);
        
  for(int e=0; e<h_div; e++){
    for(int i=0; i<w_div; i++){
      if(printAborted==false){

        dash_x = margin+(i*x_spacing);
        dash_y = margin+(e*y_spacing);
        
        count++;
        
        float mod = sin(count/10.00);
      
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
