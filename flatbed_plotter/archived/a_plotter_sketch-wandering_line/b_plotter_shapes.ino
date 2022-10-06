

void grid(int X, int Y, int SPACE, int COL,int ROW){

  int xnum = COL;
  int ynum = ROW;

    int w = SPACE*COL;
  int h = SPACE*ROW;

    for(int i=0;i<=xnum;i++){
      if(printAborted==false){
          moveToPoint(X+i*SPACE,Y);
          lower_pen();
          moveToPoint(X+i*SPACE,Y+h);
          raise_pen();
      }else{break;}
    }
    for(int i=0;i<=ynum;i++){
      if(printAborted==false){
          moveToPoint(X,i*SPACE+Y);
          lower_pen();
          moveToPoint(X+w,i*SPACE+Y);
          raise_pen();
      }else{break;}
    }
}

void plotLineCont(int X1,int Y1,int X2,int Y2){

  int xdiff = X2-X1;
  int ydiff = Y2-Y1;
  float hypo = sqrt(pow(xdiff,2)+pow(ydiff,2));

  float x_space = xdiff/hypo;

  float y_space = ydiff/hypo;

  for(int s=1; s<hypo; s++){
    int X = X1+(x_space*s);
    int Y = Y1+(y_space*s);
    if(X>margin && X<width-margin && Y>margin && Y<height-margin && printAborted==false){
      moveToPoint(X,Y);
    }else{break;}
  }
}
