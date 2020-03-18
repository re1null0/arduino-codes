unsigned int data;
int value;
void setup() 
{
    Serial.begin(9600);
}

void loop() 
{
    float sensor_volt;
    float RS_gas; // Get value of RS in a GAS
    float ratio; // Get ratio RS_GAS/RS_air
    float BAC;
    int sensorValue = analogRead(A0);
    sensor_volt=(float)sensorValue/1024*5.0;
    RS_gas = (5.0-sensor_volt)/sensor_volt; // omit *RL

   /*-Replace the name "0.01" with the value of 0.01 in the demo of First Test -*/
    ratio = RS_gas/0.01;  
    BAC = 0.1896*pow(ratio, 2) - (8.6178*ratio/10) + 1.0792;   //BAC in mg/L
    Serial.print("BAC = ");
    Serial.println(BAC*0.00001);  //convert to g/dL
    Serial.print("\n\n");
    delay(1000);
    while(Serial.available()>0){
      data=Serial.read();
      float BAC_new = BAC*0.000000001;
        if(data=='A')Serial.println(BAC_new);
        
    }
}
