int xPin = A1;
int yPin = A0;
int xPosition = 0;
int yPosition = 0;

void joystick_position();
void move_forward();
void move_left();
void move_right();
void move_down();
void print_joystick_position(int xValue,int yValue);

void setup() {
  Serial.begin(9600); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
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
            Serial.println("Button not moved");
    }
    
   if(xValue > 1020&&yValue >501 && yValue<504){
      move_forward();
    }
    
  if(xValue<6&&yValue> 479&&yValue<509){
      move_down();
   } 
    
  if(yValue<5&&xValue >505 && xValue <595){
      move_left();
  } 
 if(xValue > 473&& xValue<508&&yValue ==1023) {
      move_right();
 }
}

void move_forward(){
  Serial.println("Forward ");
  joystick_position();
}
void move_left()
{
 Serial.println("Left ");
 joystick_position();
}
void move_right()
{
  Serial.println("Right: ");
  joystick_position();
}
void move_down()
{
  Serial.println("Down ");
  joystick_position();
}
