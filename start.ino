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
int xPin = A1;
int yPin = A0;
int bPin = A5;
int buttonPin = 13;

int xDir = 0;
int yDir = 0;
int bValue = 0;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
//int servo_up = 0;
int pos = 0;

int xValue = 0;
int yValue = 0;

int state = 0;

void joystick_position();
void joystick_move_forward();
void joystick_move_left();
void joystick_move_right();
void joystick_move_down();
void print_joystick_position(int xValue,int yValue);
void servo_move_up();
void servo_move_down();

void setup() {
  Serial.begin(115200); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(DIR_MOTOR_PEN,OUTPUT);
  pinMode(STEP_MOTOR_PEN,OUTPUT);
  pinMode(DIR_MOTOR_PLATE,OUTPUT);
  pinMode(STEP_MOTOR_PLATE,OUTPUT);
   myservo.attach(6); 
   Serial.println("Hello\n");
}

void loop() {
  joystick_position();
  delay(10);
  Serial.println("/n");
}

void print_joystick_position(int xValue,int yValue){
  Serial.print("X: ");
  Serial.print(xValue);
  delay(1000);
  Serial.print("Y: ");
  Serial.println(yValue);
  delay(1000);
}
  
void joystick_position(){
  xValue= analogRead(xPin);
  yValue = analogRead(yPin);
  bValue = analogRead(bPin);
  Serial.println(bValue);
  
  if(bValue < 100)
        if(myservo.read() > 40)
        myservo.write(20);
        else 
        myservo.write(50);
 
  if((xValue>500 && xValue <525 ) && (yValue>500 && yValue<525)){
    stepStop();
               
    } else if((xValue>500 && xValue <525 )){

    if(yValue > 525){      
        yValue = map(yValue,525,1023,20,1);
        yDir = 1;
      } else {
        yValue = map(yValue,500,0,20,1);
        yDir = 0;
      }
      
      digitalWrite(STEP_MOTOR_PLATE, LOW);
      stepMeHigh(STEP_MOTOR_PEN,yDir,yValue);

    } else if((yValue>500 && yValue <525 )){
      
      if(xValue > 525){      
        xValue = map(xValue,525,1023,20,1);
        xDir = 1;
      } else {
        xValue = map(xValue,500,0,20,1);
        xDir = 0;
      }

      digitalWrite(STEP_MOTOR_PEN, LOW);
      stepMeHigh(STEP_MOTOR_PLATE,xDir,xValue);
      
    } else {

      if(xValue > 525){      
        xValue = map(xValue,525,1023,20,1);
        xDir = 1;
      } else {
        xValue = map(xValue,500,0,20,1);
        xDir = 0;
      }
    
      if(yValue > 525){      
        yValue = map(yValue,525,1023,20,1);
        yDir = 1;
      } else {
        yValue = map(yValue,500,0,20,1);
        yDir = 0;
      }
      
      stepMeHigh(STEP_MOTOR_PLATE,xDir,xValue);
      stepMeHigh(STEP_MOTOR_PEN,yDir,yValue);   
    }
    
    /*
    if(xValue > 1010&&yValue >500 && yValue<510){    
      Serial.println("Down ");
      state = 1;
      //stepMe(MOTOR_PLATE,1);
    }
        
    if(xValue<6&&yValue> 479&&yValue<509){
        Serial.println("Up ");
        state = 2;
        //stepMe(MOTOR_PLATE,0);
    } 
        
    if(yValue<5&&xValue >505 && xValue <595){    
      Serial.println("Right ");
      state = 3;
      //stepMe(MOTOR_PEN,1);
    } 
      
    if(xValue > 473 && xValue<508 && yValue >1010) {    
      Serial.println("Left ");
      state = 4;
      //stepMe(MOTOR_PEN,0);
    }

    

 switch(state){
    case 0: stepStop();
            break;
            
    case 1: stepMeHigh(STEP_MOTOR_PLATE,1);
            break;
    
    case 2: stepMeHigh(STEP_MOTOR_PLATE,0);
            break;
    
    case 3: stepMeHigh(STEP_MOTOR_PEN,0);
            break;
    
    case 4: stepMeHigh(STEP_MOTOR_PEN,1);
            break;
 }

 */
}

void servo_move_down(){
  for (pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);                    
  }
}

void servo_move_up(){
  //servo goes up
  for(angle = 0; angle < 90; angle += 1)    
  {                                  
    servo_test.write(angle);                    
  } 
  //delay(1000);
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
  digitalWrite(STEP_MOTOR_PEN, LOW);
  digitalWrite(STEP_MOTOR_PLATE, LOW);
}
