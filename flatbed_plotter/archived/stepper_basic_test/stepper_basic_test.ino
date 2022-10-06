#define dirPin 2
#define stepPin 3

int count = 0;
int val;
int stepsPerRev = 12000;

void setup() {
  // Declare pins as output:
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  // Set the spinning direction CW/CCW:

}
void loop() {
  
  digitalWrite(dirPin, LOW);
  for(int i=0;i<stepsPerRev;i++){
    move(250);
  }
  delay(500);
  
  digitalWrite(dirPin, HIGH);
  for(int i=0;i<stepsPerRev;i++){
    move(300);
  }
  delay(250);
}

int move(int d){
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(d);
  digitalWrite(stepPin, LOW);
  delayMicroseconds(d);
}
