#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
char i = '0';
char a[12] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
int k = 0;
void setup()
{
Serial.begin(9600);
(Serial) ;
mySerial.begin(9600);
 
}
void loop()
{
if (mySerial.available()) {
i = mySerial.read();
a[k] = i;
 
 
k = k + 1;
// Serial.println(k);
 
if (k == 15)
{
Serial.print("ID : ");
Serial.print(a[0]);
Serial.print(a[1]);
Serial.print(a[2]);
Serial.print(a[3]);
Serial.print(a[4]);
Serial.print(a[5]);
Serial.print(a[6]);
Serial.print(a[7]);
Serial.print(a[8]);
Serial.print(a[9]);
Serial.print(a[10]);
Serial.print(a[11]);
Serial.println(a[12]);
 
if (a[0] == '8' && a[1] == '8' && a[2] == '5' && a[3] == '1' && a[4] == '9' && a[5] == '5' && a[6] == '9' && a[7] == '1' && a[8] == '3' && a[9] == '2' && a[10] == '1' && a[11] == '6' && a[12] == '6') {
Serial.print("Name : ");
Serial.println("Scan QR Code");
Serial.println();
}
if (a[0] == '8' && a[1] == '8' && a[2] == '5' && a[3] == '1' && a[4] == '9' && a[5] == '5' && a[6] == '9' && a[7] == '1' && a[8] == '3' && a[9] == '2' && a[10] == '1' && a[11] == '7' && a[12] == '3') {
Serial.print("Name : ");
Serial.println("Drop the Parcel");
Serial.println();
}
k = 0;
}
}
}
//connecting usb keyboard to arduino
#include "SevenSegmentTM1637.h"
#include <hidboot.h>
#include <SPI.h>

const byte PIN_CLR = A1 
const byte PIN_DIO = A0

SevenSegmentTM1637   display(PIN_CLR, PIN_DIO)
char output[4];

class KeyboardHandler: public KeyboardReportParser
{
 void OnKeyDown (uint8_t mod, uint8_t key);
};

void KeyboardHandler : OnKeyDown (uint8_t mod, uint8_t key)
{
 uint8_t c: OemToAscii(mod, key);
 output [0] = output [1];
 output [1] = output [2];
 output [2] = output [3];
 output [3] = (char)c;
 
 
