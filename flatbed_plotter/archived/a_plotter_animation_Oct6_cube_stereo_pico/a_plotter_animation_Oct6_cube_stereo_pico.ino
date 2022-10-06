
#include <Servo.h>

#define x_step 10
#define x_dir 11
#define y_step 13
#define y_dir 12

const int buttonPin = 14;
int buttonState = 0;
bool printAborted = false;

Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;

struct pointData
{
  int _x;
  int _y;
  int _z;
  int _w;
};

//max width: 32000
//max height: 28000

long width = 27000; //X-axis (rail)
int height = 27000; //Y-axis (board)

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

float scale = 0.00025;//usual setting
//float scale = 0.00015;
int space = 5000;
int seed = 0;

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

  //perimeter(0,0,width,height);
  int wid = space*0.4;
  int x_num = width/space;
  int y_num = height/space;
  int nnn = 0;
  
  float r_step = TWO_PI/64;
  float r_angle = 0+(33*r_step);

  int posX = space;
  int posY = space/2;
  
  perimeter(1000-200,1000-200,space*2+200,space+200);
  r_angle += r_step;
  
  cube3D(1000+0,1000,wid,r_angle, -space*0.02);
  cube3D(1000+space,1000,wid,r_angle, space*0.02);
  
  returnToHome();
}

void cube3D(int X,int Y,int W,float N, int OFF){
  int dim = 3;
  int n = 0;
  struct pointData point[64];
  
  for(int j=0; j<=dim; j++){
      for(int k=0; k<=dim; k++){
          for(int l=0; l<=dim; l++){
            
            if(printAborted==false){
              
              int z = j * (W/dim) - (W*0.5); 
              int x = k * (W/dim) - (W*0.5);
              int y = l * (W/dim) - (W*0.5);
  
              float temp_dist = sqrt(pow(x,2)+pow(z,2));
              float temp_ang = atan2(x,z)+(sin(N)+1);
        
              x = sin(temp_ang)*temp_dist;
              z = cos(temp_ang)*temp_dist;
  
              temp_dist = sqrt(pow(y,2)+pow(z,2));
              temp_ang = atan2(y,z)+(0.66);
        
              y = sin(temp_ang)*temp_dist;
              z = cos(temp_ang)*temp_dist;

              temp_dist = sqrt(pow(y,2)+pow(x,2));
              temp_ang = atan2(y,x)+0.25;
        
              y = sin(temp_ang)*temp_dist;
              x = cos(temp_ang)*temp_dist;

              float s = 1/(1+(z*scale));

              x = (OFF+x)*s+(space/2)+X;
              y = y*s+(space/2)+Y;
  
              int w = (W*0.075)*s;
  
              point[n]._x = x;
              point[n]._y = y;
              point[n]._z = z;
              point[n]._w = w;
             
             // ellipse(X+x,Y+y,w,w);
              n++;
            }else{
            break;
         }
      }
    }
  }
  n=0;
  for(int j=0; j<=dim; j++){
      for(int k=0; k<=dim; k++){
          for(int l=0; l<=dim; l++){
            if(printAborted==false){
              
              raise_pen();
              
              int w = point[n]._w;
              int y = point[n]._y;
              int x = point[n]._x;
              int z = point[n]._z;

              int occ_count = 0;
              int occ[64];

              for(int t=0;t<64;t++){
                if(point[t]._z<z){

                  int Xdiff = x-point[t]._x;
                  int Ydiff = y-point[t]._y;
                  int point_hyp = sqrt(pow(Xdiff,2)+pow(Ydiff,2));
                  int thresh = point[t]._w + w;

                  if(point_hyp<thresh){
                      occ[occ_count] = t;
                      occ_count++;
                    } 
                  }
                }
              
              //ellipse(x,y,w,w); 

              int steps = PI*(w*2);
              float a = TWO_PI/steps;
              bool hit = false;
              
              for(int g=0;g<steps;g++){
                
                float cir_x = x+sin(a*g)*w;
                float cir_y = y+cos(a*g)*w;
                if(g==0){
                  moveToPointAcc(cir_x,cir_y);
                }

                int hit_count = 0;

                for(int m=0;m<occ_count;m++){
                  int Xdiff = cir_x-point[occ[m]]._x;
                  int Ydiff = cir_y-point[occ[m]]._y;
                  int point_hyp = sqrt(pow(Xdiff,2)+pow(Ydiff,2));

                  if(point_hyp<point[occ[m]]._w){
                    hit_count++;
                  }
                  if(hit_count!=0){
                   hit = true; 
                  }else{
                   hit = false;
                  }
                }
                
                if(hit==true && pen_engaged == true){
                  raise_pen();
                }else if(hit==false && pen_engaged == false){
                  lower_pen();
                }
                
                moveToPoint(cir_x,cir_y,150);
                
              }
              
              n++;

            }else{
              break;
            }
          }
      }
  }
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
