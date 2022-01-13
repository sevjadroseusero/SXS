#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX
char i = '0';
char a[15] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
int k = 0;
void setup()
{
Serial.begin(9600);
while (!Serial) ;
mySerial.begin(9600);
 
}
void loop()
{
if (mySerial.available()) {
 
//Serial.write(mySerial.read());
i = mySerial.read();
//Serial.println(i);
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
Serial.println(a[12])
;

}
}
}
