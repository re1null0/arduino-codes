#include <LiquidCrystal_I2C.h>

#include <Wire.h>
#include "DHT_NEW.h"

LiquidCrystal_I2C _lcd1();
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
_I2CRealRimeClockTime _RTC1;
bool _trgr2 = 0;
bool _RTCAlO1 = 0;
bool _pzs1OES = 0;
String _RTC1_GetTime1_StrOut;
bool _RTCAlO2 = 0;
bool _trgrt3 = 0;
bool _trgrt3I = 0;
bool _trgr3 = 0;
int _disp3oldLength = 0;
bool _gen3I = 0;
bool _gen3O = 0;
unsigned long _gen3P = 0UL;
bool _trgrt4 = 0;
bool _trgrt4I = 0;
bool _trgrt6 = 0;
bool _trgrt6I = 0;
bool _trgrt1 = 0;
bool _trgrt1I = 0;
bool _gen1I = 0;
bool _gen1O = 0;
unsigned long _gen1P = 0UL;
int _disp5oldLength = 0;
unsigned long _dht1LRT = 0UL;
unsigned long _dht1Tti = 0UL;
int _disp1oldLength = 0;
bool _gen2I = 0;
bool _gen2O = 0;
unsigned long _gen2P = 0UL;
bool _trgrt2 = 0;
bool _trgrt2I = 0;
int _disp2oldLength = 0;
bool _trgr1 = 0;
bool _trgrt5 = 0;
bool _trgrt5I = 0;
int _disp4oldLength = 0;
void setup()
{
Wire.begin();
delay(10);
Wire.beginTransmission(68);
Wire.write(0x0E);
Wire.write(B00000000);
Wire.write(B10001000);
Wire.endTransmission();
_RTC1.startTime = millis() - 1000;
pinMode(3, OUTPUT);
pinMode(2, OUTPUT);
pinMode(4, OUTPUT);
pinMode(10, OUTPUT);
pinMode(8, OUTPUT);

_lcd1.begin();
_lcd1.init();
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
if (((int(_dht1.humidity))) <= (70)) { if (_trgrt4I) { _trgrt4 = 0;} else {_trgrt4 = 1; _trgrt4I = 1;} } else {_trgrt4 = 0; _trgrt4I = 0;}; 
if (((int(_dht1.humidity))) >= (75)) { if (_trgrt3I) { _trgrt3 = 0;} else {_trgrt3 = 1; _trgrt3I = 1;} } else {_trgrt3 = 0; _trgrt3I = 0;}; 
if(_trgrt4) _trgr2 = 0;
if(_trgrt3) _trgr2 = 1;
digitalWrite(2, _trgr2);
if (1) {
_dispTempLength1 = ((((((String("h=")) + ((String((int(_dht1.humidity)), DEC))))) + (String("%"))))).length();
if (_disp2oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp2oldLength = _dispTempLength1;
_lcd1.setCursor(0, 1);
_lcd1.print((((((String("h=")) + ((String((int(_dht1.humidity)), DEC))))) + (String("%")))));
} else {
if (_disp2oldLength > 0) {_isNeedClearDisp1 = 1; _disp2oldLength = 0;} 
}
if (((int(_dht1.temperature))) <= (24)) { if (_trgrt2I) { _trgrt2 = 0;} else {_trgrt2 = 1; _trgrt2I = 1;} } else {_trgrt2 = 0; _trgrt2I = 0;}; 
if (((int(_dht1.temperature))) >= (25)) { if (_trgrt1I) { _trgrt1 = 0;} else {_trgrt1 = 1; _trgrt1I = 1;} } else {_trgrt1 = 0; _trgrt1I = 0;}; 
if(_trgrt2) _trgr1 = 0;
if(_trgrt1) _trgr1 = 1;
digitalWrite(3, !(_trgr1));
if (1) {
_dispTempLength1 = ((((((String("t=")) + ((String((int(_dht1.temperature)), DEC))))) + (String("C"))))).length();
if (_disp1oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp1oldLength = _dispTempLength1;
_lcd1.setCursor(0, 0);
_lcd1.print((((((String("t=")) + ((String((int(_dht1.temperature)), DEC))))) + (String("C")))));
} else {
if (_disp1oldLength > 0) {_isNeedClearDisp1 = 1; _disp1oldLength = 0;} 
}

//Плата:2
if (1)
{ 
get3231Date(0x68, &_RTC1);
_RTCAlO1 = 1;
if (_RTC1.Hours != 6) { _RTCAlO1 = 0;}
} else {_RTCAlO1 = 0;}
if (_RTCAlO1) { if (_trgrt5I) { _trgrt5 = 0;} else {_trgrt5 = 1; _trgrt5I = 1;} } else {_trgrt5 = 0; _trgrt5I = 0;}; 
if (1)
{ 
get3231Date(0x68, &_RTC1);
_RTCAlO2 = 1;
if (_RTC1.Hours != 22) { _RTCAlO2 = 0;}
} else {_RTCAlO2 = 0;}
if (_RTCAlO2) { if (_trgrt6I) { _trgrt6 = 0;} else {_trgrt6 = 1; _trgrt6I = 1;} } else {_trgrt6 = 0; _trgrt6I = 0;}; 
if(_trgrt6) _trgr3 = 0;
if(_trgrt5) _trgr3 = 1;
digitalWrite(4, _trgr3);
get3231Date(0x68, &_RTC1);
_RTC1_GetTime1_StrOut = ( _convertRealTimeClockNumberToString(_RTC1.Hours))+
String(":")+
( _convertRealTimeClockNumberToString(_RTC1.minutes))+
String(":")+
( _convertRealTimeClockNumberToString(_RTC1.seconds));
if (1) {
_dispTempLength1 = ((_RTC1_GetTime1_StrOut)).length();
if (_disp3oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp3oldLength = _dispTempLength1;
_lcd1.setCursor(7, 0);
_lcd1.print((_RTC1_GetTime1_StrOut));
} else {
if (_disp3oldLength > 0) {_isNeedClearDisp1 = 1; _disp3oldLength = 0;} 
}

//Плата:3
if (1) {if (! _gen1I) { _gen1I = 1; _gen1O = 1; _gen1P = millis(); } } else { _gen1I = 0 ; _gen1O= 0; } if (_gen1I ) { if (_gen1O) { if ( _isTimer( _gen1P , 2000 )) { _gen1P = millis(); _gen1O = 0; } } else { if ( _isTimer( _gen1P , 183000 )) { _gen1P = millis(); _gen1O = 1; } } }
digitalWrite(10, !(_gen1O));

//Плата:4
if (( (analogRead (0))) <= (100)) { if (! _gen2I) { _gen2I = 1; _gen2O = 1; _gen2P = millis(); } } else { _gen2I = 0 ; _gen2O= 0;}
if (_gen2I) { if ( _isTimer ( _gen2P , 1000 )) { _gen2P = millis(); _gen2O = ! _gen2O;}}
if (_gen2O) {
_dispTempLength1 = (String("add water")).length();
if (_disp4oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp4oldLength = _dispTempLength1;
_lcd1.setCursor(7, 1);
_lcd1.print(String("add water"));
} else {
if (_disp4oldLength > 0) {_isNeedClearDisp1 = 1; _disp4oldLength = 0;} 
}
if(_gen2O)
{if((!_pzs1OES)){ tone(7, 1200); _pzs1OES =1;}} else {if(_pzs1OES){noTone(7); _pzs1OES =0; }}

if (( (analogRead (1))) <= (500)) {if (! _gen3I) { _gen3I = 1; _gen3O = 1; _gen3P = millis(); } } else { _gen3I = 0 ; _gen3O= 0; } if (_gen3I ) { if (_gen3O) { if ( _isTimer( _gen3P , 30000 )) { _gen3P = millis(); _gen3O = 0; } } else { if ( _isTimer( _gen3P , 120000 )) { _gen3P = millis(); _gen3O = 1; } } }
digitalWrite(8, _gen3O);
//Плата:5
if (1) {
_dispTempLength1 = ((((String("CO2=")) + ((String( (analogRead (1)), DEC)))))).length();
if (_disp5oldLength > _dispTempLength1) {_isNeedClearDisp1 = 1;} 
_disp5oldLength = _dispTempLength1;
_lcd1.setCursor(0, 3);
_lcd1.print((((String("CO2=")) + ((String( (analogRead (100)), DEC))))));
} else {
if (_disp5oldLength > 0) {_isNeedClearDisp1 = 1; _disp5oldLength = 0;} 
}

 


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
