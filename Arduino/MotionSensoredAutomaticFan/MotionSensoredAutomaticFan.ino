//#include <Adafruit_ST7789.h>
//#include <Adafruit_ST7735.h>
//float temp;
int tempPin = 2;
#define trigPin 13
#define echoPin 12
#include <LiquidCrystal.h>
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};
unsigned char b_temp;
//unsigned char temp;
unsigned short xPosition;
unsigned short yPosition;
const char sound_pattern_size = 2;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4
unsigned char counter;
const int buzzer = 6;
int button;
int index = 0;
int row = 0;
int buttonFlag = 0;
int buttonCounter = 0;
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
long duration; // variable for the duration of sound wave travel
int distance;



const int xAxis_median = 100;


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;


int delay_gcd;
const unsigned short tasksNum = 3;
task tasks[tasksNum];

enum SM1_States{SM1_start, waitPress, wait, startPress};
enum SM2_States{SM2_INIT, Go};

void setup() {
    pinMode(6, OUTPUT);
    pinMode(13, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(12, INPUT);
  lcd.setCursor(0,0);
  pinMode(3, OUTPUT);
//  state = SM1_start;
  pinMode(A0, INPUT);
    pinMode(A1, INPUT);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
   lcd.begin(16,2);
   pinMode(2, INPUT_PULLUP);
     unsigned char i = 0;
  tasks[i].state = SM1_start;
  tasks[i].period = 800;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 800;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick2;
  i++;
  tasks[i].state = SM3_INIT;
  tasks[i].period = 400;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;
  delay_gcd = 400;
   digitalWrite(3, LOW);
   
  Serial.begin(9600);
     pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}




  //int VRM= analogRead(A2);
  int VRM = (5.00 / 1023.00) * analogRead(A2);      //Conversion to voltage
  int VRC = 5 - VRM;
  int RTC = VRM / (VRC / 10000);               //Resistance of RT

  int lnC = log(RTC / 10000);
  int TXC = (1 / ((lnC / 3977) + (1 / 298.15))); //Temperature from thermistor

  int TXCY = TXC - 273.15; //Conversion to Celsius
int  TXCM = (TXCY * (9/5)) + 32;
float  temp = TXCM;

int desired = temp;
int i =10;

int tick2(int state){
  switch(state){
    case SM2_INIT:
      if(desired < temp) {
        //analogWrite(3, 250);
        state = Go;
      }
      else {
        digitalWrite(3,LOW);
        state = SM2_INIT;
      }
      break;

    case Go:
      Serial.print("distance: ");
      Serial.println(distance);
    digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  if (distance < 10){
    analogWrite(3, 100);
  }
  else if(distance < 20){
    analogWrite(3, 125);
  }
  else if(distance < 30){
    analogWrite(3, 175);
  }

  else {
    analogWrite(3, 250);
  }
      if(desired >= temp) {
        //digitalWrite(3,LOW);
        state = SM2_INIT;
        //digitalWrite(3,LOW);
      }
      else{
        
        state = Go;
      }
  }
  return state;
}




int tick(int state){
  switch (state){
    case SM1_start:
    Serial.println(button);
    Serial.println("stateStart");
    if(i==10){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Current Temp:");
     lcd.setCursor(0,1);
  lcd.print(temp);
  
  i=0;
    }
      if(button ==0){
        state = waitPress;
      }
      else{
        i++;
        state = SM1_start;
      }
    break;
    case waitPress:
    Serial.println("waitPress");
    Serial.println(button);
      if(button ==1){
        state = wait;
      }
      else{
        state = waitPress;
        
      }
      break;
    case wait:
     Serial.println("wait");
      if(button ==0){
        i=0;
        lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Current Temp:");
     lcd.setCursor(0,1);
      lcd.print(temp);
      lcd.print(" *F");
      state = startPress;
        
      }
      else{
        Serial.println(button);
        Serial.println(xPosition);
        Serial.println(yPosition);
        if(xPosition > 750){
          desired++;
        }
        else if( xPosition < 250){
          desired--;
        }
       lcd.clear();
       lcd.print("Desired Temp:");
     lcd.setCursor(0,1);
      lcd.print(desired);
      lcd.print(" *F");
        state = wait;
      }
      break;

      case startPress:
          if(button == 1){
            state = SM1_start;
          }
          else{
            state = startPress;
          }
          break;
          
  
      default: break;
   
  }
  return state;
}


void loop() {
//long duration, distance;
  /*digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;

  Serial.println(distance);
*/
  
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
   temp = analogRead(A2);
   int VRT= analogRead(A2);
    VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  int VR = 5 - VRT;
  int RT = VRT / (VR / 10000);               //Resistance of RT

  int ln = log(RT / 10000);
  int TX = (1 / ((ln / 3977) + (1 / 298.15))); //Temperature from thermistor

  TX = TX - 273.15; //Conversion to Celsius
  TX = (TX * (9/5)) + 32;
  temp = TX;
  //Serial.println(temp);
  button= digitalRead(2);

    unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
//tick();


  //Serial.println(
  //if(desired < temp) {analogWrite(3, 100); }
  //else{digitalWrite(3,LOW); }
   //delay(1000); // update sensor reading each one second
}
