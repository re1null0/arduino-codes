const int lightPin=13;
unsigned int data;
String incoming;
void setup() {
  Serial.begin(9600);
  pinMode(lightPin,OUTPUT);
}

void loop() {
    while(Serial.available()>0){
      data=Serial.read();
        incoming = Serial.readStringUntil('\n');
        if(data=='Y')digitalWrite(lightPin,HIGH);
        if(data=='N')digitalWrite(lightPin,LOW);
        if(data=='T')Serial.println("Temperature is: 25 ");
        if(data=='C')Serial.println("CO2 level is 240");
        if(data=='H')Serial.println("Humidity is: 14");
        
    }
  
}
