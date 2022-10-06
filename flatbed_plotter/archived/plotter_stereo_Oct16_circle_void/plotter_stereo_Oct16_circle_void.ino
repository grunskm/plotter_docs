
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

struct circleData
{
  int _x;
  int _y;
  int _z;
  int _w;
};

struct pointData
{
  int x;
  int y;
  int z;
};

//max width: 32000
//max height: 28000

long width = 10000; //X-axis (rail)
int height = 5000; //Y-axis (board)

int x1; 
int y1;

float s1 = 0.034;
float s2 = 0.167;
float s3 = 0.278;
float s4 = 0.124;
float s5 = 0.065;
float s6 = 0.173;
float s7 = 0.113;
float s8 = 0.187;

//float scale = 0.00025;//usual setting
float scale = 0.00025;
int space = 2500;
int seed = 0;

const int points = 15;
struct pointData point[points];

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
  
  for(int i=0; i<points; i++){
    int tx = random(-space,space);
    int ty = random(-space,space);
    int tz = random(0,space);
    
    point[i].x = tx;
    point[i].y = ty;
    point[i].z = tz;

  }

  perimeter(0,0,width,height);
  
  stereoView(width*0.3,height*0.5,-500);
  stereoView(width*0.7,height*0.5,500);
  
  returnToHome();
}

void stereoView(int X,int Y, int OFF){
  //perimeter(X,Y,W,W);
  raise_pen();
  for(int i=0; i<(points-1);i++){
    if(printAborted==false){
      drawLineOcc3d(
      X,
      Y,
      point[i].x+OFF,
      point[i].y,
      point[i].z,
      point[i+1].x+OFF,
      point[i+1].y,
      point[i+1].z
      ); 
    }    
  }
}

void drawLineOcc3d(int X, int Y,int X1,int Y1,int Z1,int X2,int Y2,int Z2){
  raise_pen();
  
  int xDiff = X2-X1;
  int yDiff = Y2-Y1;
  int zDiff = Z2-Z1;

  float xyHyp = sqrt(pow(xDiff,2.00)+pow(yDiff,2.00));
  float xyzHyp = sqrt(pow(xyHyp,2.00)+pow(zDiff,2.00))/2;

  float xStep = xDiff/xyzHyp;
  float yStep = yDiff/xyzHyp;
  float zStep = zDiff/xyzHyp;

  float temp_x = X1;
  float temp_y = Y1;
  float temp_z = Z1;

  for(int f=0; f<xyzHyp; f++){
    if(printAborted==false){

      temp_x += xStep;
      temp_y += yStep;
      temp_z += zStep;

      float s = 1.00000/(1.00000+temp_z*scale);

      int line_x = X+temp_x*s;
      int line_y = Y+temp_y*s;

      if(f==0){
        moveToPointAcc(line_x, line_y);
        lower_pen();
      }else{
        moveToPointAcc(line_x, line_y); 
      }
      
    }
  }
  float s = 1.00000/(1.00000+Z2*scale);
  int line_x = X+X2*s;
  int line_y = Y+Y2*s;
  moveToPointAcc(line_x, line_y); 
  raise_pen();
}




void movingSquiggle(int X,int Y,int SPACE, float N, int S){
      int wid = SPACE*0.4;
      int posX = X;
      int posY = Y;
      float scale = S;
      int space = SPACE;
  
     for(int h=0;h<100;h++){
      if(printAborted==false){

        float sz = h;//wid;//*(sin((h+seed)*s2)+cos((h+seed)*s5)+sin((h+seed)*s3)+cos((h+seed)*s8))/4.00;
        
        float s = 1/(1+sz*scale);
        
        float sx = wid*(sin((h+seed)*s1+N)+cos((h+seed)*s2+N)+sin((h+seed)*s3+N)+cos((h+seed)*s4+N))/4.00*s;
        float sy = wid*(cos((h+seed)*s5+N)+sin((h+seed)*s6+N)+cos((h+seed)*s7+N)+sin((h+seed)*s8+N))/4.00*s;

//        float temp_dist = sqrt(pow(sx,2)+pow(sz,2));
//        float temp_ang = atan2(sx,sz)+r_angle;
//        
//        sx = sin(temp_ang)*temp_dist;
//        sz = cos(temp_ang)*temp_dist;
       
        int x2 = (sx)+posX+(space/2);
        int y2 = (sy)+posY+(space/2);
        if(h==0){
          moveToPointAcc(x2,y2);
          toggle_pen();
          x1 = x2;
          y1 = y2;
        }
        plotLineCont(x1,y1,x2,y2);
        x1 = x2;
        y1 = y2;
      }
     }
     raise_pen();
}

void cross(int X, int Y, int L){
  if(printAborted==false){
    plotLine(X+L,Y,X-L,Y);
    plotLine(X,Y+L,X,Y-L);
  }
}


void loop() {

}
