#ifndef PLOTTER_FUNCTIONS_H
#define PLOTTER_FUNCTIONS_H
#include <Arduino.h>

// class with 'global' variables
class Paper(int W, int H);

// compound functions

void dropSquiggle(int Y, int W);
void flower(int X, int Y, int R, int P);
void grass(int X, int Y, int MIN, int MAX);
void pixel(int X, int Y);
void arc(int X, int Y, int R);
void squiggle(int X,int Y,int LEN, int AMP,int FRQ);
void rect(int X, int Y, int W, int H);
void countToFive(int X, int Y);
void ran_circle(int X, int Y, int R );
void ellipse(int X, int Y, int W, int H);
void jagged_circle();
void randomCross(int x_max,int y_max, int R);
void randomSquiggle(int x_max,int y_max, int R);
void plotLine2(int X1,int Y1,int X2,int Y2);
void randomLine(int x_max,int y_max, int R);
void lineRotation();
void asterisk(int X,int Y,int R);
void perimeter();

// basic functions

void plotLineDashed(int X1,int Y1,int X2,int Y2);
void plotLineCont(int X1,int Y1,int X2,int Y2);
void plotLine(int X1,int Y1,int X2,int Y2);
void moveToPointAccDraw(int X,int Y);
void moveToPointAcc(int X,int Y);
void moveToPoint(int X,int Y, int S);
void returnToHome();
void raise_pen();
void lower_pen();
void toggle_pen();
void stepPen(int pin, int s);
void abortCheck();

#endif