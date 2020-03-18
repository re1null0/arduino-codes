#define DEBUG true
#define SSID "WirelessNetA"     // "SSID-WiFiname"
#define PASS "20031979" // "password"
#define IP "184.106.153.149"      // thingspeak.com ipip
#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <Event.h>
#include <Timer.h>
#include <SoftwareSerial.h>

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;   // the number of the LED pin
SoftwareSerial esp8266(10,11);
Timer t;
PulseSensorPlayground pulseSensor; 
String msg = "GET https://api.thingspeak.com/update?api_key=M2PB3719XPTZIZEL"; 
int buttonState = 0;         // variable for reading the pushbutton status


 
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}
 
void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
 
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
}
