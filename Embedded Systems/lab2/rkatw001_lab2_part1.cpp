/*
Name: Rahul Katwala
Video demo: https://youtube.com/shorts/aT7CAsZ8ttk
SSID: 862146702
Assignment: CS120B Lab 1 Part 1

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
enum states {start, Mode1,  Mode2} state;

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

void setup() {
  pinMode(8, INPUT);
  pinMode(9, INPUT_PULLUP);
  pinMode(A1, INPUT);
  
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
    b_buf = analogRead(A1);
    
    value = map(b_buf, 0, 1023, 0, 255);
//  Serial.print("b_buf: ");
  //  Serial.println(value);
  
    
    
    
    
    switch (state){
      
        
      case start:
        state = Mode1;
        break;

      case Mode1:
     // b_buf=15;
      //writeBuffer(b_buf);
      
      
        
        if (b_buf > 0x00){
          resetBuffer();
          b_buf = 0xFF;
        }
        else {
          resetBuffer();
          b_buf= 0;
        }
        
      
        for (int i = (b_size - 1); i >= 0; i--) {
        if ((b_buf >> i) & 0x01) {
        digitalWrite(b[i], HIGH);
        }
    }
        if(digitalRead(9) == LOW){
          state = Mode2;
        }
        else{
          state=Mode1;
        }

        
           if(digitalRead(9) == LOW){
             resetBuffer();
          state = Mode2;
        }
        else{
          state=Mode1;
        }
        
        break;

    

     case Mode2:
     //b_buf=1;
     //writeBuffer(b_buf);
     //Serial.println("Mode2");
    
        /*if(b_buf == 0x01){
          b_buf = 0xFF;
       }
        else if(b_buf <= 0x06){
          b_buf = 0x03;
        }
        else if (b_buf >= 0x07){
          b_buf = 0x00;
        }
        */
        unsigned char val;
        if(value == 0) val = 0x0F;
        else if(value <= 115) {resetBuffer(); val = 0x03;}
        else {resetBuffer(); val = 0x00;}
        //b_buf = val;
//        Serial.print("Value:" );
//        Serial.println(value);
        writeBuffer(val);
        
        
        if(digitalRead(8) == HIGH){
          resetBuffer();
          state = Mode1;
          
        }
        else{
          state = Mode2;
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
