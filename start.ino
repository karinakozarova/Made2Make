int xPin = A1;
int yPin = A0;
int ledPin = 8;
int xPosition = 0;
int yPosition = 0;

void joystick_position();
void move_forward();
void move_left();
void move_right();
void move_down();

void setup() {
  Serial.begin(9600); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
  /*pinMode(ledPin,OUTPUT);*/
}

void loop() {
  joystick_position();

}

void joystick_position(){
  int xValue=analogRead(xPin);
  Serial.print("X: ");
  Serial.print(xValue);
  delay(250);
  int yValue=analogRead(yPin);
  Serial.print("Y: ");
  Serial.println(yValue);
  delay(250);
  /*digitalWrite(ledPin,xValue*50);*/
  if(xValue==507){
      if(yValue==504 || yValue==505 || yValue==503){
            Serial.print("Button not moved");
          }
    }
    
   if(xValue > 1020){
    if(yValue >501 && yValue<504){
      move_forward();
    }
    }
    
  if(xValue<6){
    if(yValue> 479&&yValue<509)
    {
      move_down();
    }
   } 
    
  if(yValue<5){
    if(xValue >505 && xValue <595){
    move_left();
    }
  } 
 if(xValue > 473&& xValue<508) {
  if(yValue ==1023){
  move_right();
 }
 }
}

void move_forward(){
//x ot 1023 do 1022 
// y ot 360 do 506
 Serial.print("Forward ");
joystick_position();
}
void move_left()
{
//x 506 - 594
// y 0
 Serial.print("Left ");

joystick_position();
}
void move_right()
{
//x 474-507
// y 1023
 Serial.print("Right: ");
joystick_position();
}
void move_down()
{
// x 0
//y 480 -504
 Serial.print("Down ");
joystick_position();
}
