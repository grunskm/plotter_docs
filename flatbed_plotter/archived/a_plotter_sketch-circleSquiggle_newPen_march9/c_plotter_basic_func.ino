//
//void perimeter(){
//  int len = 100;
//  
//  moveToPoint(0,0); 
//  
//  moveToPoint(0,height-len);
//  lower_pen();
//  moveToPoint(0,height);
//  moveToPoint(len,height);  
//  raise_pen();
//  
//  moveToPoint(width-len,height);
//  lower_pen();
//  moveToPoint(width,height);
//  moveToPoint(width,height-len);
//  raise_pen();
//  
//  moveToPoint(width,len); 
//  lower_pen();
//  moveToPoint(width,0);
//  moveToPoint(width-len,0);
//  raise_pen();
//
//  
//  moveToPoint(len,0);
//  lower_pen();
//  moveToPoint(0,0);
//  moveToPoint(0,len);
//  raise_pen();
//
//  moveToPoint(0,0);  
//}

void inLineLine(int X1, int Y1, int X2, int Y2){
  moveToPoint(X1,Y1,50);
  
  int xdiff  = X2-X1;
  int ydiff  = Y2-X1;

  float dist = sqrt(pow(X1-X2,2)+pow(Y1-Y2,2));

  float xstep = xdiff/dist;
  float ystep = ystep/dist;
  
  for( int k=0; k<dist; k++){
    moveToPoint(X1+(xstep*k),Y1+(ystep*k),50);
  }
  moveToPoint(X2,Y2,50);
}

void plotLine(int X1,int Y1,int X2,int Y2){
  moveToPoint(X1,Y1,50);
  //toggle_pen();

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
    moveToPoint(X1+(x_space*s),Y1+(y_space*s),50);
  }
  moveToPoint(X2,Y2,50);
  //toggle_pen();
}

void moveToPoint(int X,int Y, int M){
    int MIN = 400;
    int MAX = M;
    float acc = 1.0025;
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,LOW);
    }else{
      digitalWrite(x_dir,HIGH);
    }
    float v = MIN;
    int c = 0;
    for(int q=0;q<x_distance;q++){
      if( q<(x_distance/2) && v>MAX){
        c++;
        v /= acc;
      }else if(q>=(x_distance-c) && v<MIN){
        v *= acc;
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
    v = MIN;
    c = 0;
    for(int q=0;q<y_distance;q++){
      if(q<(y_distance/2) && v>MAX){
        c++;
        v /= acc;
      }else if(q >=(y_distance-c) && v<MIN){
        v *= acc;
      }
      stepPen(y_step,v);
    }
}



void returnToHome(){
  raise_pen();
  moveToPoint(0,0,50);
}

void raise_pen(){
  servo.write(115);
  pen_engaged = false;
  delay(75);
}
void lower_pen(){
  servo.write(155);
  pen_engaged = true;
  delay(75);
}

void toggle_pen(){
  if(pen_engaged==false){
    lower_pen();
  }else{
    raise_pen();
  }
}

void stepPen(int pin, int s){
    abortCheck();
    digitalWrite(pin, HIGH);
    delayMicroseconds(s);
    digitalWrite(pin, LOW);
    delayMicroseconds(s);
}

void abortCheck(){
   buttonState = digitalRead(buttonPin);
   if (buttonState == HIGH) {
   printAborted = true;
  }
}
