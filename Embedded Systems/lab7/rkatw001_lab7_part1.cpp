/*
Name: Rahul Katwala
Video demo: https://youtu.be/I4jdU9tfd_g
SSID: 862146702
Assignment: CS120B Lab 7 Part 1

*/
//-------------------------------------------------------------------------------

// Array of Output Pin variables, set to the pins being used
#include <LiquidCrystal.h>
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};
unsigned char b_temp;
unsigned char temp;
unsigned short xPosition;
unsigned short yPosition;
const char sound_pattern_size = 2;
const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4
unsigned char counter;
const int buzzer = 3;
int button;
int index = 0;
int row = 0;
int buttonFlag = 0;
int buttonCounter = 0;
const int rs = 4, en = 5, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int xAxis_median = 100;

void resetBuffer() {
    for(int i = 0; i < b_size; i++) {
        // Note this is an arduino function call to the pins
        digitalWrite(b[i], LOW);
    }
}
// Writes to the buffer. Note this function ORs the current value with the new value
// Note that size is an optional argument with default size the same as the buffer
void writeBuffer(unsigned char b_temp, int size = b_size)
{
    for (int i = (size - 1); i >= 0; i--) {
        if ((b_temp >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }

}

typedef struct task {
  int state;
  unsigned long period;
  unsigned long elapsedTime;
  int (*TickFct)(int);
    
} task;

enum States {start, base, shift, next} state;
int Tick(){
  switch (state){
    case start:
      state = base;
      break;
     case base:
     if (buttonFlag ==1){
      state = shift;
      
     }
     else{

      
       if((yPosition > 900) && (xPosition > 900)){
          lcd.setCursor(index,row);
          lcd.print("f");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

        else if((yPosition > 900) && (xPosition < 200)){
          lcd.setCursor(index,row);
          lcd.print("g");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }
       else if((yPosition < 200) && (xPosition < 200)){
          lcd.setCursor(index,row);
          lcd.print("h");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

       else if((yPosition < 200) && (xPosition > 900)){
          lcd.setCursor(index,row);
          lcd.print("i");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }
       
       
       
       else if(xPosition > 900){
          lcd.setCursor(index,row);
          lcd.print("a");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }
       else if(xPosition< 200){
          lcd.setCursor(index,row);
          lcd.print("b");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

       else if(yPosition < 200){
          lcd.setCursor(index,row);
          lcd.print("e");
          if(index == 15){
            lcd.setCursor(index, row);
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

       else if(yPosition > 900){
          lcd.setCursor(index,row);
          lcd.print("c");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

      
       else{
        state = base;
       }
       
       

       





       
     }
     break;
     case next:
        if(((xPosition > 480) && (xPosition <540)) && ((yPosition > 480) && (yPosition <540))){
          state = base;
        }
        else{
          state = next;
        }
        break;
        
     case shift:
      if((yPosition > 900) && (xPosition > 900)){
          lcd.setCursor(index,row);
          lcd.print("F");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

        else if((yPosition > 900) && (xPosition < 200)){
          lcd.setCursor(index,row);
          lcd.print("G");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }
       else if((yPosition < 200) && (xPosition < 200)){
          lcd.setCursor(index,row);
          lcd.print("H");
          if(index ==15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

       else if((yPosition < 200) && (xPosition > 900)){
          lcd.setCursor(index,row);
          lcd.print("I");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }
       
       
       
       else if(xPosition > 900){
          lcd.setCursor(index,row);
          lcd.print("A");
          if(index ==15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }
       else if(xPosition< 200){
          lcd.setCursor(index,row);
          lcd.print("B");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

       else if(yPosition < 200){
          lcd.setCursor(index,row);
          lcd.print("E");
          if(index == 15){
            lcd.setCursor(index, row);
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

       else if(yPosition > 900){
          lcd.setCursor(index,row);
          lcd.print("C");
          if(index == 15){
            row = 1;
            index = 0;
          }
          else{
            index++;
          }
          state = next;
       }

      
       else{
        state = shift;
       }
       buttonFlag = 0;
      break;
     default: break;
  
  }
}

void setup() {
  lcd.setCursor(0,0);
  state = start;
  pinMode(A0, INPUT);
    pinMode(A1, INPUT);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
   lcd.begin(16,2);
  Serial.begin(9600);
}

void loop() {
   xPosition = analogRead(A0);
  yPosition = analogRead(A1);
  pinMode(2, INPUT_PULLUP);
  button = digitalRead(2);
  if(button ==0){
    
    buttonFlag = 1;
    buttonCounter++;
    if(buttonCounter == 4){
       lcd.clear();
       lcd.setCursor(0,0);
       buttonCounter = 0;
       row = 0;
       index = 0;
       buttonFlag = 0;
    }
    
  }
  else{
    buttonCounter = 0;
  }
  
   /*Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(button);
  Serial.println(counter);
  Serial.println(index);
  */
    delay(500);
    Tick();

}
