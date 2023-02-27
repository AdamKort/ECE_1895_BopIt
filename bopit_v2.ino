const int spinIn = 6;
const int spinOut = 9;
const int betIn = 2;
const int betOut = 10;
const int spinIndicate  = 8;
const int betIndicate = 7;


int spinInState = 0;
int betInState = 0;

bool pass_level = false;
int randNum = 0;

void setup() {
  pinMode(betIn, INPUT);   // Button input for the bet it feature
  pinMode(spinIn, INPUT);  // Button input for the spin it feature
  pinMode(betOut, OUTPUT);    // Lights up the LED for bet it
  pinMode(spinOut, OUTPUT);    // Lights up the LED for spin it
  pinMode(spinIndicate, OUTPUT); //Indicator for which operation to perform
  pinMode(betIndicate, OUTPUT);  //Indicator for which operation to perform
  Serial.begin(9600);
}

//BEGINNING MAIN LOOP
void loop() {
  randNum = random(2);

  delay(1000);
  Serial.print(randNum);
  //The spin it function      NOT WORKING
  if (randNum == 0) {
    digitalWrite (spinIndicate, HIGH);
    delay(1000);    
    spinInState = digitalRead(spinIn);
    if (spinInState == HIGH){
      digitalWrite(spinOut, HIGH); // sets the digital pin 9 on
      delay(100);  
      digitalWrite(spinOut, LOW);  // sets the digital pin 9 off
      pass_level = true;
    }
    digitalWrite (spinIndicate, LOW);
  }
  
  //The bet it function
  if (randNum == 1) {
    digitalWrite (betIndicate, HIGH);
    delay(1000);
    betInState = digitalRead(betIn);
    if (betInState == HIGH){
      digitalWrite(betOut, HIGH); // sets the digital pin 9 on
      delay(100);  
      digitalWrite(betOut, LOW);  // sets the digital pin 9 off
      pass_level = true;
    }    
    digitalWrite (betIndicate, LOW);
  }


}