
#include <Servo.h>

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3


Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;

int width = 25000;


void setup() {
  Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  lineRotation();
  moveToPoint(-1000,-1000);
}

void loop() {

}

void lineRotation(){
  float a = TWO_PI/320; 
  int r = width/280;
  int count = 0;
  
  int x_sp = width/80;
  int y_sp = width/80;
  
  for(int d=0;d<80;d++){
    for(int f=0;f<80;f++){
      count++;
      int xr = sin(a*(d*f))*r;
      int yr = cos(a*(d*f))*r;
      int x = f*x_sp;
      int y = d*y_sp;
      plotLine(x+xr,y+yr,x-xr,y-yr); 
    }
  }
  
}

void asterisk(){
  float a = TWO_PI/6; 
  int r = 200;
  
  int x_sp = width/50;
  int y_sp = width/50;
  
  for(int d=0;d<50;d++){
    for(int f=0;f<50;f++){
      for(int h=0; h<3; h++){
        int xr = sin(a*h)*r;
        int yr = cos(a*h)*r;
        int x = f*x_sp;
        int y = d*y_sp;
        plotLine(x+xr,y+yr,x-xr,y-yr); 
      }
    }
  }
}

void plotLine(int X1,int Y1,int X2,int Y2){
  moveToPoint(X1,Y1);
  toggle_pen();

  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(X1-X2,2)+pow(Y1-Y2,2));
  //float hypo = sqrt(pow((xdiff+ydiff),2))/2;
  //Serial.println(hypo);
  float x_space = xdiff/hypo;
  //Serial.println(x_space);
  float y_space = ydiff/hypo;
  //Serial.println(y_space);

  
  for(int s=1; s<hypo; s++){
    moveToPoint(X1+(x_space*s),Y1+(y_space*s));
  }
  moveToPoint(X2,Y2);
  toggle_pen();
}

void moveToPoint(int X,int Y){
  
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,HIGH);
    }else{
      digitalWrite(x_dir,LOW);
    }
    for(int q=0;q<x_distance;q++){
      stepPen(x_step,200);
    }
    
    int target_y = Y;
    int y_diff = pen_y-target_y;
    int y_distance = sqrt(pow(pen_y-target_y,2));
    pen_y = target_y;
    
    if(y_diff>0){
      digitalWrite(y_dir,HIGH);
    }else{
      digitalWrite(y_dir,LOW);
    }
    for(int q=0;q<y_distance;q++){
      stepPen(y_step,200);
    }
}

void toggle_pen(){
  if(pen_engaged==false){
    servo.write(180);
    pen_engaged = true;
  }else{
    servo.write(150);
    pen_engaged = false;
  }
  delay(100);
}

void stepPen(int pin, int sp){
    digitalWrite(pin, HIGH);
    delayMicroseconds(sp);
    digitalWrite(pin, LOW);
    delayMicroseconds(sp);
}
