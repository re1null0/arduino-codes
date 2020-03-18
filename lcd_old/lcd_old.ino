#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT_NEW.h"

LiquidCrystal_I2C _lcd1(0x3f, 16, 2);
int _dispTempLength1=0;
boolean _isNeedClearDisp1;

DHT _dht1;

struct _I2CRealRimeClockTime
{
byte seconds = 0;
byte minutes = 0;
byte Hours = 0;
byte weekday = 0;
byte day = 0;
byte month = 0;
byte year = 0;
unsigned long startTime = 0;
};
_I2CRealRimeClockTime _RTC2;
unsigned long _dht1LRT = 0UL;
unsigned long _dht1Tti = 0UL;
bool _trgs2 = 0;
String _RTC2_GetTime1_StrOut;
int _disp1oldLength = 0;
bool _trgs1 = 0;
bool _tim1I = 0;
bool _tim1O = 0;
unsigned long _tim1P = 0UL;
int _disp4oldLength = 0;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
bool _RTCAlO1 = 0;
int _disp2oldLength = 0;
int _disp3oldLength = 0;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
bool _trgrt3 = 0;
bool _trgrt3I = 0;
bool _trgrt1 = 0;
bool _trgrt1I = 0;
bool _trgt1 = 0;
bool _trgt1I = 0;
void setup()
{
Wire.begin();
delay(10);
Wire.beginTransmission(68);
Wire.write(0x0E);
Wire.write(B00000000);
Wire.write(B10001000);
Wire.endTransmission();
_RTC2.startTime = millis() - 1000;
pinMode(1, OUTPUT);
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
pinMode(10, OUTPUT);

//_lcd1.init();
_lcd1.backlight();
_dht1.setup(6);
_dht1LRT = millis();
_dht1Tti = millis(); 
}
void loop()
{if (_isNeedClearDisp1) {_lcd1.clear(); _isNeedClearDisp1= 0;}

 

 

//Плата:1
if(_isTimer(_dht1Tti, 1000)) {
if(_isTimer(_dht1LRT,( _dht1.getMinimumSamplingPeriod()))) {
_dht1.readSensor();
_dht1LRT = millis(); 
_dht1Tti = millis(); 
}
}
if (1) {
_dispTempLength1 = ((((String("h=")) + ((String((int(_dht1.humidity)), DEC))) + (String("%"))))).length();
if (_disp2oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp2oldLength = _dispTempLength1;
_lcd1.setCursor(0, 1);
_lcd1.print((((String("h=")) + ((String((int(_dht1.humidity)), DEC))) + (String("%")))));

_lcd1.print((((String("h=")) + ((String((int(100)), DEC))) + (String("ppm")))));
} else {
if (_disp2oldLength > 0) {_isNeedClearDisp1 = 1; _disp2oldLength = 0;} 
}
if(((int(_dht1.humidity))) < (70.00)) _trgs2 = 1;
if(((int(_dht1.humidity))) > (75.00)) _trgs2 = 0;
digitalWrite(2, !(_trgs2));
if (1) {
_dispTempLength1 = ((((String("t=")) + ((String((int(_dht1.temperature)), DEC))) + (String("C"))))).length();
if (_disp1oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp1oldLength = _dispTempLength1;
_lcd1.setCursor(0, 0);
_lcd1.print((((String("t=")) + ((String((int(_dht1.temperature)), DEC))) + (String("C")))));
} else {
if (_disp1oldLength > 0) {_isNeedClearDisp1 = 1; _disp1oldLength = 0;} 
}
if (((int(_dht1.temperature))) < (25.00)) { if (_trgrt1I) { _trgrt1 = 0;} else {_trgrt1 = 1; _trgrt1I = 1;} } else {_trgrt1 = 0; _trgrt1I = 0;}; 
if (((int(_dht1.temperature))) > (24.00)) { if (_trgrt2I) { _trgrt2 = 0;} else {_trgrt2 = 1; _trgrt2I = 1;} } else {_trgrt2 = 0; _trgrt2I = 0;}; 
if(_trgrt1) _trgs1 = 1;
if(_trgrt2) _trgs1 = 0;
digitalWrite(1, _trgs1);

//Плата:2
if (1)
{ 
get3231Date(0x68, &_RTC2);
_RTCAlO1 = 1;
if (_RTC2.Hours != 23) { _RTCAlO1 = 0;}
if (_RTC2.minutes != 24) { _RTCAlO1 = 0;}
} else {_RTCAlO1 = 0;}
if (_RTCAlO1) { if (_trgrt3I) { _trgrt3 = 0;} else {_trgrt3 = 1; _trgrt3I = 1;} } else {_trgrt3 = 0; _trgrt3I = 0;}; 
if(_trgrt3) {_tim1O = 1; _tim1I = 1;} else { if(_tim1I) {_tim1I = 0; _tim1P = millis();} else { if (_tim1O) {if ( _isTimer(_tim1P, 28800000)) _tim1O = 0;}}}
digitalWrite(4, _tim1O);

//Плата:3
get3231Date(0x68, &_RTC2);
_RTC2_GetTime1_StrOut = ( _convertRealTimeClockNumberToString(_RTC2.Hours))+
String(":")+
( _convertRealTimeClockNumberToString(_RTC2.minutes))+
String(":")+
( _convertRealTimeClockNumberToString(_RTC2.seconds));
if (1) {
_dispTempLength1 = ((_RTC2_GetTime1_StrOut)).length();
if (_disp3oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp3oldLength = _dispTempLength1;
_lcd1.setCursor(6, 0);
_lcd1.print((_RTC2_GetTime1_StrOut));
} else {
if (_disp3oldLength > 0) {_isNeedClearDisp1 = 1; _disp3oldLength = 0;} 
}
if (1) {if (! _gen1I) { _gen1I = 1; _gen1O = 1; _gen1P = millis(); } } else { _gen1I = 0 ; _gen1O= 0; } if (_gen1I ) { if (_gen1O) { if ( _isTimer( _gen1P , 60000 )) { _gen1P = millis(); _gen1O = 0; } } else { if ( _isTimer( _gen1P , 120000 )) { _gen1P = millis(); _gen1O = 1; } } }
bool _tmp1 = _gen1O;
if (_tmp1) { if (! _trgt1I) _trgt1 = ! _trgt1; } 
_trgt1I = _tmp1; 
if (!(_trgt1)) {
_dispTempLength1 = (String("water on")).length();
if (_disp4oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp4oldLength = _dispTempLength1;
_lcd1.setCursor(6, 1);
_lcd1.print(String("water on"));
} else {
if (_disp4oldLength > 0) {_isNeedClearDisp1 = 1; _disp4oldLength = 0;} 
}
digitalWrite(10, !(_trgt1));

 


}
bool _isTimer(unsigned long startTime, unsigned long period )
{
unsigned long currentTime;
currentTime = millis();
if (currentTime>= startTime) {return (currentTime>=(startTime + period));} else {return (currentTime >=(4294967295-startTime+period));}
}
void get3231Date(int addres, struct _I2CRealRimeClockTime *timeStruct)
{
if (!(_isTimer ((timeStruct ->startTime), 250))) {
return;
}
Wire.beginTransmission( addres);
Wire.write(0x00);
Wire.endTransmission();
Wire.requestFrom(addres, 7);
if (Wire.available()) {
byte seconds = Wire.read();
byte minutes = Wire.read();
byte hours = Wire.read();
byte day = Wire.read();
byte date = Wire.read();
byte month = Wire.read();
byte year = Wire.read();
timeStruct -> seconds = (((seconds & B11110000) >> 4) * 10 + (seconds & B00001111));
timeStruct -> minutes = (((minutes & B11110000) >> 4) * 10 + (minutes & B00001111));
timeStruct -> Hours = (((hours & B00110000) >> 4) * 10 + (hours & B00001111));
timeStruct -> weekday = (day & B00000111);
timeStruct -> day = (((date & B00110000) >> 4) * 10 + (date & B00001111));
timeStruct -> month = (((month & B00010000) >> 4) * 10 + (month & B00001111));
timeStruct -> year = (((year & B11110000) >> 4) * 10 + (year & B00001111));
} timeStruct ->startTime = millis();
}
String _convertRealTimeClockNumberToString(byte value)
{
if (value > 9) {
return String(value, DEC);
}
return (String("0") + String(value, DEC));
}

