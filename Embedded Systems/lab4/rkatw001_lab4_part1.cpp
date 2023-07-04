/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/NLab8OrdFSE
SSID: 862146702
Assignment: CS120B Lab 4 Part 1

*/
//-------------------------------------------------------------------------------


// Array of Output Pin variables, set to the pins being used
const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};
// Output Buffer
int b_buf = 0x00;
// Input Variables
//int mode = 0;
// Serial Monitor Buffer
int s_buf = 0x00;
enum states {start, pause, active, reset} state;
unsigned char temp = 0;
unsigned char mode = 0;
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
  
  if (mode ==0){
  if(temp ==0 ){
      b_buf=9;
    temp = b_buf;
    return;
      //counter++;
      //resetBuffer();
    }
  if(temp == 11){
    b_buf = 9;
    temp = b_buf;
    return;
  }
    
  if(temp == 9){
    b_buf = 6;
    temp = b_buf;
    return;
  }
    if(temp==6){
    b_buf= 1;
    temp = b_buf;
    return;
  }
    if(temp == 0x01){
      b_buf=11;
      temp = b_buf;
  }
  }
  
  
  else {
    
    if(temp ==0 ){
      b_buf=0x03;
    temp = b_buf;
    return;
      //counter++;
      //resetBuffer();
    }
  if(temp == 3){
    b_buf = 0x06;
    temp = b_buf;
    return;
  }
    
  if(temp == 6){
    b_buf = 12;
    temp = b_buf;
    return;
  }
    if(temp==12){
      b_buf=15;
      temp = b_buf;
      return;
  }
    if(temp == 15){
      b_buf=3;
     temp = b_buf;
    }
    
  }
  
}

void pullUp(){
  if(mode ==0){
  if(temp ==0){
    b_buf =11;
    temp = b_buf;
    return;
  }
  if(temp ==11){
    b_buf =1;
    temp = b_buf;
    return;
  }
   if(temp ==1){
    b_buf =6;
    temp = b_buf;
    return;
  }
   if(temp ==6){
    b_buf =9;
    temp = b_buf;
    return;
  }
  
  if(temp ==9){
    b_buf =11;
    temp = b_buf;
    return;
  }
  }
  
  else{
  if(temp ==3){
    b_buf =15;
    temp = b_buf;
    return;
  }
  if(temp ==15){
    b_buf =12;
    temp = b_buf;
    return;
  }
   if(temp ==12){
    b_buf =6;
    temp = b_buf;
    return;
  }
   if(temp ==6){
    b_buf =3;
    temp = b_buf;
    return;
  }
  
  if(temp ==0){
    b_buf =11;
    temp = b_buf;
    return;
  }
  }
    
  
}


void setup() {
 // pinMode(8, INPUT);
  //pinMode(9, INPUT_PULLUP);
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
  switch (state){
      
        
      case start:
        state = active;
        break;

      case active:
     // b_buf=15;
      
      mode = 0;
          //if(digitalRead(8) == HIGH) {
    
               pullDown();
              resetBuffer();
              writeBuffer(b_buf);
            /*state = active;
              Serial.print("button pressed - temp: ");
              Serial.println(temp);
    
          }
          
         
          if(digitalRead(9) == LOW){
        
            pullUp();
              resetBuffer();
              writeBuffer(b_buf);
              Serial.print("button pressed - temp: ");
              Serial.println(temp);
              //state = active;
          }
      */
     // Serial.print("active: ");
      //Serial.println(b_buf);
      //Serial.print("light: ");
      //Serial.println(value);
      if (value < 8){
        temp = 3;
        b_buf=3;
        resetBuffer();
        writeBuffer(b_buf);
        state = reset;
      }

      else{
        
        state = active;
      }
      
        
        break;
        
      
     case reset:
      mode = 1;
      //Serial.print("reset: ");
      //Serial.println(b_buf);
      //if(digitalRead(8) == HIGH) {
    
               pullDown();
        resetBuffer();
              writeBuffer(b_buf);
            //state = active;
          //    Serial.print("button pressed - temp: ");
              //Serial.println(temp);
    
  //        }
          
         
      /*    if(digitalRead(9) == LOW){
      //
            pullUp();
              resetBuffer();
              writeBuffer(b_buf);
              Serial.print("button pressed - temp: ");
              Serial.println(temp);
              //state = active;
          }*/
      
      if(value >8){
        temp = 1;
        b_buf = 1;
        resetBuffer();
        writeBuffer(b_buf);
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
    
  //Serial.print("value: ");
    //Serial.println(value);
  
    delay(1000);
    
    
    
    Tick();
    
  
   
}
