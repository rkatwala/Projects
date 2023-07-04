/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/TUNwX5now9k
SSID: 862146702
Assignment: CS120B Lab 5 Part 1

*/
//-------------------------------------------------------------------------------


enum States{INIT, S0, pressPause, releasePause} state;
//unsigned long lastRan;
int button = 0;
unsigned char temp;
// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {8, 9, 10, 11};
const int xAxis = A0; // Recall that A0 is really a number under the hood.
const int light_pattern_size = 2;
const char light_pattern[light_pattern_size] = {0x00, 0x0F};

const char sound_pattern_size = 2;
//const double sound_pattern[sound_pattern_size] = {261.63, 293.66}; // C4, D4

const int buzzer = 3;

unsigned char counter = 0;
unsigned char b_temp;

//const int xAxis_median = 100; // Adjust this if needed

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

int Tick(){
    //Read thing
    switch(state){ // State transitions
      case INIT:
            Serial.println("state init");
         //State Transition
            state = S0;
        break;
      case S0:
       // button = digitalRead(2);
         // int buttonState = digitalRead(2);
          if(button == 0){
            noTone(3);
            state = pressPause;
          }

          
          else{
          
          playSong(counter);
          counter++;
          if(counter == 20){
            counter = 0;
            resetBuffer();
            temp = 0;
            b_temp = 0;
            
  }

  
        if(counter ==18 || counter ==19){
          temp = 15;
          b_temp = temp;
          writeBuffer(b_temp);
        }
        Serial.print("state song: counter:    ");
          
          Serial.println(counter);
          Serial.print("percentage:    ");
          Serial.println(temp);
          state = S0;
          }
          break;

       case pressPause:
       noTone(3);
      // button = digitalRead(2);
       Serial.println("state pausepress");
       Serial.println(button);
        if(button == 1){
          state = releasePause;
        }
          else{
            state = pressPause;
          }
         break;

        case releasePause:
        noTone(3);
        Serial.print("state pause :     ");
        Serial.println(button);
        //button = digitalRead(2);
          if(button == 0){
            state = S0;
          }
          else{
            state = releasePause;
          }
          break;
       default:
       break;
       
    }
}

void playSong(int i){
  if(i<5){
    tone(3, 261.63);
  }
  else if(i<10){
    tone(3, 293.66);
  }
  else if(i<15){
    tone(3, 349.23);
  }
  else{
    tone(3, 440.00);
  }
  if(i<=4){
    temp = 0;
    b_temp = temp;
  }
  if(i > 4){
    temp = 0x01;
    b_temp=temp;
  }
  if(i > 9){
    temp = 0x03;
    b_temp =temp;
  }
  if(i> 14){
    temp = 0x07;
    b_temp = temp;
  }
  if(i>18){
    temp = 15;
    b_temp = temp;
  }
  writeBuffer(b_temp);
  //counter++;
  
  
}
    


void setup() {
    // OUTPUT is a defined macro in Arduino!
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);

  //activate pull-up resistor on the push-button pin
  pinMode(2, INPUT_PULLUP);
    counter = 0;
    temp = 0;
  b_temp=0;
  state=INIT;
    for(int i = 0; i < b_size; i++)
        {
            pinMode(b[i], OUTPUT);
        }
    // We will also read from the serial monitor
    Serial.begin(9600);
}

void loop() {
    button = digitalRead(2);
    delay(500);
    Tick();
}
