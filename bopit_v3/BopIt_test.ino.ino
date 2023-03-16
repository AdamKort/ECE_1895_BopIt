#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <time.h>

const int spinIn = 6;
const int spinOut = 9;
const int betIn = 2;
const int betOut = 10;
// EDIT THE ZEROS
const int winIn = 0;
const int winOut = 0;
const int loseIn = 0;
const int loseOut = 0;
const int RESET = 0;

const int spinIndicate  = 8; //Indicate lights act like the 
const int betIndicate = 7;
// EDIT THE ZEROS
const int wintIndicate = 0;
const int loseIndicate = 0;

int spinInState = 0;
int betInState = 0;
int winInState = 0;
int loseInState = 0;
int score = 0;
int inputTime = 300;
int inputRead = 0;

bool pass_level = false;
bool resetFlag = false;
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

void sample(int time){
    for(time; time>0; time--){
      // read in all 4 inputs
      spinInState = digitalRead(spinIn);
      betInState = digitalRead(betIn);
      winInState = digitalRead(winIn);
      loseInState = digitalRead(loseIn);
      
      // set inputRead if an input is read
      if(spinInState == 1)     
        inputRead = 1;
      else if(betInState == 1)
        inputRead = 2;
      else if(winInState == 1)
        inputRead = 3;
      else if(loseInState == 1)
        inputRead = 4;    
        
      // break if any input was detected  
      if(inputRead != 0)
        break; 

      // delay and sample until input is read or input time limit reached       
      delay(1);
    }
}

void setScore(bool input){
    if (input == false){
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("MISINPUT!!");
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
}

//BEGINNING MAIN LOOP
void loop() {

  if (resetFlag == true){
    score = 0;
    resetFlag = false;
  }

  // change this to 4!
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

    int temp = inputTime;
    sample(temp);  

    switch (inputRead){
      case 1:
          digitalWrite(spinOut, HIGH); // sets the digital pin 9 on
          delay(100);  
          digitalWrite(spinOut, LOW);  // sets the digital pin 9 off
          pass_level = true;
          break;          
      default:
          pass_level = false;
          break;
    }    

    setScore(pass_level);
      
    delay(1000);
    lcd.clear();
    digitalWrite (spinIndicate, LOW);
  }
  
  //The bet it function
  if (randNum == 1) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Bet it! "); //You can write 16 Characters per line .
    digitalWrite (spinIndicate, HIGH);

    int temp = inputTime;
    sample(temp);

    switch (inputRead){
      case 2:
          digitalWrite(betOut, HIGH); // sets the digital pin 9 on
          delay(100);  
          digitalWrite(betOut, LOW);  // sets the digital pin 9 off
          pass_level = true;
          break;          
      default:
          pass_level = false;
          break;
    }     

    setScore(pass_level);
  
    delay(1000);
    lcd.clear();
    digitalWrite (betIndicate, LOW);
  }

//  below are the two functions that we have not implemented yet in the same format as the above two

  /*
  //The win it function
  if (randNum == 2) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Win it! "); //You can write 16 Characters per line .
    digitalWrite (winIndicate, HIGH);

    int temp = inputTime;
    sample(temp);

    switch (inputRead){
      case 3:
          digitalWrite(winOut, HIGH); // sets the digital pin 9 on
          delay(100);  
          digitalWrite(winOut, LOW);  // sets the digital pin 9 off
          pass_level = true;
          break;          
      default:
          pass_level = false;
          break;
    }     

    setScore(pass_level);
  
    delay(1000);
    lcd.clear();
    digitalWrite (winIndicate, LOW);
  }

   //The lose it function
  if (randNum == 3) {
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Lose it! "); //You can write 16 Characters per line .
    digitalWrite (loseIndicate, HIGH);

    int temp = inputTime;
    sample(temp);

    switch (inputRead){
      case 4:
          digitalWrite(loseOut, HIGH); // sets the digital pin 9 on
          delay(100);  
          digitalWrite(loseOut, LOW);  // sets the digital pin 9 off
          pass_level = true;
          break;          
      default:
          pass_level = false;
          break;
    }     

    setScore(pass_level);
  
    delay(1000);
    lcd.clear();
    digitalWrite (loseIndicate, LOW);
  } 

  */

  while(score == 0){
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Play Again? "); //You can write 16 Characters per line .
    lcd.setCursor(2,0); //Defining positon to write from first row,first column .
    lcd.print(" Reset Game! "); //You can write 16 Characters per line . 
    int rst = 0;   

    while(true){
      rst = digitalRead(RESET);
      if (rst == 1){
        resetFlag = true;
        break;
      }      
    }
    
    break;
  }

}
