
#include <Servo.h>

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3

const int rows[] = 
{1077,11,114,18,108,21,106,24,101,27,99,30,97,15,7,9,95,14,12,8,93,12,15,8,93,11,17,8,91,10,19,8,91,8,22,7,91,7,23,7,91,7,23,8,9,6,1,12,62,7,23,8,6,6,19,59,7,24,7,4,5,23,58,7,24,7,3,4,26,57,7,24,8,4,29,56,7,24,7,4,30,56,7,24,8,2,17,5,9,56,7,24,7,2,13,12,8,55,8,23,19,15,8,55,8,23,17,18,7,55,8,23,16,19,7,56,7,23,15,20,7,56,8,22,14,21,7,57,7,9,8,5,14,21,7,57,7,8,10,4,13,22,7,46,19,7,5,3,4,2,12,23,7,43,23,6,13,1,12,23,7,41,25,5,14,1,11,23,8,40,27,2,16,12,23,8,39,29,1,16,11,24,8,39,29,17,11,23,8,40,10,6,14,15,12,22,9,39,8,11,12,15,11,23,8,40,7,12,13,14,11,21,10,40,7,14,12,13,11,20,10,41,7,15,11,12,12,18,11,42,7,16,11,11,12,15,14,42,7,18,9,11,11,14,15,43,7,19,7,11,10,12,17,45,7,20,6,10,1,7,11,20,46,7,36,8,6,23,48,7,35,9,6,21,50,8,34,8,6,20,53,7,34,8,6,17,56,8,34,6,8,17,55,8,35,4,9,19,54,9,52,14,53,9,55,12,53,10,55,11,53,11,54,10,54,12,54,9,54,13,53,9,54,14,52,8,55,16,50,7,57,28,36,8,58,26,36,8,60,25,36,7,62,23,36,8,64,19,37,8,63,19,38,8,62,13,15,6,24,8,61,10,19,6,24,8,61,9,19,8,23,7,62,8,20,8,23,8,60,8,21,8,22,9,60,8,21,8,22,8,61,7,21,9,20,10,60,8,21,10,18,10,61,8,21,10,17,10,62,7,21,12,15,11,62,8,20,12,14,11,63,7,21,13,12,10,65,7,20,14,10,11,66,8,19,16,7,11,67,8,18,19,2,13,68,8,17,9,1,24,70,7,16,9,3,21,72,7,15,10,4,19,73,8,14,9,6,16,76,7,12,10,9,13,77,8,10,10,13,7,80,9,9,9,102,9,6,10,103,10,4,10,105,22,107,19,110,18,111,16,113,14,116,10,121,4};
const int cols[] = 
{2603,12,113,18,109,21,106,23,105,24,103,26,102,8,8,11,101,7,11,10,99,8,13,9,98,8,13,9,98,7,16,8,97,7,16,8,97,7,17,8,96,7,17,8,96,7,18,8,9,10,76,7,18,8,6,16,73,7,19,8,2,22,52,15,3,8,18,8,1,25,48,19,1,8,19,34,46,31,17,35,45,31,18,19,1,15,43,33,17,14,11,11,41,35,16,12,15,10,40,8,8,20,16,10,17,9,39,8,13,16,16,9,19,9,38,8,16,14,15,8,21,8,38,7,18,14,14,8,22,7,37,8,20,13,13,8,22,8,35,8,22,12,13,8,22,8,35,7,25,10,13,7,23,8,34,8,24,3,8,13,7,23,7,35,8,22,6,7,13,7,22,8,35,7,23,8,3,2,13,7,21,9,34,8,22,14,13,7,21,8,35,8,19,17,13,7,19,10,36,6,19,17,14,7,18,10,36,7,19,18,13,6,19,9,37,7,19,18,15,3,18,9,39,7,19,2,1,15,35,10,39,7,19,18,34,10,40,7,19,18,33,10,41,7,19,18,31,11,42,7,20,16,1,4,24,13,44,7,20,3,1,10,1,6,20,15,45,7,20,12,1,9,15,18,46,9,19,7,2,12,13,19,47,11,22,16,13,17,50,14,15,18,14,14,54,45,15,16,52,43,17,17,53,38,22,16,54,35,28,12,55,34,29,11,58,29,32,9,62,25,34,8,62,5,18,35,8,61,4,15,9,3,29,7,61,3,13,10,7,27,8,59,3,12,12,7,28,7,58,3,11,14,7,28,7,58,2,11,15,7,28,7,57,3,9,17,7,27,8,57,2,9,17,8,27,8,57,2,8,18,9,26,7,57,2,8,19,9,25,8,57,2,8,19,9,24,9,57,2,7,19,11,23,8,59,8,19,11,22,8,59,1,8,19,12,20,9,60,7,20,13,18,9,61,7,19,14,17,9,61,8,19,15,15,10,61,8,18,17,13,10,62,8,18,8,1,9,12,9,63,7,19,8,1,12,7,10,64,7,18,8,3,27,65,7,18,8,4,25,66,7,17,8,6,24,66,7,16,9,8,21,67,7,16,8,10,18,69,8,13,10,13,14,70,8,12,10,17,9,73,9,7,12,100,28,100,27,102,24,105,22,107,19,112,14};

const int buttonPin = 10;
int buttonState = 0;
bool printAborted = false;

Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;

// max width: 32000
// max height: 28000

int width = 10000; //X-axis (rail)
int height = 10000; //Y-axis (board)
int x_margin = 0;
int y_margin = 0;

int space = 100;

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

  //perimeter();
  
  int k = 0;
  int last_point = -1;
  
  for( int i=0; i<129; i++){
    if(printAborted==false){
    moveToPoint(0,i*space);
    lower_pen();
    
    for( int e=0; e<128; e++){
      if(printAborted==false){
        
        int data_point = 0; //pgm_read_byte(cols+k);
  
        if(data_point != last_point){
         moveToPoint(e*space,i*space);
         toggle_pen();
         last_point = data_point;
        }
        k++;
      }
    }
    moveToPoint(64*space,i*space);
    raise_pen();
    }
  }

  returnToHome();
  
  k = 0;
  last_point = -1;

  for( int i=0; i<129; i++){
    if(printAborted==false){
    moveToPoint(i*space,0);
    lower_pen();
    
    for( int e=0; e<128; e++){
      if(printAborted==false){
        
        int data_point = 0; //pgm_read_byte(rows+k);
  
        if(data_point != last_point){
         moveToPoint(i*space,e*space);
         toggle_pen();
         last_point = data_point;
        }
        
        k++;
      }
    }
    moveToPoint(i*space,64*space);
    raise_pen();
    }
  }
 

  returnToHome();
}


void loop() {

}