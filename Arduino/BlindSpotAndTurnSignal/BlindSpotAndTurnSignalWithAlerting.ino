#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 180;
int buzzer=6;
int counter = 0;
int melodyBell[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteBellDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

// notes of the moledy followed by the leftDuration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Nokia Ringtone
  // Score available at https://musescore.com/user/29944637/scores/5266155
  
  NOTE_E5, 8, NOTE_D5, 8, NOTE_FS4, 4, NOTE_GS4, 4,
  NOTE_CS5, 8, NOTE_B4, 8, NOTE_D4, 4, NOTE_E4, 4,
  NOTE_B4, 8, NOTE_A4, 8, NOTE_CS4, 4, NOTE_E4, 4,
  NOTE_A4, 2,
};



// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and leftDuration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the leftDuration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteleftDuration = 0;
#define trigPin 5
#define echoPin 4

#define trigPin2 3
#define echoPin2 2

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
byte readCard[4];
String MasterTag = "3213771E";
String tagID = "";


MFRC522 mfrc522(SS_PIN, RST_PIN);

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

enum SM_light {first, bell, leftTurnSignal, rightTurnSignal, off, off2, turnSignalBlind}; 
enum SM_blind{start, leftBlindSpot, bothBlindSpot, rightBlindSpot, alert}; 


