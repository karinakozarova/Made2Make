int xPin = A1;
int yPin = A0;

int xPosition = 0;
int yPosition = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(xPin, INPUT);
  pinMode(yPin, INPUT);
}


void loop() {

}

void joystick_position(){
  int xValue=analogRead(xPin);
  Serial.println(xPosition);
  delay(1);
  int yValue=analogRead(yPin);
  Serial.println(yPosition);
  delay(1);
  }




