
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
bool hit = false;
bool in_circle1 = false;
bool in_circle2 = false;

// max width: 32000
// max height: 28000

int width = 5000; //X-axis (rail)
int height = 5000; //Y-axis (board)

int count = 0;

void setup() {
 // Serial.begin(9600);

  servo.attach(9);
  raise_pen();
  delay(2000);

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  pinMode(buttonPin, INPUT);

  perimeter(-width/2, -height/2, width, height);

  int w = width*0.8;
  int margin = (height-w)/2;
  int h = height-(margin*2);

  int space = 40;
  int n = h/space;

  //ellipse(0,0,1500,1500);

  for(int i=0; i<n; i++){
    if(printAborted==false){
      int x_start = -width/2+margin;
      int x_end = x_start+w;
      
      int y = -height/2+margin+i*space;

      int x1 = x_start;
      int x2 = x_start;

      int thresh = 1500;
      int ang_off = TWO_PI*0.7;
      
      raise_pen();
      moveToPointAcc(x1,y);
      
      while(hit == false){
        x2++;
        int dist = distance(x2,y,0,0);
        if(x2 >= x_end){
          break;
        }else if(dist<thresh){
          hit = true;
          plotLineDash(x1,y,x2,y,w,space);
          x1 = x2;
        }
      }
      
      while(hit == true){
        x2++;
        int dist = distance(x2,y,0,0);
        
        if(dist>thresh){
          hit = false;

          float a1 = atan2(x1,y);
          float a2 = atan2(x2,y);
          
          int rot_x1 = sin(a1+ang_off)*dist;
          int rot_y1 = cos(a1+ang_off)*dist;

          int rot_x2 = sin(a2+ang_off)*dist;
          int rot_y2 = cos(a2+ang_off)*dist;
          
          plotLineDash(rot_x1,rot_y1,rot_x2,rot_y2,w,space);
          x1 = x2;
        }
      }
      
      plotLineDash(x1,y,x_end,y,w,space);
    }
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