void setup() {
  pinMode(5, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(4, INPUT);
  pinMode(3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(2, INPUT);
  //lights
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  //buttons
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  //buzzer
  pinMode(6, OUTPUT);
  
  unsigned char i = 1;
  tasks[i].state = first;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick;
  i--;
  tasks[i].state = start;
  tasks[i].period = 300;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &tick2;
  
  delay_gcd = 300;
   //digitalWrite(3, LOW);
   
  Serial.begin(9600);
  //Serial.begin(9600);
  SPI.begin();
  
  mfrc522.PCD_Init();
  delay(4);
  //Show details of PCD - MFRC522 Card Reader
  mfrc522.PCD_DumpVersionToSerial();
  
  Serial.println("--------------------------");
  Serial.println(" Access Control ");
  Serial.println("Scan Your Card>>");
  // put your setup code here, to run once:

}

int leftChecker = 0;
int rightChecker = 0;
//int counter = 0;
int count = 0;
int validID = 0;
int tick(int state) {
  switch(state) { 
    case first: 
      Serial.print("first: ");
      Serial.println(buttonLeft);
      if (((rightDistance < 9) && (buttonRight == 1)) || ((leftDistance < 9) && (buttonLeft == 1))) { 
        state = turnSignalBlind;
      }
      else if((buttonLeft == 1) && (buttonRight == 1)){
        state = bell;
      }
      else if (buttonLeft == 1){
        side = 0;
        limit++;
        leftChecker = 1;
        state = leftTurnSignal;
      }
      else if(buttonRight ==1 ){
        side = 1;
        limit++;
        rightChecker=1;
        state = rightTurnSignal;
      }
      else { 
        state = first;
      }
     break;

     case bell: 
       for (int thisNote = 0; thisNote < 8; thisNote++) {
          int noteDuration = 1000 / noteBellDurations[thisNote];
          tone(buzzer, melodyBell[thisNote], noteDuration);
          int pauseBetweenNotes = noteDuration * 1.30;
          delay(pauseBetweenNotes);
          
          noTone(buzzer);
        }
        if((buttonLeft == 1) && (buttonRight == 1)){
          state = bell;
        }
        else { 
          state = first;
        }
      break;
      
     case rightTurnSignal:
      Serial.println("state: rightTurnSignal");
      //digitalWrite(rightLight, HIGH);  // turn the LED on (HIGH is the voltage level)
      
//      if(rightDistance < 10) {
//        state = turnSignalBlind;
//      }
      if ((buttonLeft == 1) && (buttonRight == 1) && (limit!=0)) {
        digitalWrite(rightLight, LOW);
        state = bell;
      }
      else if(rightDistance < 10) {
        state = turnSignalBlind;
      }
      else { 
        digitalWrite(rightLight, HIGH);
        state = off;
        limit++; }
      
      break;

      case off: 
        digitalWrite(rightLight, LOW);
        if(limit < 6) { 
          if(rightDistance < 10) {
            state = turnSignalBlind;
          }
          else { 
            limit++;
            state = rightTurnSignal; } 
          
        }
        else{
          limit=0;
          rightChecker = 0;
          state = first;
        }
        break;
      
      case leftTurnSignal:
        Serial.println("state: leftTurnSignal");
        //digitalWrite(leftLight, HIGH);  // turn the LED on (HIGH is the voltage level)
        if ((buttonLeft == 1) && (buttonRight == 1) && (limit!=0)) {
          digitalWrite(leftLight, LOW);
          state = bell;
        }
        else if(leftDistance < 10) {
          state = turnSignalBlind;
        }
        else { 
          digitalWrite(leftLight, HIGH);
          state = off2;
          limit++; 
        }
      
      break;

      case off2: 
        digitalWrite(leftLight, LOW);
        if(limit < 6) { 
          if(leftDistance < 10) {
            state = turnSignalBlind;
          }
          else { 
          limit++;
          state = leftTurnSignal; } 
          
        }
        else{
          limit=0;
          leftChecker = 0;
          state = first;
        }
        break;
        
      case turnSignalBlind:
        digitalWrite(rightLight, LOW);
        digitalWrite(leftLight, LOW);
        Serial.println("state: turnSignalBlind");
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
  
          // calculates the leftDuration of each note
          divider = melody[thisNote + 1];
          if (divider > 0) {
            // regular note, just proceed
            noteleftDuration = (wholenote) / divider;
          } else if (divider < 0) {
            // dotted notes are represented with negative leftDurations!!
            noteleftDuration = (wholenote) / abs(divider);
            noteleftDuration *= 1.5; // increases the leftDuration in half for dotted notes
          }
  
          // we only play the note for 90% of the leftDuration, leaving 10% as a pause
          tone(buzzer, melody[thisNote], noteleftDuration * 0.9);
  
          // Wait for the specief leftDuration before playing the next note.
          delay(noteleftDuration);
  
          // stop the waveform generation before the next note.
          noTone(buzzer);
        }
        leftChecker = 0;
        rightChecker = 0;
        state = start;
      break;
  }
  return state;
}

int leftSide = 0;
int rightSide = 0;

int tick2(int state) { 
    switch(state) { 
    case start: 
      digitalWrite(rightBlindLight, LOW);
      digitalWrite(leftBlindLight, LOW);
      if ((leftDistance < 9) && (rightDistance < 9)){
        state = bothBlindSpot;
      }
      else if (leftDistance < 9){
        state = leftBlindSpot;
      }
      else if (rightDistance < 9){
        state = rightBlindSpot;
      }
      else { 
        state = start;
      }
     break;

     case rightBlindSpot:
        Serial.print("state: rightBlindSpot, rightDistance: ");
        Serial.println(rightDistance);
        digitalWrite(rightBlindLight, HIGH);


        if (buttonRight == 1 || rightChecker == 1) { 
          state = alert;
          rightSide = 1;
        }
        else if ((leftDistance < 10) && (rightDistance < 10)){
          counter = 0;
          state = bothBlindSpot;
        }
        else if (rightDistance < 10) {
          counter = 0;
          state = rightBlindSpot;
           
        }
       
        else {
          counter++;
          if(counter == 5) {
            digitalWrite(rightBlindLight, LOW);
            digitalWrite(leftBlindLight, LOW);
            state = start;
            counter = 0;
          }
        }
        break;

        case leftBlindSpot:
          Serial.print("state: leftBlindSpot, leftDistance: ");
          Serial.println(leftDistance);
          digitalWrite(leftBlindLight, HIGH);
  
  
  
          if (buttonLeft == 1 || leftChecker == 1) { 
            leftSide = 1;
            state = alert;
          }
          else if ((leftDistance < 10) && (rightDistance < 10)){
            counter = 0;
            state = bothBlindSpot;
          }
          else if (leftDistance < 10) {
            counter = 0;
            state = leftBlindSpot;
             
          }
         
          else {
            counter++;
            if(counter == 5) {
              digitalWrite(rightBlindLight, LOW);
              digitalWrite(leftBlindLight, LOW);
              state = start;
              counter = 0;
            }
         }
      break;


        case bothBlindSpot:
        Serial.print("state: BlindSpot, leftDistance: ");
        Serial.println(leftDistance);
        digitalWrite(rightBlindLight, HIGH);
        digitalWrite(leftBlindLight, HIGH);


        if ((buttonRight == 1) || (buttonLeft == 1)) {
          state = alert;
        }

        else if ((leftDistance < 10) && (rightDistance < 10)) {
          counter = 0;
          state = bothBlindSpot;
           
        }
       
        else {
          counter++;
          if(counter == 5) {

            if (leftDistance < 10) {
              digitalWrite(rightBlindLight, LOW);
              counter = 0;
              state = leftBlindSpot;
             
            }
            else if(rightDistance< 10) { 
              digitalWrite(leftBlindLight, LOW);
              counter=0;
              state = rightBlindSpot;
            }
            else { 
              digitalWrite(rightBlindLight, LOW);
              digitalWrite(leftBlindLight, LOW);
              state = start;
              counter = 0; 
            } 
         }
      }
      break;

      case alert:  
        if (rightSide == 1) {
          digitalWrite(leftBlindLight, LOW);
          digitalWrite(rightBlindLight, HIGH);
          rightSide = 0;
        }
        else { 
          digitalWrite(rightBlindLight, LOW); 
          digitalWrite(leftBlindLight, HIGH);
          leftSide = 0;
          }
          //digitalWrite(leftBlindLight, HIGH);
          state = start;
          counter = 0;
       break;
           
  }
  return state;
}



void loop() {

  while ((getID() && (validID ==0))) {
    
    if (tagID == MasterTag){
      Serial.println(" Access Granted!");
      Serial.println("--------------------------");
      validID = 1;
    }
    
    else{
      Serial.println(" Access Denied!");
      Serial.println("--------------------------");
    }
  }

  if (validID ==1){


 delay(100);
  digitalWrite(trigPin, LOW);  // Added this line
  //digitalWrite(trigPin2, LOW);
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //digitalWrite(trigPin2, HIGH);
  
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  //digitalWrite(trigPin2, LOW);
  leftDuration = pulseIn(echoPin, HIGH);
  //rightDuration = pulseIn(echoPin2, HIGH);
  leftDistance = (leftDuration*.0343)/2;
  //rightDistance = (rightDuration*.0343)/2;



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
  Serial.print("after left dist: ");
  Serial.println(leftDistance);
  Serial.print("after right dist: ");
  Serial.println(rightDistance);
  buttonLeft = digitalRead(A4);
  buttonRight = digitalRead(A5);

  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
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

