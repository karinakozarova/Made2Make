#define DIR_MOTOR_PEN 9
#define STEP_MOTOR_PEN 10
#define DIR_MOTOR_PLATE 11
#define STEP_MOTOR_PLATE 12
#define STEP_DURATION 1 //in ms
#define MOTOR_PLATE 2
#define MOTOR_PEN 1

#include <Servo.h> 
 
Servo servo_test; 
Servo myservo;
                
int angle = 0;   
int down = 0; 
int xPin = A1;
int yPin = A0;
int bPin = A5;

int xDir = 0;
int yDir = 0;
int bValue = 0;
int sValue = 0;

int xPosition = 0;
int yPosition = 0;
int xValue = 0;
int yValue = 0;
int pos = 0;

void joystick_position();

void setup() {
  Serial.begin(115200); 
 
  //setting uo the pins
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(DIR_MOTOR_PEN,OUTPUT);
  pinMode(STEP_MOTOR_PEN,OUTPUT);
  pinMode(DIR_MOTOR_PLATE,OUTPUT);
  pinMode(STEP_MOTOR_PLATE,OUTPUT);
 
  //attaching the servo
  myservo.attach(6);
 
  Serial.println("Program started");
}

void loop() {
  joystick_position();
}
  
void joystick_position(){
  //control the joystick
  xValue= analogRead(xPin);
  yValue = analogRead(yPin);
  bValue = analogRead(bPin);
  Serial.print(bValue);

   //it moves up and down 
   //chenge the pottentiometer of the arduino and it changes the angle of the pen 
   sValue = map(bValue,0,1023,85,10);
  
  myservo.write(sValue);
 // move the pen according to the x and y cordinates
  if((xValue>490 && xValue <525 ) && (yValue>490 && yValue<525))
  {
    stepStop();        
  } 
 else if((xValue>490 && xValue <525 )){

           if(yValue > 525)
           {     
               //push the y value and the pen moves to the right
               yValue = map(yValue,525,1023,20,1);
               yDir = 1;
           } 
           else 
           {
               //push the y value and it the pen to the left 
               yValue = map(yValue,490,0,20,1);
               yDir = 0;

           }
      
      digitalWrite(STEP_MOTOR_PLATE, LOW); 
      stepMeHigh(STEP_MOTOR_PEN,yDir,yValue);

 } 
 else if((yValue>490 && yValue <525 ))
 {
      
      if(xValue > 525)
      {      
        //push the y value and it moves the plate forward => the pen moves backward
        xValue = map(xValue,525,1023,20,1);
        xDir = 1;
      } 
      else
      {
        xValue = map(xValue,490,0,20,1);
        xDir = 0;
      }

      digitalWrite(STEP_MOTOR_PEN, LOW);
      stepMeHigh(STEP_MOTOR_PLATE,xDir,xValue);
      
 }
 else
 {
      //push the y value and it moves the position of the plate backward => the pen moves forward
      if(xValue > 525)
      {      
        xValue = map(xValue,525,1023,20,1);
        xDir = 1;
      } 
      else
      {
        xValue = map(xValue,490,0,20,1);
        xDir = 0;
      }
   
      if(yValue > 525){      
        yValue = map(yValue,525,1023,20,1);
        yDir = 1;
      }
      else
      {
        yValue = map(yValue,490,0,20,1);
        yDir = 0;
      }
      
      stepMeHigh(STEP_MOTOR_PLATE,xDir,xValue);
      stepMeHigh(STEP_MOTOR_PEN,yDir,yValue);   
    }
}

void servo_move_down(){
  
  //pen goes down
  //change the angle of the pen from 90 to 0
  for (pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);                    
  }
 
}

void servo_move_up(){
 
  //pen goes up
  //change the angle of the pen from 0 to 90
  for(angle = 0; angle < 90; angle += 1)    
  {                                  
    servo_test.write(angle);                    
  }
 
}

void stepMeHigh(int motor, int dir, int del) { 
 
  //1 - motor pen, 2 - motor plate // 0 - left, 1 - right //
  digitalWrite(DIR_MOTOR_PLATE, dir);
  digitalWrite(DIR_MOTOR_PEN, dir);
  digitalWrite(motor, HIGH);
  delay(del);
  digitalWrite(motor, LOW);
 
 }

void stepStop(){
 
 //nulls the step
  digitalWrite(STEP_MOTOR_PEN, LOW);
  digitalWrite(STEP_MOTOR_PLATE, LOW);
 
}
