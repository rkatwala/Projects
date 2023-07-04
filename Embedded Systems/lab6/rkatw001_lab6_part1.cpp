/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/I7Wd1Zq2rz0?feature=share
SSID: 862146702
Assignment: CS120B Lab 6 Part 1

*/
//-------------------------------------------------------------------------------


// Array of Output Pin variables, set to the pins being used
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
const int xAxis_median = 100; // Adjust this if needed

// Reset the Output Buffer.
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

int delay_gcd;
const unsigned short tasksNum = 2;
task tasks[tasksNum];

enum SM1_States { SM1_INIT, SM1_S0, SM2_S1};
int SM1_Tick(int state){
     //Read thing
    switch(state){ // State transitions
     
      case SM1_INIT:
      
          if (button == 0){
            if(counter > 7 && counter < 10){
              counter++;
            }
            else{counter =0;}
            temp = 0;
            b_temp = 0;
            tone(3, 493.88);
          }
          else if( xPosition > 900){
            if(counter > 5 && counter < 8){
              counter++;
            }
            else{counter =0;}
            
            temp = temp | 0x04;
            b_temp = temp;
            tone(3, 261.63);
          }
          else if(xPosition < 200){
            if(counter > 3 && counter < 6){
              counter++;
            }
            else{counter =0;}
            temp = temp | 0x08;
            b_temp = temp;
            tone(3, 293.66);
          }
          else if(yPosition > 900){
            if(counter < 2){
              counter++;
            }
            else{counter =0;}
            temp = temp | 0x02;
            b_temp = temp;
            tone(3, 349.23);
          }
          else if(yPosition < 100){
            if(counter > 1 && counter < 4){
              counter++;
            }
            else{counter =0;}
            temp = temp | 0x01;
            b_temp = temp;
            tone(3, 440.00);
          }
          else{
            noTone(3);
          }
          

         // writeBuffer(b_temp);
          Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(button);
  Serial.println(counter);

          if(counter == 10){
            //counter = 0;
            state = SM1_S0;
          }
          else{ state = SM1_INIT;}
          break;
          
          case SM1_S0:
           /* if(counter < 4 && counter % 2 == 0){
              tone(3, 349.23);
            }
            
            else if(counter < 8 && counter % 2 == 0){
              tone(3, 440.00);
            }
            else if(counter < 12 && counter % 2 == 0){
              tone(3, 293.66);
            }
            else if(counter < 16&& counter % 2 == 0){
              tone(3, 261.63);
            }
            else if(counter < 20&& counter % 2 == 0){
              tone(3, 493.88);
            }
            else{
              noTone(3);
            }
            counter++;
            if(counter == 20){
              counter =0;
            }
            */
            if(button == 0){
              counter = 0;
              state = SM1_INIT;
            }
           else{
            state = SM1_S0;
           }
           Serial.print("Finish X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(button);
  Serial.println(counter);
           
           break;
           
          default:
          break;
        
    }
    //return state;
    return state;
}

enum SM2_States { SM2_INIT, SM2_S0};
int SM2_Tick(int state){
    //Read thing
    switch(state){
   

     case SM2_INIT:
        if(counter == 10){
          state = SM2_S0;
          counter = 0;
        }
        else {
          state = SM2_INIT;
        }
        break;
      case SM2_S0:
         if(button == 0){
          state = SM2_INIT;
          counter = 0;
         }

         else {
            if(counter < 4 && counter % 2 == 0){
              tone(3, 349.23);
            }
            
            else if(counter < 8 && counter % 2 == 0){
              tone(3, 440.00);
            }
            else if(counter < 12 && counter % 2 == 0){
              tone(3, 293.66);
            }
            else if(counter < 16&& counter % 2 == 0){
              tone(3, 261.63);
            }
            else if(counter < 20&& counter % 2 == 0){
              tone(3, 493.88);
            }
            else{
              noTone(3);
            }
            counter++;
            if(counter == 20){
              counter =0;
            }
            state = SM2_S0;
         }
      break;
      default: break;
      
  }

    return state;
}






void setup() {
    //some set up (Default Arduino Function)
pinMode(A0, INPUT);
    pinMode(A1, INPUT);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
  //activate pull-up resistor on the push-button pin
  pinMode(2, INPUT_PULLUP);
    counter = 0;
    temp = 0;
  b_temp=0;
    // LEDs
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    Serial.begin(9600);


  unsigned char i = 0;
  tasks[i].state = SM1_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM1_Tick;
  i++;
  tasks[i].state = SM2_INIT;
  tasks[i].period = 500;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 500; // GCD

}


void loop() {
  button = digitalRead(2);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
  // put your main code here, to run repeatedly:
  unsigned char i;
  for (i = 0; i < tasksNum; ++i) {
     if ( (millis() - tasks[i].elapsedTime) >= tasks[i].period) {
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elapsedTime = millis(); // Last time this task was ran
      
     }
   }
  delay(delay_gcd); // GCD.
}
