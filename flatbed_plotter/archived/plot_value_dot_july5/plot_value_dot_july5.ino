
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



//max width: 32000
//max height: 28000

long width = 12000; //X-axis (rail)
int height = 12000; //Y-axis (board)

int pen_x = 0;
int pen_y = 0;

int x1;
int y1;

void setup() {
  Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  lower_pen();
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

  //perimeter(0,0,width,height);
  for(int i=1;i<10;i++){
    for(int e=1;e<10;e++){
      value_dot(i*1000+1000+(i%2+500),e*1000+1000, (e+(i*10))%13+1, 500);
    }
  }
  
  
  returnToHome();
}

void value_dot(int X, int Y, int VAL, int SIZE){
  float s_step = SIZE/VAL;
  float temp = s_step*(VAL+0.50);
  s_step = temp/VAL;

  for(int i=0;i<VAL;i++){
    if(printAborted==false){
      int s = SIZE-(s_step*i);
      ellipse(X,Y,s,s);
    }
  }
  
}

void loop() {

}
