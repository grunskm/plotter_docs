
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

int width = 20000; //X-axis (rail)
int height = 20000; //Y-axis (board)

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

  for(int w=0;w<100;w++){
    int k = random();
  }

  //perimeter();
  
  int section_w = 5000;
  int y_spacing = 50;
  int x_spacing = 5;

  int grid_w = (width/section_w)-1;
  int grid_h = (height/section_w)-1;
  
  int h_space = section_w/y_spacing;
  int w_space = section_w/x_spacing; 

  for(int t=0;t<3;t++){
    for(int q=0;q<3;q++){
      if(printAborted==false){
        int x = q*5000;
        int y = t*5000;
        
        float f1 = random(300.00,400.00);
        float f2 = random(250.00,350.00);
        float f3 = random(200.00,300.00);

        Serial.println(f1);
        Serial.println(f2);
        Serial.println(f3);
        Serial.println("------");
  
        int saved_x;
        
        raise_pen();
        moveToPointAcc(x,y);
        
  
        for(int e=0; e<h_space; e++){
          for(int i=0; i<w_space; i++){
            if(printAborted==false){
              int n = (i*x_spacing)+(e*w_space);

              float thresh = sin((e+i)/1000)*0.75;
              
              float frqA = sin(n/f1);
              float frqB = sin(n/f2);
              float frqC = sin(n/f3);
  
              float mod = (frqA+frqB+frqC)/3;
  
              int dash_x = x+(i*x_spacing);
              int dash_y = y+(e*y_spacing);
             
              if(mod>=thresh && pen_engaged == false){ //pen should be down when mod is greater than 0
                if(dash_x < saved_x){ 
                  lower_pen();
                  moveToPointAcc(x+section_w,dash_y-y_spacing);//move to end of line
                  raise_pen();
                  moveToPointAcc(x,dash_y);
                  lower_pen();
                  moveToPointAcc(dash_x,dash_y);
                }else{
                  lower_pen();
                  moveToPointAcc(dash_x,dash_y);
                  saved_x = dash_x;
                }
              }else 
              if(mod<thresh && pen_engaged == true){// pen up when mod less than 0
                raise_pen();
                moveToPointAcc(dash_x,dash_y);
                saved_x = dash_x;
              }
            }else{
              break;
            }
          }
        }
      }
    }
  }
  returnToHome();

  
//
//  for(int e=0; e<h_space; e++){
//    for(int i=0; i<width; i++){
//      if(printAborted==false){
//        
//        int n = (i+(e*width));
//        
//        float frqA = sin(n/100.00);
//        float frqB = sin(n/67.00);
//        float frqC = sin(n/29.00);
//
//        float mod = frqA+frqB+frqC;
//        
//        int x = i+8000;
//        int y = e*weight+11000;
//        //ellipse(x,y,500,500);
//        if(i==0 && pen_engaged == true){
//          raise_pen();
//          moveToPointAcc(x,y);
//        }else 
//        if(i==0){
//          moveToPointAcc(x,y);
//        }
//       
//        if(i>0 && mod>=0 && pen_engaged == false){
//          lower_pen();
//          moveToPointAcc(x,y);
//          }else 
//        if(i>0 && mod<0 && pen_engaged == true){
//          raise_pen();
//          moveToPointAcc(x,y);
//          }
//        }else{
//          break;
//        }
 //   }
//  }
//
//  

}


void loop() {

}
