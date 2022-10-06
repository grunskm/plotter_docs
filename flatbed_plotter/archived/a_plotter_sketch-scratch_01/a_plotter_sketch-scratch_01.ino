
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

// max width: 32000
// max height: 28000

int width = 28000; //X-axis (rail)
int height = 24000; //Y-axis (board)
int count = 0;

void setup() {
  connection_setup();
  perimeter();

  int w = width*0.7;
  int h = height*0.05;
  int m = (width-w)/2;

  scratch(m+(w/2),height*0.25,w,h);
  scratch(m+(w/2),height*0.5,w,h);
  scratch(m+(w/2),height*0.75,w,h);
  
  returnToHome();
}



void scratch(int X,int Y, int W, int H){
    count = 0;
    while(count<5000 && printAborted==false){

    float inc = count*0.05;
    
    float x_off = (W*0.1)*(sin(count*0.031)+sin(count*0.071)+sin(count*0.017)+sin(count*0.0024))/4.000;
    
    float y_off = H*(sin(count*0.017)+cos(count*0.021)+sin(count*0.012)+sin(count*0.0133))/4.000;
    
    
    
    int x = X+sin(inc)*((W/2)+(x_off));
    int y = Y+(cos(inc*2.00))*H+y_off;

    if(count==0){
      raise_pen();
      moveToPointAcc(x,y);
      lower_pen();
    }else{
      plotLineCont(pen_x,pen_y,x,y);
    }
    count++;
  }
}


void loop() {

}
