// Adam Kort - 1895 Assignment 13 comment
// Kaleb Foster - here is my comment... maybe
// Lauren Duffitt - just a lil comment

const int ledPin1 = 8;   // this pin is the LED1 output
const int ledPin2 = 9;   // this pin is the LED2 output
const int ledPin3 = 10;  // this pin is the LED3 output
const int buttonPin = 7; // this pin is the SPST switch input

void setup() {
  pinMode(ledPin1, OUTPUT);    // sets the digital pin 8 as output
  pinMode(ledPin2, OUTPUT);    // sets the digital pin 9 as output
  pinMode(ledPin3, OUTPUT);    // sets the digital pin 10 as output
  pinMode(buttonPin, INPUT);   // sets the digital pin 7 as input
}

void threeLights(){
  while(1){
    digitalWrite(ledPin1, HIGH);  // sets the digital pin 8 on
    delay(1000);                  // waits for a second
    digitalWrite(ledPin1, LOW);   // sets the digital pin 8 off
    digitalWrite(ledPin2, HIGH);  // sets the digital pin 8 on
    delay(1000);                  // waits for a second
    digitalWrite(ledPin2, LOW);   // sets the digital pin 8 off
    digitalWrite(ledPin3, HIGH);  // sets the digital pin 8 on
    delay(1000);                  // waits for a second
    digitalWrite(ledPin3, LOW);   // sets the digital pin 8 off
    delay(1000);                  // waits for a second
  }
}

void loop() {

  int flash = digitalRead(buttonPin);

  while(HIGH == flash){
    threeLights();
  }
}
