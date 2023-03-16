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

bool pass_level;
bool game_over;

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
}

//BEGINNING MAIN LOOP
void loop() {

  if (game_over = true){
    while(true){
      lcd.setCursor(0,0); 
      lcd.print(" This is Slot-it"); 
      lcd.setCursor(0,1); 
      lcd.print(" Press start! ");
      betInState = digitalRead(betIn);
        //If the user successfully "spun it"
      if (betInState == HIGH){
          game_over = false;
          lcd.clear();
          break;
        }
    }
  }

  randNum = random(2);
  delay(1000);

  //The spin it function
  if (randNum == 0) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Spin it! "); //You can write 16 Characters per line .
    digitalWrite (spinIndicate, HIGH);

    while (true)//time(NULL) - startTime > secs)
    {
      spinInState = digitalRead(spinIn);
      betInState = digitalRead(betIn);
      //If the user successfully "spun it"
      if (spinInState == HIGH){
        digitalWrite(spinOut, HIGH); // sets the digital pin 9 on
        delay(100);  
        digitalWrite(spinOut, LOW);  // sets the digital pin 9 off
        pass_level = true;
        break;
      }

      if (betInState == HIGH){
        pass_level = false;
        break;
      } 
    }

    if (pass_level == true){
      score++;
      lcd.setCursor(1,0); //Defining positon to write from first row,first column .
      lcd.print("Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      game_over = false;
    }

    if (pass_level == false){
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print(" YOU LOSE :( "); //You can write 16 Characters per line .
      lcd.setCursor(0,1); //Defining positon to write from second row,first column .
      lcd.print("Final Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      game_over = true;
      delay(3000);
    }
  
    delay(4000);
    lcd.clear();
    digitalWrite (spinIndicate, LOW);
  }
  
  //The bet it function
  if (randNum == 1) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Bet it! "); //You can write 16 Characters per line .
    digitalWrite (betIndicate, HIGH);

    time_t secs = 3000; // 3 seconds

    time_t startTime = time(NULL);
    while (true)//time(NULL) - startTime > secs)
    {
      betInState = digitalRead(betIn);
      spinInState = digitalRead(spinIn);

      //If the user successfully "bet it"
      if (betInState == HIGH){
        digitalWrite(betOut, HIGH); // sets the digital pin 9 on, lights up success light
        delay(100);  
        digitalWrite(betOut, LOW);  // sets the digital pin 9 off, turns off success light
        pass_level = true;
        break;
      }  

      if (spinInState == HIGH){
        pass_level = false;
        break;
      } 
    }

    if (pass_level == true){
      score++;
      lcd.setCursor(1,0); //Defining positon to write from first row,first column .
      lcd.print("Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      game_over = false;
    }

    if (pass_level == false){
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print(" YOU LOSE :( "); //You can write 16 Characters per line .
      lcd.setCursor(0,1); //Defining positon to write from second row,first column .
      lcd.print("Final Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      game_over = true;
      delay(3000);
    }
  
    delay(1000);
    lcd.clear();
    digitalWrite (betIndicate, LOW);
  }


}
