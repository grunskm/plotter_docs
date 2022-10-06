
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
bool flip = false;
float t=0;

// max width: 32000
// max height: 28000

int width = 15000; //X-axis (rail)
int height = 15000; //Y-axis (board)

double count = 0.00;
int depth;
float frq[10];
float amp[10];
int c_step = 5;
float squash;

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

  perimeter(-width/2, -height/2, width, height);

  for(int i=0;i<5;i++){
    int nothing = random();
  }
    
  int w = width*0.6;
  int margin = (height-w)/2;
  int h = height-(margin*2);

  int space = 100;
  int n = h/space;
  int horizon = n*0.55;
  int thresh = w*0.4;
  squash = 0.5;

  depth = 3;
  for(int i=0;i<depth;i++){
    frq[i] = random(1,10)/1000.00;
    amp[i] = random(1,20)/100.00;
  }

  t= 0.25;
  for(int i=0; i<horizon; i++){
      if(printAborted==true){
        break;
      }
      bool hit = false;
      bool circle1 = false;
      bool circle2 = false;
      
      int x_start = -width/2+margin;
      int x_end = x_start+w;
      
      int y = -height/2+margin+i*space;

      int x1 = x_start;
      int x2 = x_start;

      int ang_off = TWO_PI*0.17;
      count = 0;
      
      raise_pen();
      moveToPointAcc(x1,y);
      
      while(x2 <= x_end){
        if(printAborted==true){
          break;
        }
        x2+=c_step;
        
        int dist = distance(x2,y,0,0);
        
        if(dist<thresh){
          circle1 = true;
        }else{
          circle1 = false;
        }
        if(dist<thresh*0.3){
          circle2 = true;
        }else{
          circle2 = false;
        }
        
        if(hit==true && circle1==false && circle2==false || hit==true && circle1==true && circle2==true){

          float a1 = atan2(x1,y);
          float a2 = atan2(x2,y);
          int dist1 = distance(x1,y,0,0);
          int dist2 = distance(x2,y,0,0);
          int rot_x1 = sin(a1+ang_off)*dist1;
          int rot_y1 = cos(a1+ang_off)*dist1;
          int rot_x2 = sin(a2+ang_off)*dist2;
          int rot_y2 = cos(a2+ang_off)*dist2;
          
          plotLineDash(rot_x1,rot_y1,rot_x2,rot_y2,i,t);
          x1 = x2;
          hit = false;
        }else 
        if(hit==false && circle1==true && circle2==false){
          plotLineDash(x1,y,x2,y,i,t);
          x1 = x2;
          hit = true;
        }
      }
      plotLineDash(x1,y,x_end,y,i,t);
      raise_pen();
      x1 = x2;
  }
  // resetting new variables for second half
  depth = 5;
  t= -0.25;
  for(int i=0;i<depth;i++){
    frq[i] = random(1,10)/1000.00;
    amp[i] = random(1,20)/100.00;
  }
  
  for(int i=horizon; i<n; i++){
      if(printAborted==true){
        break;
      }
      bool hit = false;
      bool circle1 = false;
      bool circle2 = false;
      
      int x_start = -width/2+margin;
      int x_end = x_start+w;
      
      int y = -height/2+margin+i*space;

      int x1 = x_start;
      int x2 = x_start;

      int ang_off = TWO_PI*0.17;
      count = 0;
      squash = 3;
      
      raise_pen();
      moveToPointAcc(x1,y);
      
      while(x2 <= x_end){
        if(printAborted==true){
          break;
        }
        x2++;
        
        int dist = distance(x2,y,0,0);
        
        if(dist<thresh){
          circle1 = true;
        }else{
          circle1 = false;
        }
        if(dist<thresh*0.3){
          circle2 = true;
        }else{
          circle2 = false;
        }
        
        if(hit==true && circle1==false && circle2==false || hit==true && circle1==true && circle2==true){
          float a1 = atan2(x1,y);
          float a2 = atan2(x2,y);
          int dist1 = distance(x1,y,0,0);
          int dist2 = distance(x2,y,0,0);
          int rot_x1 = sin(a1+ang_off)*dist1;
          int rot_y1 = cos(a1+ang_off)*dist1;
          int rot_x2 = sin(a2+ang_off)*dist2;
          int rot_y2 = cos(a2+ang_off)*dist2;
          
          plotLineDash(rot_x1,rot_y1,rot_x2,rot_y2,i,t);
          x1 = x2;
          hit = false;
        }else 
        if(hit==false && circle1==true && circle2==false){
          plotLineDash(x1,y,x2,y,i,t);
          x1 = x2;
          hit = true;
        }
      }
      
      plotLineDash(x1,y,x_end,y,i,t);
      raise_pen();
      x1 = x2;
  }

  returnToHome();
}

float distance(int X1,int Y1,int X2,int Y2){
  int x_diff = X1-X2;
  int y_diff = Y1-Y2;
  return sqrt(pow(x_diff,2)+pow(y_diff,2));
}


void loop() {

}
