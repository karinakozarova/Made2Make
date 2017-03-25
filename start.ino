#define DIR_MOTOR_PEN 9
#define STEP_MOTOR_PEN 10
#define DIR_MOTOR_PLATE 11
#define STEP_MOTOR_PLATE 12
#define STEP_DURATION 2 //in ms
#define MOTOR_PLATE 2
#define MOTOR_PEN 1

#include <Servo.h> 
 
Servo servo_test; 
Servo myservo;
                
int angle = 0;    
int xPin = A1;
int yPin = A0;
int buttonPin = 13;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
//int servo_up = 0;
int pos = 0;

int xValue = 0;
int yValue = 0;

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
  pinMode(buttonPin, INPUT);
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
  Serial.println("Loop ");
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
  delay(15);
  yValue = analogRead(yPin);
 
  if(xValue==507&&(yValue==504 || yValue==505 || yValue==503)){
           buttonState = digitalRead(buttonPin);
            //Serial.println(buttonState);
            if(buttonState == LOW) {
              // delay(100);
              //Serial.println("Clicked");
              servo_move_down();
              
              }else{
              //Serial.println("Button not moved");
              servo_move_up();
              }
            }
    
    
   if(xValue > 1010&&yValue >501 && yValue<504){
      //joystick_move_forward();
      
  Serial.println("Forward ");
      stepMe(MOTOR_PLATE,1);
    }
    
  if(xValue<6&&yValue> 479&&yValue<509){
      //joystick_move_down();
      
  Serial.println("Down ");
      stepMe(MOTOR_PLATE,0);
   } 
    
  if(yValue<5&&xValue >505 && xValue <595){
      //joystick_move_left();
      
  Serial.println("Left ");
      stepMe(MOTOR_PEN,1);
  } 
 if(xValue > 473&& xValue<508&&yValue >1010) {
      //joystick_move_right();
      
  Serial.println("Right ");
      stepMe(MOTOR_PEN,0);
  }
 
}
void joystick_move_forward(){
  Serial.println("Forward ");
  joystick_position();
  
}
void joystick_move_left()
{
 Serial.println("Left ");
 joystick_position();
}
void joystick_move_right()
{
  Serial.println("Right: ");
  joystick_position();
}
void joystick_move_down()
{
  Serial.println("Down ");
  joystick_position();
}
void servo_move_down(){
  for (pos = 90; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(15);                       
  }
}
void servo_move_up(){
  //servo goes up
  for(angle = 0; angle < 90; angle += 1)    
  {                                  
    servo_test.write(angle);                 
    delay(15);                       
  } 
  //delay(1000);
}

 void stepMe(int motor, int dir) { 
  //1 - motor pen, 2 - motor plate // 0 - left, 1 - right // 
  if(motor == 1) { // motor pen
      digitalWrite(DIR_MOTOR_PEN, dir);
      digitalWrite(STEP_MOTOR_PEN, HIGH);
      delay(STEP_DURATION*5);
      digitalWrite(STEP_MOTOR_PEN, LOW);
  } else { 
    digitalWrite(DIR_MOTOR_PLATE, dir);
      digitalWrite(STEP_MOTOR_PLATE, HIGH);
      delay(STEP_DURATION*5);
      digitalWrite(STEP_MOTOR_PLATE, LOW);
  }
 }
