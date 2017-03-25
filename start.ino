#include <Servo.h> 
 
Servo servo_test; 
                
int angle = 0;    
int xPin = A1;
int yPin = A0;
int buttonPin = 12;

int xPosition = 0;
int yPosition = 0;
int buttonState = 0;
int servo_up = 0;

void joystick_position();
void joystick_move_forward();
void joystick_move_left();
void joystick_move_right();
void joystick_move_down();
void print_joystick_position(int xValue,int yValue);
void servo_move_up();
void servo_move_down();
void joystick_onclick();

void setup() {
  Serial.begin(9600); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  joystick_position();

}
void print_joystick_position(int xValue,int yValue){
  Serial.print("X: ");
  Serial.print(xValue);
  delay(250);
  Serial.print("Y: ");
  Serial.println(yValue);
  delay(250);
  }
void joystick_position(){
  int xValue=analogRead(xPin);
  int yValue=analogRead(yPin);
 
  if(xValue==507&&(yValue==504 || yValue==505 || yValue==503)){
            buttonState = digitalRead(buttonPin);
            if (buttonState == HIGH) {
              joystick_onclick();
              }
            else Serial.println("Button not moved");
            
    }
    
   if(xValue > 1020&&yValue >501 && yValue<504){
      joystick_move_forward();
    }
    
  if(xValue<6&&yValue> 479&&yValue<509){
      joystick_move_down();
   } 
    
  if(yValue<5&&xValue >505 && xValue <595){
      joystick_move_left();
  } 
 if(xValue > 473&& xValue<508&&yValue ==1023) {
      joystick_move_right();
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

void servo_move_up(){
  //servo goes up
  for(angle = 0; angle < 90; angle += 1)    
  {                                  
    servo_test.write(angle);                 
    delay(15);                       
  } 
  delay(1000);
}
void servo_move_down(){
  //servo goes down
  for(angle = 90; angle>=1; angle-=5)    
  {                                
    servo_test.write(angle);              
    delay(5);                       
  } 
  delay(1000);
  servo_up = 0;
  }
 void joystick_onclick(){
  if(servo_up==1){servo_move_down();}
  else servo_move_up();
  }
