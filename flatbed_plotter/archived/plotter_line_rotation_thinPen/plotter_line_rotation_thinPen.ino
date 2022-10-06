
#include <Servo.h>

#define x_step 4
#define x_dir 5
#define y_step 2
#define y_dir 3


Servo servo;
bool pen_engaged;

int pen_x = 0;
int pen_y = 0;

int width = 28000;
int height = 32000;


void setup() {
  Serial.begin(9600);

  servo.attach(9);
  servo.write(150);
  pen_engaged = false;

  pinMode(x_step, OUTPUT);
  pinMode(x_dir, OUTPUT);
  pinMode(y_step, OUTPUT);
  pinMode(y_dir, OUTPUT);

  toggle_pen();
  delay(1000);
  toggle_pen();
  delay(1000);
  toggle_pen();
  delay(1000);
  toggle_pen();
  delay(5000);

  lineRotation();
  moveToPointAcc(0,0);
}

void loop() {

}

void randomLine(){
    for(int i=0;i<100;i++){
    int y = random(0,width);
    int x = random(0,height);
    int y_2 = random(0,width);
    int x_2 = random(0,height);
    plotLine(x,y,x_2,y_2);
  }
}

void countToFive(){
//    for(int g=0;g<20;g++){
//    for(int h=0; h<20; h++){
//      int x = h*(xsp*2);
//      int y = g*ysp;
//      for(int t=0; t<4; t++){
//        plotLine(x+(200*t),y+200,x+(200*t),y-200);
//      }
//      plotLine(x-150,y-100,x+750,y+100);
//    }
//  }
}

void lineRotation(){
  float a = TWO_PI/360; 

  int count = 0;
  
  int sp = height/120;
  int r = sp*0.3;
  
  for(int d=0;d<90;d++){
    for(int f=0;f<120;f++){
      count++;
      int xr = sin(a*pow(d*f,2)/50)*r;
      int yr = cos(a*pow(d*f,2)/50)*r;
      int x = f*sp;
      int y = d*sp;
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
  moveToPointAcc(X1,Y1);
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

void moveToPointAcc(int X,int Y){
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,HIGH);
    }else{
      digitalWrite(x_dir,LOW);
    }
    int v = 500;
    int c = 0;
    for(int q=0;q<x_distance;q++){
      if(q<x_distance/2 && v>50){
        c++;
        v-=1;
      }else if(q>=(x_distance-c) && v<500){
        v+=1;
      }
      stepPen(x_step,v);
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
    v = 500;
    c = 0;
    for(int q=0;q<y_distance;q++){
      if(q<(y_distance/2) && v>50){
        c++;
        v -= 1;
      }else if(y_distance-q<=c && v<500){
        v += 1;
      }
      stepPen(y_step,v);
    }
}

void moveToPoint(int X,int Y){
    int sp = 200;
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
      stepPen(x_step,sp);
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
      stepPen(y_step,sp);
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

void stepPen(int pin, int s){
    digitalWrite(pin, HIGH);
    delayMicroseconds(s);
    digitalWrite(pin, LOW);
    delayMicroseconds(s);
}
