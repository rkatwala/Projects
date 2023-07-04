/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/riGk3J0Anvs
SSID: 862146702
Assignment: CS120B Lab 5 Part 3

*/
//-------------------------------------------------------------------------------


enum States{INIT, normal, finish} state;
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
            counter = 0;
            state = finish;
          }
          else{ state = normal;}
          break;
          
          case finish:
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
            if(button == 0){
              counter = 0;
              state = normal;
            }
           else{
            state = finish;
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
    delay(500);
    Tick();
}
