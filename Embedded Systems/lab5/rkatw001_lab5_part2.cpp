/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/hzTVfz6gjL0
SSID: 862146702
Assignment: CS120B Lab 5 Part 2

*/
//-------------------------------------------------------------------------------


enum States{INIT, normal} state;
//unsigned long lastRan;
int button = 0;

int xPosition = 0;
int yPosition = 0;
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
            state = normal;
        break;
      case normal:
          if (button == 0){
            temp = 0;
            b_temp = 0;
            resetBuffer();
          }
          else if( xPosition > 900){
            temp = temp | 0x04;
            b_temp = temp;
          }
          else if(xPosition < 300){
            temp = temp | 0x08;
            b_temp = temp;
          }
          else if(yPosition > 900){
            temp = temp | 0x02;
            b_temp = temp;
          }
          else if(yPosition < 100){
            temp = temp | 0x01;
            b_temp = temp;
          }

          writeBuffer(b_temp);
          Serial.print("X: ");
  Serial.print(xPosition);
  Serial.print(" | Y: ");
  Serial.print(yPosition);
  Serial.print(" | Button: ");
  Serial.println(button);
          state = normal;
          break;
          default:
          break;
        
    }
}


    


void setup() {
    // OUTPUT is a defined macro in Arduino!
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);
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
    xPosition = analogRead(A0);
  yPosition = analogRead(A1);
  button = digitalRead(2);
    delay(100);
    Tick();
}
