
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

long width = 24000; //X-axis (rail)
int height = 20000; //Y-axis (board)

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

  perimeter(0,0,width,height);
  for(int i=4;i<width/500-3;i++){
    for(int e=4;e<height/500-3;e++){
      if(printAborted==false){
        int x = i*500;
        int y = e*500;
        int dist = 
          circum_dist(x,y,4000,4000,4000)+
          circum_dist(x,y,5700,16650,4000)+
          circum_dist(x,y,17000,7630,4000)+
          circum_dist(x,y,10000,9000,4000);
          
        if(dist==0){
          dist=1;
        }else if(dist>20){
          dist = 20;
        }
        Serial.println(dist);
        
        value_dot(x,y, dist, 250);

      }
    }
  }
  
  
  returnToHome();
}

int circum_dist(int X, int Y, int circ_X, int circ_Y, int D){
  
    int x_diff = X-circ_X;
    int y_diff = Y-circ_Y;
    
    int dist = sqrt(pow(x_diff,2)+pow(y_diff,2));
    if(dist<D){
      dist = D-dist;
    }else{
      dist = dist-D;
    }
    dist = sqrt(pow(dist,2));
    int val = map(dist,0,3000,6,0);
    if(val<1){
      val=0;
    }
    return val;
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
