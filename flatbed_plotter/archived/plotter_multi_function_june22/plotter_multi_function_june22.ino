
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

int width = 16000; //X-axis (rail)
int height = 13000; //Y-axis (board)
//int x_margin = width*0.1;
//int y_margin = height*0.1;

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
//
  int red = 0;
  for(int q=0;q<10;q++){
    random(0,15);
  }

  perimeter();

   for(int e = 1; e<10; e++){
    float x_margin = width*(e*0.1);
    float y_margin = height*(e*0.1);

    int w = width-(x_margin*2);
    int h = height-(y_margin*2);
  
    int xnum = 5;
    int ynum = 5;
    int xspace = w/xnum;
    int yspace = h/ynum;
    
    for(int i=0;i<=xnum;i++){
      plotLine(i*xspace+x_margin,y_margin,i*xspace+x_margin,h+y_margin);
      if(printAborted==true){
        break;
      }
    }
    for(int i=0;i<=ynum;i++){
      plotLine(x_margin,i*yspace+y_margin,w+x_margin,i*yspace+y_margin);
      if(printAborted==true){
        break;
      }
    }
    
    for(int q=0; q<10; q++){
      
      int x = random(x_margin,width-x_margin);
      int y = random(y_margin,height-y_margin);
      
      int sz = 50-(e*5)+5;
      
      for(int i=0; i<sz; i++){
        
        int ww = i*50+50;
        int hh = ww;
        ellipse(x,y,ww,hh);
        if(printAborted==true){
          break;
        }
      }
      if(printAborted==true){
        break;
      }
    }
    if(printAborted==true){
      break;
    }
  }
  
  
//for(int q=0; q<10;q++){
//  
//  int x = floor(random(0,xnum))*xspace+margin;
//  int y = floor(random(0,ynum))*yspace+margin;
//  for(int z=1;z<25;z++){
//    ellipse(x,y,z*xspace/20/2,z*xspace/20/2);
//  }
//}
//  for(int t=0;t<10;t++){
//    randomSquiggleSmooth(width*0.1,width*0.9,height*0.1,height*0.9,1000);
//  }
  

  returnToHome();
}


void loop() {

}
