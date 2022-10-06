


bool collideCircle(int X, int Y,int CIR_X,int CIR_Y,int CIR_R, float SQUASH){

  int x_diff = CIR_X-X;
  int y_diff = CIR_Y-Y;

  int x_space = sqrt(pow(CIR_R,2)-pow(y_diff,2))*SQUASH;

  int x_min = CIR_X-x_space;
  int x_max = CIR_X+x_space;
  
  if( Y>CIR_Y-CIR_R 
   && Y<CIR_Y+CIR_R 
   && X>x_min
   && X<x_max){
    return true;
   }else{
    return false;
   }
}

void dropSquiggle(int Y, int W){

//  float space = height/31.00;
//  
//  for(int i=0;i<30;i++){
//    dropSquiggle(height-((i*space)+(space/2)),space);
//  }
  
  float s1 = 1.00/random(50.00,100.00);
  float s2 = 1.00/random(50.00,200.00);
  float s3 = 1.00/random(100.00,300.00);
  float s4 = 1.00/random(50.00,100.00);
  float s5 = 1.00/random(50.00,200.00);
  float s6 = 1.00/random(100.00,300.00);

  int x1;
  int y1;
  
   for(int h=0;h<width-1000;h++){
    if(printAborted==false){
      float sx = (sin(h*s1)+sin(h*s2)+sin(h*s3))/3.00;
      float sy = (sin(h*s4)+sin(h*s5)+sin(h*s6))/3.00;
      int x2 = (h+1000.00)-((sx+1)*W/2);
      int y2 = Y+(sy*W/2);
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
  toggle_pen();
}

void flower(int X, int Y, int R, int P){
  raise_pen();
  float d = R*0.5;
  int steps = 2*PI*R*d;
  float a = TWO_PI/steps;
  float petals = a*P;
  int s = random(0,steps);
  int seed = random(0,300);
  for(int g=0;g<s;g++){
    if(g==1){
      lower_pen();
    }
    float r = R+sin(g*petals)*d;
    float cir_x = X+sin((a*g)+seed)*r;
    float cir_y = Y+cos((a*g)+seed)*r;
    if(cir_x<width+1 && cir_x>=0 && cir_y<height+1 && cir_y>=0){
      moveToPointAcc(cir_x,cir_y);
    }else{
      break;
    }
  }
  raise_pen();
}

void grass(int X, int Y, int MIN, int MAX){
  int len = random(MIN,MAX);
  int servo_a = 180;
 // int speed1 = 200;
  int grass_x = X;
  int grass_y = Y;
  moveToPointAcc(grass_x,grass_y);
  toggle_pen();
  for(int g=0;g<len;g++){
    int xx = grass_x+pow(g,2)/4000;
    int yy = grass_y-g;
   
    if(X<width+1 && X>=0 && Y<height+1 && Y>=0 && printAborted==false){
      moveToPointAccDraw(xx,yy);
    }else{
      break;
      Serial.println("break");
    }
  }
  toggle_pen();
}

void pixel(int X, int Y){
  int s = 75;
  moveToPointAcc(X,Y);
  toggle_pen();
  moveToPointAcc(X+s,Y);
  moveToPointAcc(X+s,Y+s);
  moveToPointAcc(X,Y+s);
  moveToPointAcc(X,Y);
  toggle_pen();
}

//void arc(int X, int Y, int R){
//  int steps = PI*R*2;
//  float a = TWO_PI/steps;
//  for(int g=0;g<steps;g++){
//    float cir_x = X+sin(a*g)*R;
//    float cir_y = Y+cos(a*g)*R;
//    
//    if(g==0){
//      moveToPointAcc(cir_x,cir_y);
//      toggle_pen();
//    }else{moveToPoint(cir_x,cir_y);}
//  }
//  toggle_pen();
//}

void squiggle(int X,int Y,int LEN, int AMP,int FRQ){

    for(int n=0;n<LEN;n++){
    if(n==1){
      toggle_pen();
    }
    float a  = n*TWO_PI/FRQ;
    float x = X+sin(a)*AMP;
    float y = Y+n;
    moveToPointAcc(x,y);      
    }
    toggle_pen();
}
//
//void rectDashed(int X, int Y, int W, int H, int DASH){
//    if(printAborted==false){
//      moveToPointAcc(X,Y);
//      lower_pen();
//      plotLineDashed(X,Y,X+W,Y,DASH);
//      plotLineDashed(X+W,Y,X+W,Y+H,DASH);
//      plotLineDashed(X+W,Y+H,X,Y+H,DASH);
//      plotLineDashed(X,Y+H,X,Y,DASH);
//      raise_pen();
//      //count=0;
//    }
//
//}

void rect(int X, int Y, int W, int H){
    if(printAborted==false){
      moveToPointAcc(X,Y);
      toggle_pen();  
      plotLine(X,Y,X+W,Y);
      plotLine(X+W,Y,X+W,Y+H);
      plotLine(X+W,Y+H,X,Y+H);
      plotLine(X,Y+H,X,Y);
      toggle_pen();
    }
}

void tally(int X, int Y){
  for(int t=0; t<4; t++){
    plotLine(X+200,Y+(200*t),X-200,Y+(200*t));
  }
  plotLine(X-100,Y-150,X+100,Y-1000);
}

//void ran_circle(int X, int Y, int R ){
//   /// float a = TWO_PI/STEPS;
//  int steps = PI*R*2;
//  float a = TWO_PI/steps;
//  for(int g=0;g<steps;g++){
//    float cir_x = X+sin(a*g)*R;
//    float cir_y = Y+cos(a*g)*R;
//    
//    if(g==0){
//      moveToPointAcc(cir_x,cir_y);
//      toggle_pen();
//    }else{moveToPoint(cir_x,cir_y,100);}
//  }
//  toggle_pen();
//}

void ellipse(int X, int Y, int W, int H){
  int steps = PI*(W+H);
  float a = TWO_PI/steps;
  for(int g=0;g<steps;g++){
    float cir_x = X+sin(a*g)*W;
    float cir_y = Y+cos(a*g)*H;
    
    if(g==0){
      moveToPointAcc(cir_x,cir_y);
      toggle_pen();
    }else{moveToPoint(cir_x,cir_y,150);}
  }
  toggle_pen();
}

void jagged_circle(){
  float a = TWO_PI/45;
for(int e=0;e<10;e++){
  for(int i=0;i<=45;i++){
  float inner_x = (width*0.2)+sin(a*i)*(e*200+100);
  float inner_y = (height*0.2)+cos(a*i)*(e*200+100);
  moveToPointAcc(inner_x,inner_y);
  if(i==0){
    toggle_pen();
  }
  // plotLine(outer_x,outer_y,inner_x,inner_y);
  }
  toggle_pen();
}
}

void randomCross(int x_max,int y_max, int R){
  float a = TWO_PI/360*random(30,330);
  int x = random(2500,x_max);
  int y = random(2500,y_max);
  int x_2 = x+sin(a)*R;
  int y_2 = y+cos(a)*R;
  plotLine(x+random(-200,200),y+random(-200,200),x_2+random(-200,200),y_2+random(-200,200));
  plotLine(x+random(-200,200),y_2+random(-200,200),x_2+random(-200,200),y+random(-200,200));
  
//  int x = random(0,x_max);
//  int y = random(0,y_max);
//  int x_2 = random(0,x_max);
//  int y_2 = random(0,y_max);
//  plotLine(x,y,x_2,y_2);
}

void randomSquiggle(int x_max,int y_max, int R){
  float deg = TWO_PI/360;
  float a = deg*random(0,360);
  int r = 100;
  
  int x = random(0,x_max);
  int y = random(0,y_max);
  for(int j=0;j<1;j++){
    int x_1 = x;
    int y_1 = y;
    for(int m=0; m<R; m++){
      if(m==1){
        toggle_pen();
      }
      a += random(-15,15)*deg;
      int x_2 = x_1+sin(a)*r;
      int y_2 = y_1+cos(a)*r;
      plotLine2(x_1,y_1+(j*500),x_2,y_2+(j*500));
      x_1 = x_2;
      y_1 = y_2;
    }
    toggle_pen();
  }
}

void plotLine2(int X1,int Y1,int X2,int Y2){
  moveToPointAcc(X1,Y1);
  
  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(xdiff,2)+pow(ydiff,2));


  float x_space = xdiff/hypo;

  float y_space = ydiff/hypo;

  for(int s=1; s<hypo; s++){
    int X = X1+(x_space*s);
    int Y = Y1+(y_space*s);
    if(X<width+1 && X>=0 && Y<height+1 && Y>=0){
      moveToPointAccDraw(X,Y);
    }else{
      break;
    }
  }
}

void randomLine(int x_max,int y_max, int R){
  float angle = TWO_PI/360;
  float a = angle*random(0,360);
  int x = random(0,x_max);
  int y = random(0,y_max);
  int x_2 = x+sin(a)*R;
  int y_2 = y+cos(a)*R;
  plotLine(x,y,x_2,y_2);
  
//  int x = random(0,x_max);
//  int y = random(0,y_max);
//  int x_2 = random(0,x_max);
//  int y_2 = random(0,y_max);
//  plotLine(x,y,x_2,y_2);
}

void lineRotation(){
//  float a = TWO_PI/100; 
//
//  int count = 0;
//  
//  int sp = height/120;
//  int r = sp*1.5;
//  
//  float xr = sin(a*sin(100)*100)*r;
//  float yr = cos(a*cos(100)*100)*r;
//  int x = f*sp;
//  int y = d*sp;
//  plotLine(x+xr,y+yr,x-xr,y-yr);  
}

void asterisk(int X,int Y,int R){
  float a = TWO_PI/6; 

  for(int h=0; h<3; h++){
    int xr = sin(a*h)*R;
    int yr = cos(a*h)*R;
    int x = X;
    int y = Y;
    plotLine(x+xr,y+yr,x-xr,y-yr); 
  }
}

void perimeter(){
  int len = 100;
  
  moveToPointAcc(0,0); 
  
  moveToPointAcc(0,height);
  plotLine(0,height,0,height-len);
  plotLine(0,height,len,height);  
  
  moveToPointAcc(width,height);
  plotLine(width,height,width-len,height);
  plotLine(width,height,width,height-len);
  
  moveToPointAcc(width,0); 
  plotLine(width,0,width-len,0);
  plotLine(width,0,width,len);
    
  moveToPointAcc(0,0);
  plotLine(0,0,len,0);
  plotLine(0,0,0,len);

  moveToPointAcc(0,0);  
}
