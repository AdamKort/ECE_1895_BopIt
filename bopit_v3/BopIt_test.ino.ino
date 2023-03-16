#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <time.h>

const int spinIn = 6;
const int spinOut = 8;
const int betIn = 2;
const int betOut = 7;
// EDIT THE ZEROS
const int loseIn = 10;;
const int loseOut = 0;
const int MISINPUT = 9;
const int RESET = 0;

int spinInState = 0;
int betInState = 0;
int loseInState = 0;
int score = 0;
int inputTime = 3000;
int inputRead = 0;

bool pass_level = false;
bool resetFlag = true;
int randNum = 0;

//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
void setup() {
  pinMode(betIn, INPUT);   // Button input for the bet it feature
  pinMode(spinIn, INPUT);  // Rotary Encoder input for the spin it feature
  pinMode(loseIn, INPUT);  // IR Sensor input for lose it feature
  pinMode(betOut, OUTPUT);    // Lights up the LED for bet it
  pinMode(spinOut, OUTPUT);    // Lights up the LED for spin it
  pinMode(loseOut, OUTPUT);
  pinMode(MISINPUT, OUTPUT);
  Serial.begin(9600);
  digitalWrite(betOut, 1);
  digitalWrite(spinOut, 1);

  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light

}

//BEGINNING MAIN LOOP
void loop() {
  if (resetFlag == true){
    score = 0;
    while(true){
      lcd.setCursor(0,0); 
      lcd.print(" This is Slot-it"); 
      lcd.setCursor(0,1); 
      lcd.print(" Press start! ");
      betInState = digitalRead(betIn);

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
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Spin it! "); //You can write 16 Characters per line .
    

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
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Bet it! "); //You can write 16 Characters per line .
    

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
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Lose it! "); //You can write 16 Characters per line .

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
    lcd.setCursor(0,0); //Defining positon to write from first row,first column .
    lcd.print(" Play Again? "); //You can write 16 Characters per line .
    lcd.setCursor(0,1); //Defining positon to write from first row,first column .
    lcd.print(" Reset Game! "); //You can write 16 Characters per line . 
    delay(2000);
    int rst = 0;  
    inputTime = 3000; 
    resetFlag = true;

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
    if (input == false){
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("MISINPUT!!");
      lcd.setCursor(0,1);
      lcd.print("Final Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      digitalWrite(MISINPUT, 0);
      delay(100);
      digitalWrite(MISINPUT, 1);
      delay(3000);
      score = 0;
    }
    else{
      score++;
      lcd.setCursor(1,0); //Defining positon to write from first row,first column .
      lcd.print("Score: "); //You can write 16 Characters per line .
      lcd.print(score);
      delay(500);
    }
}

