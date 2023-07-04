// the setup function runs once when you press reset or power the board
// the setup function runs once when you press reset or power the board
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
String tagID = "";
RH_ASK driver;

#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
String plates[10] = {};



int occurances[10] = {};
int index = 0;
byte readCard[4];
String MasterTag = "3213771E";
//String tagID = "";


MFRC522 mfrc522(SS_PIN, RST_PIN);



#define trigPin 5
#define echoPin 4

#define trigPin2 A1
#define echoPin2 A0

int buttonLeft = 0;
int buttonRight = 0;
int leftLight = A3;
int rightLight = A2;
int leftBlindLight = A1;
int rightBlindLight = A0;
long leftDistance = 0;
long leftDuration;
long rightDuration;
long rightDistance = 0;


typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;


int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

int side = 0;
int limit = 0;



enum SM_light {red, redWait, green, yellow};


enum SM_LCD {base, tickets};




void setup() {
  //pinMode(5, OUTPUT); // Sets the trigPin as an OUTPUT
 // pinMode(4, INPUT);
  //pinMode(3, OUTPUT); // Sets the trigPin as an OUTPUT
  //pinMode(2, INPUT);
  //lights
  pinMode(A2, INPUT);
  pinMode(8, INPUT);
  pinMode(A3, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, INPUT);
  //buttons
  pinMode(A4, OUTPUT);
  pinMode(A5, OUTPUT);
  //buzzer
  pinMode(6, OUTPUT);
  
  unsigned char i = 0;
  tasks[i].state = red;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick;
   i++;
  tasks[i].state = base;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick2;
  
  delay_gcd = 500;
   //digitalWrite(3, LOW);
   
  Serial.begin(9600);
  
  SPI.begin();
 
  mfrc522.PCD_Init();
  delay(4);
  //Show details of PCD - MFRC522 Card Reader
  mfrc522.PCD_DumpVersionToSerial();
  lcd.begin(16, 2);
  
  
  // put your setup code here, to run once:

}




int leftChecker = 0;
int rightChecker = 0;
//vector<String> id;
int counter = 0;
int count = 0;
int validID = 0;

int spot = 0;
int tick2(int state) { 
  switch (state){ 
  case base: 
  Serial.println("base");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Press btn");
  lcd.setCursor(0,1);
  lcd.print("for tckts");
  if (digitalRead(A2) == 1) { 
    state = tickets;
  }
  else { 
    state = base;
  }
    break;

    case tickets: 
      if (plates[spot]!=""){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("#");
      lcd.print(spot+1);
      lcd.print(" Plate: ");
      lcd.print(plates[spot]);
      lcd.setCursor(0,1);
      lcd.print("Ticket #: ");
      lcd.print(occurances[spot]);
    }
    else {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("no tckts");
    }
    if (digitalRead(8) == 1) { 
      spot =0;
      state = base;
      
      
    }
    else if(digitalRead(A2) == 1) { 
      spot++;
      if(plates[spot] == ""){
        spot=0;
      }
      state = tickets;
    }
    else{
      state = tickets;
    }
    break;
      
  }
  return state;
    
}


int lcdReset = 0;
int lcdChange = 0;
int tick(int state) {
  switch(state) {
    case red:
            digitalWrite(A5, HIGH);
              digitalWrite(A4, LOW); 
          Serial.println("red");
          if ((count > 7) && ((rightDistance < 12))) {
              
              count = 0;
              state = redWait;
              
          }
          else {
              count++;
              while(getID()) {
                int flag = 0;
                for (int i=0; i< 10;i++){
                  if (plates[i] == tagID){
                    occurances[i] = occurances[i]+1;
                    flag = 1;
                    
                  }
                }
                if (flag == 0) { 
                  plates[index] = tagID;
                  occurances[index] = 1;
                  index++;
                }
                  //occurances[index] = 1;
                  //id.push_back(tagID);
                  Serial.println(tagID);
                  
              }
              state = red;
          }
          break;

      case redWait: 
        Serial.println("redWait");
        if (count > 4) {
          digitalWrite(A5, LOW);
          digitalWrite(A3, HIGH);
          count = 0; 
          state = green;
        }
        else { 
          count++;
          while(getID()) {
                int flag = 0;
                for (int i=0; i< 10;i++){
                  if (plates[i] == tagID){
                    occurances[i] = occurances[i]+1;
                    flag = 1;
                    
                  }
                }
                if (flag == 0) { 
                   plates[index] = tagID;
                   occurances[index] = 1;
                   index++;
                }
                  //id.push_back(tagID);
                Serial.println(tagID);
        
          }
          state = redWait;
        }
        break;
      case green:
      digitalWrite(A5, LOW);
              digitalWrite(A3, HIGH);
          Serial.println("green");
          if (count > 15){
            digitalWrite(A3, LOW);
              digitalWrite(A4, HIGH);
              count =0;
              state = yellow;
              //count =0;
          }
          else {
              count++;
              state = green;
          }
          break;
    
      case yellow:
      digitalWrite(A3, LOW);
              digitalWrite(A4, HIGH);
          Serial.println("yellow");
          if (count > 6){
            digitalWrite(A4, LOW);
              digitalWrite(A5, HIGH);
              count =0;
              state = red;
          }
          else{
              count++;
              state = yellow;
          }
          break;
          
  }
  return state;
}

int leftSide = 0;
int rightSide = 0;
int reset = 9;
int place = A1;



void loop() {

  

  //Serial.println(digitalRead(8));
  //Serial.println(digitalRead(A2));
  //lcd.print("test");


  delay(100);
  //digitalWrite(trigPin, LOW);  // Added this line
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2); // Added this line
  //digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin2, HIGH);
  
  delayMicroseconds(10); // Added this line
  //digitalWrite(trigPin, LOW);
  digitalWrite(trigPin2, LOW);
  //leftDuration = pulseIn(echoPin, HIGH);
  rightDuration = pulseIn(echoPin2, HIGH);
  //leftDistance = (leftDuration*.0343)/2;
  rightDistance = (rightDuration*.0343)/2;

  
  //leftDistance = 100;
  //Serial.print("after left dist: ");
  //Serial.println(leftDistance);
  Serial.print("after right dist: ");
  Serial.println(rightDistance);
  buttonLeft = digitalRead(A4);
  buttonRight = digitalRead(A5);
  for(int i=0;i<tasksNum; ++i){
    if((millis()-tasks[i].elapsedTime)>=tasks[i].period){
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elapsedTime = millis();
    }
  }
  
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  
  // put your main code here, to run repeatedly:

}

boolean getID()
{
  
  // Getting ready for Reading PICCs
  //If a new PICC placed to RFID reader continue
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  
  //Since a PICC placed get Serial and continue
  if ( ! mfrc522.PICC_ReadCardSerial()) {
  return false;
  }
  
  tagID = "";
  // The MIFARE PICCs that we use have 4 byte UID
  for ( uint8_t i = 0; i < 4; i++) {
  //readCard[i] = mfrc522.uid.uidByte[i];
  // Adds the 4 bytes in a single String variable
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
  
}
