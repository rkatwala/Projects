/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/3nHWEKk6SFA
SSID: 862146702
Assignment: CS120B Lab 3 Part 2

*/
//-------------------------------------------------------------------------------


// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables
int mode = 0;
// Serial Monitor Buffer
int s_buf = 0x00;
enum states {start, active, reset} state;
unsigned char temp = 0;
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
    if(Serial.available())
        s_buf = Serial.parseInt();

    for(int i = (s_size - 1); i>=0; i--)  {
        s[i] = (s_buf >> i) & 0x01; // What's going on here?
        // ">>" bit shifting
        // "&" bit masking
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

void pullDown(){
  
  
  if(temp ==0 ){
      b_buf=0x01;
    temp = b_buf;
    return;
      //counter++;
      //resetBuffer();
    }
  if(temp == 1){
    b_buf = 0x03;
    temp = b_buf;
    return;
  }
    
  if(temp == 3){
    b_buf = 7;
    temp = b_buf;
    return;
  }
  else{
    b_buf= 0x0F;
    temp = b_buf;
  }
  
  
}

void pullUp(){
  
  if(temp ==0){
    b_buf =0;
    temp = b_buf;
    return;
  }
  if(temp ==1){
    b_buf =0;
    temp = b_buf;
    return;
  }
   if(temp ==3){
    b_buf =1;
    temp = b_buf;
    return;
  }
   if(temp ==7){
    b_buf =3;
    temp = b_buf;
    return;
  }
  
  if(temp ==15){
    b_buf =7;
    temp = b_buf;
    return;
  }
       
}


void setup() {
  pinMode(8, INPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(A1, INPUT);
  temp = 0;
  b_buf=0;
  state=start;
    // OUTPUT is a defined macro in Arduino!
    for(int i = 0; i < b_size; i++)
    {
        pinMode(b[i], OUTPUT);
    }
    // We will also read from the serial monitor
    Serial.begin(9600);
}
void Tick(){
  static unsigned char value = 0;
    
    // Note that here we arbitrarily connect b_buf & s_buf together. The important point is that we preserve the current value of the output buffer into a variable b_buf before writing it to the pins. If we resetBuffer or readData() again, we still know the values the output is set to, because it is in b_buf.
    value = analogRead(A1);
    
    value = map(value, 0, 1023, 0, 255);
  //Serial.print("value: ");
    //Serial.println(value);
  
    
    delay(200);
    
    
    switch (state){
      
        
      case start:
        state = active;
        break;

      case active:
     // b_buf=15;
        if(digitalRead(8) == HIGH) {
    
        pullDown();
        writeBuffer(b_buf);
        //state = active;
           // Serial.print("button pressed - temp: ");
        //Serial.println(temp);
    
      }
      
    
      if(digitalRead(9) == LOW){
        
        pullUp();
            resetBuffer();
          writeBuffer(b_buf);
        //    Serial.print("button pressed - temp: ");
        //Serial.println(temp);
            //state = active;
      }
      
      //Serial.print("active: ");
      //Serial.println(b_buf);
      //Serial.print("light: ");
      //Serial.println(value);
      if (value < 3){
        state = reset;
      }

      else{
        state = active;
      }
      
        
        break;
    
      
     case reset:
      resetBuffer();
      b_buf = 0;
      temp = 0;
      //Serial.print("reset: ");
      //erial.println(value);
      if (value > 2){
        state = active;
      }
      else{
        state = reset;
      }
  break;
  

      default:
        state = start;
        break;

    
      
    }
    
}


void loop() {
    Tick();
  
    
   

    
    


    
    
      
        
    
  
    
   

    
    
}
