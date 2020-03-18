/*  Demonstration of sending data to an Android App via Bluetooth. This example 
    uses SoftwareSerial on pins 2 and 3 
    
   Characters are read in from the keyboard, output on the Serial Monitor and written to 
   the Bluetooth device using SoftwareSerial 
      
*/  
     
#include <SoftwareSerial.h>
  
#define rxPin 2                     // define SoftwareSerial rx data pin  
#define txPin 3                     // define SoftwareSerial tx data pin  
  
SoftwareSerial blueTooth(rxPin, txPin);  // create instance of SoftwareSerial  
  
void setup()  
{  
  Serial.begin(9600);            // Start hardware Serial  
  blueTooth.begin(9600);         // Start SoftwareSerial  
}  
  
void loop()  
{  
    char c;  
    
       c = Serial.read();  
        
       Serial.println(c);             // Write the character to the Serial Monitor  
        
       blueTooth.write (c);           // Write the character to Bluetooth  
     
}  
