

void plotLine(int X1,int Y1,int X2,int Y2){
  moveToPointAcc(X1,Y1);
  toggle_pen();

  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(xdiff,2)+pow(ydiff,2));


  float x_space = xdiff/hypo;

  float y_space = ydiff/hypo;

  for(int s=1; s<hypo; s++){
    int X = X1+(x_space*s);
    int Y = Y1+(y_space*s);
    if(X<width+1 && X>=0 && Y<height+1 && Y>=0 && printAborted==false){
      moveToPointDraw(X,Y);
    }else{
      break;
      raise_pen();
    }
  }
  toggle_pen();
}


void moveToPointDraw(int X,int Y){
    int MIN = 400;
    int MAX = 50;
    float acc = 1.005;
    
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,LOW);
    }else{
      digitalWrite(x_dir,HIGH);
    }
    int v = MIN;
    int c = 0;
    for(int q=0;q<x_distance;q++){
      if( q<(x_distance/2) && v>MAX){
        c++;
        v/=acc;
      }else if(q>=(x_distance-c) && v<MIN){
        v*=acc;
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


void moveToPointAcc(int X,int Y){
    int MIN = 500;
    int MAX = 100;
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,LOW);
    }else{
      digitalWrite(x_dir,HIGH);
    }
    int v = MIN;
    int c = 0;
    for(int q=0;q<x_distance;q++){
      if( q<(x_distance/2) && v>MAX){
        c++;
        v-=1;
      }else if(q>=(x_distance-c) && v<MIN){
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
    v = MIN;
    c = 0;
    for(int q=0;q<y_distance;q++){
      if(q<(y_distance/2) && v>MAX){
        c++;
        v -= 1;
      }else if(q >=(y_distance-c) && v<MIN){
        v += 1;
      }
      stepPen(y_step,v);
    }
}

void moveToPoint(int X,int Y, int MIN, int MAX){
//    int MIN = 500;
//    int MAX = 100;
    float acc = 1.005;
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

void perimeter(){
  int len = 100;
  
  moveToPointAcc(0,0); 
  
  moveToPoint(0,height-len,500,50);
  lower_pen();
  moveToPointAcc(0,height);
  moveToPointAcc(len,height);  
  raise_pen();
  
  moveToPoint(width-len,height,500,50);
  lower_pen();
  moveToPointAcc(width,height);
  moveToPointAcc(width,height-len);
  raise_pen();
  
  moveToPoint(width,len,500,50); 
  lower_pen();
  moveToPointAcc(width,0);
  moveToPointAcc(width-len,0);
  raise_pen();

  
  moveToPoint(len,0,500,50);
  lower_pen();
  moveToPointAcc(0,0);
  moveToPointAcc(0,len);
  raise_pen();

  moveToPointAcc(0,0);  
}

void returnToHome(){
  raise_pen();
  moveToPointAcc(0,0);
}

void toggle_pen(){
  if(pen_engaged==false){
    lower_pen();
  }else{
    raise_pen();
  }
}

void raise_pen(){
  servo.write(110);
  pen_engaged = false;
  delay(100);
}

void lower_pen(){
  servo.write(155);
  pen_engaged = true;
  delay(100);
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
