const int lightPin=13;
unsigned int data;
void setup() {
  Serial.begin(9600);
  pinMode(lightPin,OUTPUT);
  
}

void loop() {
    while(Serial.available()>0){
      data=Serial.read();
        if(data=='Y')digitalWrite(lightPin,HIGH);
        if(data=='N')digitalWrite(lightPin,LOW);
    }
  
}
