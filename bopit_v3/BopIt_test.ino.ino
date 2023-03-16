#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <time.h>

// digital input and output pins for each function
const int spinIn = 6;
const int spinOut = 8;
const int betIn = 2;
const int betOut = 7;
const int loseIn = 10;;
const int loseOut = 0;

// digital pins for fail state and reset
const int MISINPUT = 9;
const int RESET = 0;

// initialized input states for functions
int spinInState = 0;
int betInState = 0;
int loseInState = 0;
int score = 0;
int inputTime = 3000;
int inputRead = 0;

// initialized misc variables
bool pass_level = false;
bool resetFlag = true;
int randNum = 0;

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
  pinMode(betIn, INPUT);  
  pinMode(spinIn, INPUT);  
  pinMode(loseIn, INPUT); 
  pinMode(betOut, OUTPUT);   
  pinMode(spinOut, OUTPUT); 
  pinMode(loseOut, OUTPUT);
  pinMode(MISINPUT, OUTPUT);
  Serial.begin(9600);
  digitalWrite(betOut, 1);
  digitalWrite(spinOut, 1);

  lcd.begin(16,2);  // initialize LCD
  lcd.backlight();  // power on backlight for LCD

}

// MAIN LOOP
void loop() {
  // main menu
  if (resetFlag == true){
    score = 0;
    while(true){
      // print to LCD and wait for user to hit RESET button to start game
      lcd.setCursor(0,0); 
      lcd.print(" This is Slot-it"); 
      lcd.setCursor(0,1); 
      lcd.print(" Press start! ");
      betInState = digitalRead(betIn);  // temporarily using betIt input

      // wait for user to start game
      if (betInState == HIGH){
          resetFlag = false;
          lcd.clear();
          break;
        }
    }  
  }

  randNum = random(3);

  // every 5 successful attempt, decrement time to input by 25ms
  if (score%5 == 0)
    inputTime -= 125; 

  delay(500);
  Serial.print(randNum);

  //The spin it function
  if (randNum == 0) {
    digitalWrite(spinOut, 0);
    delay(50);
    lcd.setCursor(0,0); 
    lcd.print(" Spin it! "); 

    // sample the inputs for inputTime
    int temp = inputTime;
    sample(temp); 
    digitalWrite(spinOut, 1); 

    switch (inputRead){
      case 1:
          pass_level = true;
          setScore(pass_level);
          inputRead = 0;
          break;          
      default:
          pass_level = false;
          inputRead = 0;
          setScore(pass_level);
          break;
    }     
      

    delay(1000);
    lcd.clear();
  }
  
  //The bet it function
  if (randNum == 1) {
    digitalWrite(betOut, 0);
    delay(50);
    lcd.setCursor(0,0);
    lcd.print(" Bet it! ");     

    int temp = inputTime;
    sample(temp);
    digitalWrite(betOut, 1);

    switch (inputRead){
      case 2:
          pass_level = true;
          setScore(pass_level);
          inputRead = 0;
          break;          
      default:
          pass_level = false;
          inputRead = 0;
          setScore(pass_level);
          break;
    }    

    delay(1000);
    lcd.clear();
  }

  //The lose it function
  if (randNum == 2) {
    lcd.setCursor(0,0); 
    lcd.print(" Lose it! "); 

    int temp = inputTime;
    sample(temp);

    switch (inputRead){
      case 3:
          pass_level = true;
          setScore(pass_level);
          inputRead = 0;
          break;          
      default:
          pass_level = false;
          inputRead = 0;
          setScore(pass_level);
          break;
    }    

    delay(1000);
    lcd.clear();
  } 

  while(score == 0){
    lcd.setCursor(0,0); 
    lcd.print(" Play Again? "); 
    lcd.setCursor(0,1); 
    lcd.print(" Reset Game! "); 
    delay(2000);

    // hard reset for testing
    int rst = 0;  
    inputTime = 3000; 
    resetFlag = true;

    // reset game when reset button is pressed
    /*while(true){
      rst = digitalRead(RESET);
      if (rst == 1){
        resetFlag = true;
        break;
      }      
    }*/
    
    lcd.clear();
    break;
  }

}

void sample(int time){
    for(time; time>0; time--){
      // read in all 4 inputs
      spinInState = digitalRead(spinIn);
      betInState = digitalRead(betIn);
      loseInState = digitalRead(loseIn);
     
      // set inputRead if an input is read
      if(spinInState == 1)     
        inputRead = 1;
      else if(betInState == 1)
        inputRead = 2;
      else if(loseInState == 1)
        inputRead = 3;    
        
      // break if any input was detected  
      if(inputRead != 0)
        break;        
    
      
      // delay and sample until input is read or input time limit reached       
      delay(1);
    }
}

void setScore(bool input){
  // fail screen when level is failed
    if (input == false){
      lcd.setCursor(0,0);.
      lcd.print("MISINPUT!!");
      lcd.setCursor(0,1);
      lcd.print("Final Score: "); 
      lcd.print(score);
      digitalWrite(MISINPUT, 0);
      delay(100);
      digitalWrite(MISINPUT, 1);
      delay(3000);
      score = 0;
    }
    // increase score when input is correct
    else{
      score++;
      lcd.setCursor(1,0); 
      lcd.print("Score: "); 
      lcd.print(score);
      delay(500);
    }
}
