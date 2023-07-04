/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/c-xCKUjkTes
SSID: 862146702
Assignment: CS120B Lab 1 Part 2

*/
//-------------------------------------------------------------------------------

// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables
int counter = 0;
// Serial Monitor Buffer
int s_buf = 0x00;
int temp = 0;
/* 's' is an array of integers of size 8. Note that arrays start at 0
 We will use this to be able to see the individual bit values of the s_buf

 */
const int s_size = 8;
int s[s_size];

// We can also define our own helper functions. It is a good idea to use helper functions whenever they make sense.
// Normally we also define the return type (void for none)

// Read from the serial monitor into s_buf and the s[] array for individual bits
void readData()
{
  
 // int counter = 0;
  while(digitalRead(8) == HIGH) {
    
   pullDown();
  
    
    
  
  }
  
  
  
  
  while(digitalRead(9) == LOW){
    pullUp();
  }

  for(int i = (s_size - 1); i>=0; i--)  {
        s[i] = (s_buf >> i) & 0x01; // What's going on here?
        // ">>" bit shifting
        // "&" bit masking
    }

}

void pullDown(){
  if(b_buf ==0 ){
      s_buf=0x01;
      //counter++;
      //resetBuffer();
    }
    
       else {
      
      if(b_buf == 0x0F){
        s_buf = 0;
        //counter++;
      }
      else{
        s_buf = 1+(b_buf << 1);
      //  counter++;
      }
    
    }
}

void pullUp(){
  if((b_buf == 0)){
      s_buf = 0x0F;
      
    }
       else{
    s_buf = b_buf >> 1;
        
       }
}

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




void setup() {
    // OUTPUT is a defined macro in Arduino!
    pinMode(8, INPUT);
  pinMode(9, INPUT_PULLUP);
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    // We will also read from the serial monitor
    Serial.begin(9600);
  
}

void loop() {
    readData();
    resetBuffer();
    // Note that here we arbitrarily connect b_buf & s_buf together. The important point is that we preserve the current value of the output buffer into a variable b_buf before writing it to the pins. If we resetBuffer or readData() again, we still know the values the output is set to, because it is in b_buf.
    b_buf = s_buf;
    writeBuffer(b_buf);
   
}
