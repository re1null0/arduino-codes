#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "DHT_NEW.h"
DHT _dht1;

SoftwareSerial Serial100(10, 11);

bool _modbusSlaveDataTable_0[4];
int _modbusSlaveAddresTable_0[4] = {0, 1, 2, 3};
int _modbusSlaveDataTable_4[4];
int _modbusSlaveAddresTable_4[4] = {2, 4, 6, 8};
byte _modbusSlaveBufferSize = 0;
byte _modbusSlaveLastRec = 0;
long _modbusSlaveTime;
byte _modbusSlaveBuffer[64];
const unsigned char _modbusSlave_fctsupported[] = {1, 5, 15, 3, 6, 16};
bool _trgt1 = 0;
bool _trgt1I = 0;
bool _changeNumber1_Out = 0;
int _changeNumber1_OLV;
bool _tim1I = 0;
bool _tim1O = 0;
unsigned long _tim1P = 0UL;
bool _SEEPR2OSN = 0;
bool _trgt2 = 0;
bool _trgt2I = 0;
bool _changeNumber2_Out = 0;
int _changeNumber2_OLV;
bool _trgt4 = 0;
bool _trgt4I = 0;
bool _trgt3 = 0;
bool _trgt3I = 0;
bool _SEEPR1OSN = 0;
unsigned long _dht1LRT = 0UL;
unsigned long _dht1Tti = 0UL;
void setup()
{
Serial100.begin(9600);
pinMode(7, OUTPUT);
pinMode(8, OUTPUT);
pinMode(9, OUTPUT);
pinMode(12, OUTPUT);

_dht1.setup(3);
_dht1LRT = millis();
_dht1Tti = millis(); 
}
void loop()
{int _tempVariable_int;
_modbusSlavePoll();

 

 

//Плата:1
bool _tmp1 = (_modbusSlaveDataTable_0[0]);
if (_tmp1) { if (! _trgt1I) _trgt1 = ! _trgt1; } 
_trgt1I = _tmp1; 
digitalWrite(7, !(_trgt1));
bool _tmp2 = (_modbusSlaveDataTable_0[1]);
if (_tmp2) { if (! _trgt2I) _trgt2 = ! _trgt2; } 
_trgt2I = _tmp2; 
digitalWrite(8, !(_trgt2));
bool _tmp3 = (_modbusSlaveDataTable_0[2]);
if (_tmp3) { if (! _trgt3I) _trgt3 = ! _trgt3; } 
_trgt3I = _tmp3; 
digitalWrite(9, !(_trgt3));
bool _tmp4 = (_modbusSlaveDataTable_0[3]);
if (_tmp4) { if (! _trgt4I) _trgt4 = ! _trgt4; } 
_trgt4I = _tmp4; 
if(_isTimer(_dht1Tti, 2000)) {
if(_isTimer(_dht1LRT,( _dht1.getMinimumSamplingPeriod()))) {
_dht1.readSensor();
_dht1LRT = millis(); 
_dht1Tti = millis(); 
}
}
_modbusSlaveDataTable_4[2] = _dht1.humidity;
_modbusSlaveDataTable_4[1] = _dht1.temperature;
if((_dht1.humidity) >= ((readIntegerFromEEPROM(0, 0, 0x0)))) {_tim1O = 1; _tim1I = 1;} else { if(_tim1I) {_tim1I = 0; _tim1P = millis();} else { if (_tim1O) {if ( _isTimer(_tim1P, ((readIntegerFromEEPROM(2, 0, 0x0)))*(60000))) _tim1O = 0;}}}
digitalWrite(12, !(( (_trgt4) || (_tim1O) )));
if (_changeNumber1_Out) {_changeNumber1_Out = 0;} else {_tempVariable_int = (_modbusSlaveDataTable_4[0]);
if (_tempVariable_int != _changeNumber1_OLV) {_changeNumber1_OLV = _tempVariable_int; _changeNumber1_Out = 1;}
}
if(_changeNumber1_Out){ if(!_SEEPR1OSN){(updateIntegerToEEPROM(0, 0, 0x0, ((_modbusSlaveDataTable_4[0]))));
_SEEPR1OSN=1;} }else{ if(_SEEPR1OSN){_SEEPR1OSN=0;}}
if (_changeNumber2_Out) {_changeNumber2_Out = 0;} else {_tempVariable_int = (_modbusSlaveDataTable_4[3]);
if (_tempVariable_int != _changeNumber2_OLV) {_changeNumber2_OLV = _tempVariable_int; _changeNumber2_Out = 1;}
}
if(_changeNumber2_Out){ if(!_SEEPR2OSN){(updateIntegerToEEPROM(2, 0, 0x0, ((_modbusSlaveDataTable_4[3]))));
_SEEPR2OSN=1;} }else{ if(_SEEPR2OSN){_SEEPR2OSN=0;}}

 


}
bool _isTimer(unsigned long startTime, unsigned long period )
{
unsigned long currentTime;
currentTime = millis();
if (currentTime>= startTime) {return (currentTime>=(startTime + period));} else {return (currentTime >=(4294967295-startTime+period));}
}
int modbusCalcCRC(byte length, byte bufferArray[])
{
unsigned int temp, temp2, flag;
temp = 0xFFFF;
for (unsigned char i = 0; i < length; i++) {
temp = temp ^ bufferArray[i];
for (unsigned char j = 1; j <= 8; j++) {
flag = temp & 0x0001;
temp >>= 1;
if (flag) temp ^= 0xA001;
}
}
temp2 = temp >> 8;
temp = (temp << 8) | temp2;
temp &= 0xFFFF;
return temp;
}
byte _modbusSlavePoll()
{
byte avalibleBytes = Serial100.available();
if (avalibleBytes == 0) return 0;
if (avalibleBytes != _modbusSlaveLastRec) {
_modbusSlaveLastRec = avalibleBytes;
_modbusSlaveTime = millis();
return 0;
}
if (!(_isTimer(_modbusSlaveTime, 5))) return 0;
_modbusSlaveLastRec = 0;
byte state = _modbusGetSlaveRxBuffer();
if (state < 7) {
return state;
}
if ((_modbusSlaveBuffer[0] != 1) && (_modbusSlaveBuffer[0] != 0)) return 0;
byte exception = _modbusValidateRequest();
if (exception > 0) {

if (exception != 255) { _modbusSlaveBuildException( exception );
_modbusSlaveSendTxBuffer();
} 
return exception;
}

switch ( _modbusSlaveBuffer[1] ) {
case 1 :
return process_modbus_FC1(0);
break;
case 5:
return process_modbus_FC5();
break;
case 15:
return process_modbus_FC15();
break;
case 3 :
return process_modbus_FC3(4);
break;
case 6 :
return process_modbus_FC6();
break;
case 16 :
return process_modbus_FC16();
break;
default:
break;
}
return 25;
}
byte _modbusValidateRequest() {
int msgCRC =
((_modbusSlaveBuffer[_modbusSlaveBufferSize - 2] << 8)
| _modbusSlaveBuffer[_modbusSlaveBufferSize - 1]);
if ( modbusCalcCRC( _modbusSlaveBufferSize - 2, _modbusSlaveBuffer ) != msgCRC ) { return 255;}
boolean isSupported = false;
for (uint8_t i = 0; i < sizeof( _modbusSlave_fctsupported ); i++) {
if (_modbusSlave_fctsupported[i] == _modbusSlaveBuffer[1]) {
isSupported = 1;
break;
}
}
if (!isSupported) { return 1;}
int intRegs = 0;
byte byteRegs;
switch ( _modbusSlaveBuffer[1] ) {
case 1:
if(!(checkModbusRange( word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3]) , word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5]) ,0))){return 2;}
break;
case 5:
if(!(checkModbusAddres( word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3]),0))){return 2;} 
break;
case 15 :
if(!(checkModbusRange(word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3]) , word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5]) ,0))){return 2;}
break;
case 6 :
if(!(checkModbusAddres(( word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3]) ),4))){return 2;} 
break;
case 3 :
case 16 :
if(!(checkModbusRange((word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3])), (word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5])),4))){return 2;} 
break;
}
return 0; // OK, no exception code thrown
}
bool checkModbusAddres(int addr, byte table)
{
return (!(( modbusSlaveIndexForAddres(addr,table)) == -1));
}
int modbusSlaveIndexForAddres(int addr, byte table)
{
int tableSize = 0;
switch (table) {
case 0:
tableSize = 4;
break;
case 4:
tableSize = 4;
break;
}
for (byte i = 0; i < tableSize; i++) {if((modbusSlaveAddresFromIndex(i,table)) == addr){return i;}}
return -1;
}
int modbusSlaveAddresFromIndex(byte index, byte table)
{
switch (table) {
case 0:
return _modbusSlaveAddresTable_0[index];
break;
case 4:
return _modbusSlaveAddresTable_4[index];
break;
}
return -1;
}
bool checkModbusRange(int startAddr, int addrNumber, byte table)
{
for (int i=0; i < addrNumber; i++) {if(!(checkModbusAddres((startAddr+i),table))){return false;}}
return true;
}
void _modbusSlaveBuildException( byte exception ) {
byte func = _modbusSlaveBuffer[1]; 
_modbusSlaveBuffer[0] = 1;
_modbusSlaveBuffer[1] = func + 0x80;
_modbusSlaveBuffer[ 2 ] = exception;
_modbusSlaveBufferSize = 3;}
void _modbusSlaveSendTxBuffer()
{
if(_modbusSlaveBuffer[0] == 0) {return;}
byte i = 0;
int crc = modbusCalcCRC( _modbusSlaveBufferSize,_modbusSlaveBuffer );
_modbusSlaveBuffer[ _modbusSlaveBufferSize ] = crc >> 8;
_modbusSlaveBufferSize++;
_modbusSlaveBuffer[ _modbusSlaveBufferSize ] = crc & 0x00ff;
_modbusSlaveBufferSize++;
Serial100.write( _modbusSlaveBuffer, _modbusSlaveBufferSize );
delay (5);
Serial100.flush();
_modbusSlaveBufferSize = 0;
}
byte _modbusGetSlaveRxBuffer()
{
boolean bBuffOverflow = false;
_modbusSlaveBufferSize = 0;
while (Serial100.available() ) {
_modbusSlaveBuffer[ _modbusSlaveBufferSize ] = Serial100.read();
_modbusSlaveBufferSize ++;
if (_modbusSlaveBufferSize >= 64) bBuffOverflow = true;
}
if (bBuffOverflow) {return -3; }
return _modbusSlaveBufferSize;
}
byte process_modbus_FC1(byte table)
{
byte bytesNo, bitsNo;
int currentCoil, coil;
bool value;
byte index;
int startCoil = word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[ 3] );
int coilNo = word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5] );
bytesNo = byte(coilNo / 8);
if (coilNo % 8 != 0) bytesNo ++;
_modbusSlaveBuffer[2] = bytesNo;
_modbusSlaveBufferSize = 3;
bitsNo = 0;
for (currentCoil = 0; currentCoil < coilNo; currentCoil++) {
coil = startCoil + currentCoil;
index = modbusSlaveIndexForAddres(coil, table);
if (table == 0) {value = _modbusSlaveDataTable_0[index]; } 
bitWrite(
_modbusSlaveBuffer[ _modbusSlaveBufferSize ],
bitsNo,
value);
bitsNo ++;
if (bitsNo > 7) {
bitsNo = 0;
_modbusSlaveBufferSize++;
}
}
if (coilNo % 8 != 0) _modbusSlaveBufferSize ++;
_modbusSlaveSendTxBuffer();
return _modbusSlaveBufferSize + 2;
}
byte process_modbus_FC3(byte table)
{
int startAddr = word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3] );
int byteRegsno = word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5] );
int i;
int value;
byte index;
_modbusSlaveBuffer[ 2 ] = byteRegsno * 2;
_modbusSlaveBufferSize = 3;
for (i = startAddr; i < startAddr + byteRegsno; i++) {
index = modbusSlaveIndexForAddres(i, table);
if (table == 4) {value = _modbusSlaveDataTable_4[index]; } 
_modbusSlaveBuffer[ _modbusSlaveBufferSize ] = highByte(value);
_modbusSlaveBufferSize++;
_modbusSlaveBuffer[ _modbusSlaveBufferSize ] = lowByte(value);
_modbusSlaveBufferSize++;
}
_modbusSlaveSendTxBuffer();
return _modbusSlaveBufferSize + 2;
}
byte process_modbus_FC5()
{
byte index;
int coil = word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3] );
index = modbusSlaveIndexForAddres(coil, 0);
_modbusSlaveDataTable_0[index] = (_modbusSlaveBuffer[4] == 0xff );
_modbusSlaveBufferSize = 6;
_modbusSlaveSendTxBuffer();
return _modbusSlaveBufferSize + 2;
}
byte process_modbus_FC15( ) 
{
byte frameByte, bitsNo;
byte currentCoil, coil;
byte index;
int startCoil = word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3] );
int coilNo = word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5] );
bitsNo = 0;
frameByte = 7;
for (currentCoil = 0; currentCoil < coilNo; currentCoil++) {
coil = startCoil + currentCoil;
index = modbusSlaveIndexForAddres(coil, 0);
_modbusSlaveDataTable_0[index] = bitRead( _modbusSlaveBuffer[ frameByte ], bitsNo );
bitsNo ++;
if (bitsNo > 7) {
bitsNo = 0;
frameByte++;
}
}
_modbusSlaveBufferSize = 6;
_modbusSlaveSendTxBuffer();
return _modbusSlaveBufferSize + 2;
}
byte process_modbus_FC6()
{
int addres = word( _modbusSlaveBuffer[2], _modbusSlaveBuffer[3] );
int index;
index = modbusSlaveIndexForAddres(addres, 4);
_modbusSlaveDataTable_4[index] =word( _modbusSlaveBuffer[4], _modbusSlaveBuffer[5] );
_modbusSlaveBufferSize = 6;
_modbusSlaveSendTxBuffer();
return _modbusSlaveBufferSize + 2;
}
byte process_modbus_FC16( ) 
{
byte func = _modbusSlaveBuffer[1];
int startAddr = _modbusSlaveBuffer[2] << 8 | _modbusSlaveBuffer[3];
int byteRegsno = _modbusSlaveBuffer[4] << 8 | _modbusSlaveBuffer[5];
int i;
int index;
_modbusSlaveBuffer[4] = 0;
_modbusSlaveBuffer[5] = byteRegsno;
_modbusSlaveBufferSize = 6;
for (i = 0; i < byteRegsno; i++) {
index = modbusSlaveIndexForAddres((startAddr+i), 4);
_modbusSlaveDataTable_4[index] =word( _modbusSlaveBuffer[ 7 + i * 2 ], _modbusSlaveBuffer[8 + i * 2 ]);
}
_modbusSlaveSendTxBuffer();
return _modbusSlaveBufferSize +2;
}
byte readByteFromEEPROM(int addres, byte bitAddres, byte chipAddres)
{
return EEPROM.read(addres);
}
void updateByteToEEPROM(int addres, byte bitAddres, byte chipAddres, byte value)
{
return EEPROM.update(addres, value);
}
int readIntegerFromEEPROM(int addres, byte bitAddres, byte chipAddres)
{
byte hight = readByteFromEEPROM( addres, bitAddres, chipAddres);
byte low = readByteFromEEPROM( (addres+1), bitAddres, chipAddres);
return word(hight, low);
}
void updateIntegerToEEPROM(int addres, byte bitAddres, byte chipAddres, int value)
{
updateByteToEEPROM( addres, bitAddres, chipAddres, highByte(value));
updateByteToEEPROM( (addres+1), bitAddres, chipAddres, lowByte(value));
}
