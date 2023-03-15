#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <time.h>

const int spinIn = 6;
const int spinOut = 9;
const int betIn = 2;
const int betOut = 10;
const int spinIndicate  = 8; //Indicate lights act like the 
const int betIndicate = 7;

int spinInState = 0;
int betInState = 0;
int score = 0;
int inputTime = 300;
int inputRead = 0;

bool pass_level = false;
int randNum = 0;

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
  pinMode(betIn, INPUT);   // Button input for the bet it feature
  pinMode(spinIn, INPUT);  // Button input for the spin it feature
  pinMode(betOut, OUTPUT);    // Lights up the LED for bet it
  pinMode(spinOut, OUTPUT);    // Lights up the LED for spin it
  pinMode(spinIndicate, OUTPUT); //Indicator for which operation to perform
  pinMode(betIndicate, OUTPUT);  //Indicator for which operation to perform
  Serial.begin(9600);

  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light

  // I think this is the right syntax for the interrupts? TBD
  // attachInterrupt(digitalPinInterrupt(PIN), ISR, mode)
}

//BEGINNING MAIN LOOP
void loop() {
  randNum = random(2);

  // every 10 successful attempt, decrement time to input by 25ms
  if (score%10 == 0)
    inputTime -= 25; 

  delay(1000);
  Serial.print(randNum);
  //The spin it function
  if (randNum == 0) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Spin it! "); //You can write 16 Characters per line .
    digitalWrite (spinIndicate, HIGH);

    delay(inputTime);
    spinInState = digitalRead(spinIn);
    betInState = digitalRead(betIn);
    // add other two later
    int temp = inputTime;
    for(temp; temp>0; temp--){
      spinInState = digitalRead(spinIn);
      betInState = digitalRead(betIn);
      
      if(spinInState == 1)     
        inputRead = 1;
      else if(betInState == 1)
          inputRead = 2;
      // add the rest
        
      if(inputRead != 0)
        break;      
      delay(1);
      
    }  
      
    
    
    if(betInState == HIGH) // (betInState == HIGH || loseInState == HIGH || winInState == HIGH)
      pass_level = false;

    if (spinInState == HIGH){
      digitalWrite(spinOut, HIGH); // sets the digital pin 9 on
      delay(100);  
      digitalWrite(spinOut, LOW);  // sets the digital pin 9 off
      pass_level = true;
    }
    

    if (pass_level == false){
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("MISINPUT!!")
      lcd.setCursor(2,0);
      lcd.print("Final Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      score = 0;
    }
    else{
      score++;
      lcd.setCursor(1,0); //Defining positon to write from first row,first column .
      lcd.print("Score: "); //You can write 16 Characters per line .
      lcd.print(score);
    }

  
    delay(1000);
    lcd.clear();
    digitalWrite (spinIndicate, LOW);
  }
  
  //The bet it function
  if (randNum == 1) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Bet it! "); //You can write 16 Characters per line .
    digitalWrite (spinIndicate, HIGH);

    delay(inputTime);
    spinInState = digitalRead(spinIn);
    betInState = digitalRead(betIn);
    // add other two later
    if(spinInState == HIGH) // (betInState == HIGH || loseInState == HIGH || winInState == HIGH)
      pass_level = false;

    if (betInState == HIGH){
      digitalWrite(betOut, HIGH); // sets the digital pin 9 on
      delay(100);  
      digitalWrite(betOut, LOW);  // sets the digital pin 9 off
      pass_level = true;
    }
    

    if (pass_level == false){
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("MISINPUT!!")
      lcd.setCursor(2,0);
      lcd.print("Final Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      score = 0;
    }
    else{
      score++;
      lcd.setCursor(1,0); //Defining positon to write from first row,first column .
      lcd.print("Score: "); //You can write 16 Characters per line .
      lcd.print(score);
    }
  
    delay(1000);
    lcd.clear();
    digitalWrite (betIndicate, LOW);
  }

  while(score == 0){
    delay(300);
    // fail contition met at some point
    // need to reset the game
    // could do this via an input?
  }


}
