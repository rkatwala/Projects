/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/3nwa39l6Z8g?feature=share 
SSID: 862146702
Assignment: CS120B Lab 5 Part 1

*/
//-------------------------------------------------------------------------------


// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};

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

enum SM1_States { SM1_INIT, SM1_S0};
int SM1_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM1_INIT:
         //State Transition
            state = SM1_S0;
        break;
      case SM1_S0:
         if(counter == 0){
          counter = 1;
          resetBuffer();
          writeBuffer(counter);
         }
         else if(counter  ==1){
          counter++;
          resetBuffer();
          writeBuffer(counter);
         }
         else if(counter ==2){
          counter =4;
          resetBuffer();
          writeBuffer(counter);
         }
         else if (counter ==4){
          counter = 1;
          resetBuffer();
          writeBuffer(counter);
         }
         state = SM1_S0;
         //State Transition
        break;
    }

    return state;
}

enum SM2_States { SM2_INIT, SM2_S0, SM2_S1};
int SM2_Tick(int state){
    //Read thing
    switch(state){ // State transitions
      case SM2_INIT:
         //State Transition
            state = SM2_S0;
        break;
      case SM2_S0:
            if(button == 1){
              state = SM2_S0;
            }
            else{
              state = SM2_S1;
              unsigned char temp = counter | 0x08;
              writeBuffer(temp);
            }
       case SM2_S1:
          if(button ==0){
            state = SM2_S1;
            unsigned char temp = counter | 0x08;
            writeBuffer(temp);
          }
          else{
            resetBuffer();
            writeBuffer(counter);
            state = SM2_S0;
          }
        //State Transition
        break;
      
    }

    return state;
}






void setup() {
    //some set up (Default Arduino Function)
counter = 0;
pinMode(2, INPUT_PULLUP);
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
  tasks[i].period = 100;
  tasks[i].elapsedTime = 0;
  tasks[i].TickFct = &SM2_Tick;

  delay_gcd = 100; // GCD

}


void loop() {
  button = digitalRead(2);
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
