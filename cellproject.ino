//Aviv Gideoni's Plant Cell Game Project
//For Edith Baker school
//3rd change



#include <LiquidCrystal_I2C.h>
#include <Timer.h>
#include <Wire.h> 

///new feature1
///new feature1
///new feature1

int joysticky = A1; 
int joystickx = A0; 

String SystemMode = "";

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display 

int Leds[]= {2,3,11,10,13,5,7,4,8,6,9};

String Questions[] = {
  "I'm the cell's  energy generator",
  "I'm the cell's  gate keeper", 
  "I'm the liquid  that fills cell",
  "I'm the smooth  packaging center",
  "I'm the rough   packaging center",
  "I transport     proteins",
  "I'm carrying    the DNA",
  "I produce the   proteins",
  "I'm the storage of the cell",
  "I'm coloring    the cell",
  "I'm the cell's  rigid layer"};

int Answers[] = {6,4,1,10,8,0,9,7,2,3,5};

int Button = A2;
int RedButton = A3;
int AnimateTimer = 0;
int CurrentLed = 0;
void setup(){
Serial.begin(115200); 
  
 pinMode(joystickx, INPUT); pinMode(joysticky, INPUT);

 for (int i=0;i<11;i++){
  pinMode(Leds[i],OUTPUT);
  digitalWrite(Leds[i] ,LOW);
 }

  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  
  lcd.init(); //initialize the lcd
  lcd.backlight(); //open the backlight 
  randomSeed(analogRead(0));

}

void displayQuestion(int q){

  String nextQuestion1 = Questions[q].substring(0, 16);  
  String nextQuestion2 = Questions[q].substring(16, 32);

  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print(nextQuestion1);
  lcd.setCursor(0,1);
  lcd.print(nextQuestion2);
  
  }

void TurnOffLeds(){
  for (int i=0; i < 11; i++){digitalWrite(Leds[i], LOW);}
}

void AnimateLeds(int AnimateType){
  
   if (AnimateTimer >analogRead(A0)*0.5+100)
      {
           TurnOffLeds();
           digitalWrite(Leds[CurrentLed], HIGH);  
           if (CurrentLed <10 ) {CurrentLed++;} else {CurrentLed = 0;}  
           AnimateTimer = 0;
      }
   AnimateTimer++;
}

void AnimateCorrect(){
  for (int j=0; j < 2; j++){
  for (int i=0; i < 11 ; i++){digitalWrite(Leds[i], HIGH);}
  delay(200);
  for (int i=0; i < 11 ; i++){digitalWrite(Leds[i], LOW);}
  delay(200);
  }
}
void AnimateWin(){ 
  int w=100;
  for (int j=0; j < 2; j++){
  for (int i=0; i < 6 ; i++){
        digitalWrite(Leds[3], HIGH); delay(w); 
        digitalWrite(Leds[2], HIGH);digitalWrite(Leds[4], HIGH); delay(w);
        digitalWrite(Leds[1], HIGH);digitalWrite(Leds[5], HIGH); delay(w);
        digitalWrite(Leds[0], HIGH);digitalWrite(Leds[6], HIGH); delay(w);
        digitalWrite(Leds[10], HIGH);digitalWrite(Leds[7], HIGH); delay(w);
        digitalWrite(Leds[9], HIGH);digitalWrite(Leds[8], HIGH); delay(w);
        
        digitalWrite(Leds[3], LOW); delay(w); 
        digitalWrite(Leds[2], LOW);digitalWrite(Leds[4], LOW); delay(w);
        digitalWrite(Leds[1], LOW);digitalWrite(Leds[5], LOW); delay(w);
        digitalWrite(Leds[0], LOW);digitalWrite(Leds[6], LOW); delay(w);
        digitalWrite(Leds[10], LOW);digitalWrite(Leds[7], LOW); delay(w);
        digitalWrite(Leds[9], LOW);digitalWrite(Leds[8], LOW); delay(w);
        
  }
}
}
void PerformWin(){
// what happens when the user wins
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("*****YOU WIN*****");
  lcd.setCursor(0,1); 
  lcd.print("****GREAT JOB***");
  AnimateWin();
  delay(3000);
}

void PerformLose(){
 lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("Not exactly ... ");
  lcd.setCursor(0,1); 
  lcd.print("Let's play again"); 
  delay(4000);
}

  

void PlayGame() { 

// print welcome + push the button to start the game
  SystemMode ="";
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print(" Aviv Gideoni's"); 
  lcd.setCursor(0,1); 
  lcd.print("PLANT CELL GAME");
  delay(4000);  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("PLANT CELL GAME");
  lcd.setCursor(0,1); 
  lcd.print("Push to Start-->");
  
  TurnOffLeds();
  AnimateTimer = 0;
  //joystick
  
// wait for user to push the button
  while(analogRead(Button) < 700 ){
    Serial.println(analogRead(Button));
    AnimateLeds(1);
 //   printWelcomeMessage();
    delay(1);
  }
lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Use Joystick and");
  lcd.setCursor(0,1); 
  lcd.print("then hit the Red");
  
delay(4000);  


int QtoShow=0;
bool userCorrect = true;

while ((userCorrect) && (QtoShow < 11)) {
  displayQuestion(QtoShow);

  int UserAnswer;
  UserAnswer = answerselection(); 

  if (UserAnswer == Answers[QtoShow]){
      // if user is right
  lcd.clear(); 
  lcd.setCursor(0,0); 
  lcd.print("Correct !!!");
  AnimateCorrect();
  lcd.setCursor(0,1); 
  lcd.print("Get Ready ...");
  AnimateLeds(1);
  delay(2000);
  QtoShow = QtoShow + 1;
  
  }
  else
  {
      // if user is wrong
  lcd.clear(); 
  userCorrect = false; 
      }
}

  if (userCorrect) 
  {PerformWin();}
  else {PerformLose();}
  
}
int answerselection(){

  int i = 1; 
 
 while(analogRead(RedButton) < 700){ 
  int jx = analogRead(A0); 
 
if (jx < 300){i = i-1;
              if (i == -1) {i = 10;}}
if (jx > 700){
            if(i<10) {i = i+1;}
            else {i=0;}}
    
Serial.println(i);

TurnOffLeds(); 
digitalWrite(Leds[i], HIGH);
 
delay(200);
 }
 return i;
}

void loop() 
{
PlayGame();
}