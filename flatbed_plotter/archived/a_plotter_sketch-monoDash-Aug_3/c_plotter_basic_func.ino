void plotLineDashed(int X1,int Y1,int X2,int Y2, int I, int N){
  moveToPointAccDraw(X1,Y1);
  if(I==0){
    toggle_pen();
  }
  if(pen_engaged==true){
    servo.write(145);
    delay(100);
  }

  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(xdiff,2)+pow(ydiff,2));

  float x_space = xdiff/hypo;

  float y_space = ydiff/hypo;

  for(int s=1; s<hypo; s++){
    count++;    
    int X = X1+(x_space*s);
    int Y = Y1+(y_space*s);

    int xcenter = X-(width/2);
    int ycenter = Y-(height/2);
    float dist = sqrt(pow(xcenter,2.00)+pow(ycenter,2.00));
    int dash;
    if(I<(N/2)){
      dash = (height*0.8)/28;
    }else{
      dash = map(dist,0,height*0.5,50,2000);
    }
    
  //  Serial.println(dist);
    if(in_circle1 == false && dist<height*0.35){
      toggle_pen();
      in_circle1 = true;
    }else if(in_circle1 == true && dist>height*0.35){
      toggle_pen();
      in_circle1 = false;
    }
    if(in_circle2 == false && dist<height*0.15){
      toggle_pen();
      in_circle2 = true;
    }else if(in_circle2 == true && dist>height*0.15){
      toggle_pen();
      in_circle2 = false;
    }
    
    if(count >= dash){
      toggle_pen();
      count=0;
    }
    if(X<width+1 && X>=0 && Y<height+1 && Y>=0 && printAborted==false){
      moveToPointAccDraw(X,Y);
    }else{
      break;
    }
  }
  if(pen_engaged==true){
    servo.write(120);
    delay(100);
  }
}

void plotLineCont(int X1,int Y1,int X2,int Y2){
  moveToPointAcc(X1,Y1);

  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(xdiff,2)+pow(ydiff,2));

  float x_space = xdiff/hypo;

  float y_space = ydiff/hypo;

  for(int s=1; s<hypo; s++){
    int X = X1+(x_space*s);
    int Y = Y1+(y_space*s);
    if(X<width+1 && X>=0 && Y<height+1 && Y>=0 && printAborted==false){
      moveToPointAccDraw(X,Y);
    }else{
      break;
    }
  }
}

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
      moveToPointAccDraw(X,Y);
    }else{
      break;
      raise_pen();
    }
  }
  toggle_pen();
}

void moveToPointAccDraw(int X,int Y){
    int MIN = 200;
    int MAX = 50;
    
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

void moveToPointAcc(int X,int Y){
    int MIN = 600;
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

void moveToPoint(int X,int Y, int S){
  if(X<width+1 && X>=0 && Y<height+1 && Y>=0){
    int sp = S;
    int target_x = X;
    int x_diff = pen_x-target_x;
    int x_distance = sqrt(pow(pen_x-target_x,2));
    pen_x = target_x;
    if(x_diff>0){
      digitalWrite(x_dir,LOW);
    }else{
      digitalWrite(x_dir,HIGH);
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
}


void returnToHome(){
  raise_pen();
  moveToPointAcc(0,0);
}

void raise_pen(){
  servo.write(120);
  pen_engaged = false;
  delay(50);
}
void lower_pen(){
  servo.write(145);
  pen_engaged = true;
  delay(50);
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
