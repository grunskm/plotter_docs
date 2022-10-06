
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

int width = 32000; //X-axis (rail)
int height = 28000; //Y-axis (board)
int count = 0;

void setup() {
  connection_setup();
  //perimeter();

  for(int q=0;q<10;q++){
    int do_nothing = random(0,1);
  }

  int h = height*0.2;
  int w = width*0.01;
  int m = (height-h)/2;
  
  for(int i = 0;i<5;i++){
    scratch(random(m+w,width-m-w),random(m+h/2,height-m+h/2),w,h);
  }
  //scratch(width*0.25,m+(h/2),w,h);
//  scratch(width*0.5,m+(h/2),w,h);
//  scratch(width*0.75,m+(h/2),w,h);
  
  returnToHome();
}



void scratch(int X,int Y, int W, int H){
    count = 0;
    
    while(count<1000 && printAborted==false){

    float inc = count*0.05;
    
    float y_off = (H*0.1)*(sin(count*0.031)+sin(count*0.071)+sin(count*0.017)+sin(count*0.0024))/4.000;
    
    float x_off = W*(sin(count*0.017)+cos(count*0.021)+sin(count*0.012)+sin(count*0.0133))/4.000;
    
    
    
    int y = Y+sin(inc)*((H/2)+(y_off));
    int x = X+(cos(inc*2.00))*W+x_off;

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
