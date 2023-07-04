/*
Name: Rahul Katwala
Video demo: https://youtu.be/055iBBVWzYE
SSID: 862146702
Assignment: CS120B Lab 6 Part 3

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
unsigned char list[4];


int val;
unsigned char code[3];
int flag = 0;
enum SM1_States { SM1_INIT, SM1_S0, SM1_S1, SM1_S2};
int SM1_Tick(int state){
     //Read thing
    switch(state){ // State transitions
     
      case SM1_INIT:
        Serial.println("INIT");
          for(int i=0; i<4;i++){
            code[counter] = list[random(4)];
            counter++;
          }
         state = SM1_S0;
         counter = 0;
         break;
          
       case SM1_S0:
       resetBuffer();
         Serial.println("S0");
         if(button ==0){
          state = SM1_INIT;
          counter = 0;
          b_temp=0;
         }
         else{
            if (b_temp%2==0){
              writeBuffer(code[counter]);
              counter++;
            }
            else {
              resetBuffer();
            }
            if(b_temp ==5){
              state = SM1_S1;
              counter = 0;
              b_temp = 0;
            }
            else{
            
              state = SM1_S0;
              b_temp++;
            }
         }
            break;

        case SM1_S1:
       
        
        resetBuffer();
        Serial.println("S1");
          if(counter ==3){
            state = SM1_S2;
            counter = 0;
            b_temp =0;
            temp =0;
          }
          if (button == 0){
            temp = 0;
            b_temp = 0;
            resetBuffer();
            state = SM1_INIT;
          }
          else {
          if( xPosition > 900){
            val = 8;
            if (val == code[counter]){
            counter++;
            //state = SM1_S1;
         }
         else{
          flag = 9;
         }
            temp = temp | 0x04;
            b_temp = temp;
            writeBuffer(8);
          }
          else if(xPosition < 300){
            val = 1;
            if (val == code[counter]){
            counter++;
            //state = SM1_S1;
         }
         else{
          flag = 9;
         } writeBuffer(1);
            temp = temp | 0x08;
            b_temp = temp;
          }
          else if(yPosition > 900){
            val = 2;
            if (val == code[counter]){
            counter++;
            //state = SM1_S1;
         }
         else{
          flag = 9;
         } writeBuffer(2);
            temp = temp | 0x02;
            b_temp = temp;
          }
          else if(yPosition < 100){
             writeBuffer(4);
            val =4;
             if (val == code[counter]){
            counter++;
            //state = SM1_S1;
         }
         else{
          flag = 9;
         }
            temp = temp | 0x01;
            b_temp = temp;
          }
         if (counter == 3){
            
            state = SM1_S2;
            counter = 0;
         }
         else if(flag == 9){
          state = SM1_S0;
          counter = 0;
          temp = 0;
          b_temp = 0;
          flag = 0;
          
          
         }
         else{
          
          state = SM1_S1;
          
          
         }
          }

           
           
           Serial.print("Finish X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(button);
  Serial.println(counter);
           
           break;
          case SM1_S2:
              if(button == 0){
                state = SM1_INIT;
                counter =0;
                b_temp = 0;
                temp = 0;
                val = 0;
              }
              else{
              if(counter % 2 ==0){
                writeBuffer(15);
              }
              else{
                resetBuffer();
              }
              counter++;
              state = SM1_S2;
              
              }
              break;
          default:
          break;
        
    }
    //return state;
    return state;
}

int c = 0;

enum SM2_States { SM2_INIT};
int SM2_Tick(int state){
    //Read thing
    switch(state){
   

     case SM2_INIT:
      
        
       
            if(c < 4 && c % 2 == 0){
              tone(3, 349.23);
            }
            
            else if(c < 8 && c % 2 == 0){
              tone(3, 440.00);
            }
            else if(c < 12 && c % 2 == 0){
              tone(3, 293.66);
            }
            else if(c < 16&& c % 2 == 0){
              tone(3, 261.63);
            }
            else if(c < 20&& c % 2 == 0){
              tone(3, 493.88);
            }
            else{
              noTone(3);
            }
            c++;
            if(c > 20){
              c =0;
            }
            state = SM2_INIT;
         
      break;
      default: break;
      
  }

    return state;
}






void setup() {
  randomSeed(analogRead(3));
    //some set up (Default Arduino Function)
pinMode(A0, INPUT);
    pinMode(A1, INPUT);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
  //activate pull-up resistor on the push-button pin
  pinMode(2, INPUT_PULLUP);
  //pinMode(3, OUTPUT);
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
  list[0] = 1;
  list[1] = 2;
  list[2] = 4;
  list[3] = 8;
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
