//scanning qr code
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
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
i = mySerial.read();
a[k] = i;
 
 
k = k + 1;
// Serial.println(k);
 
if (k == 15)
{
Serial.print("Tracking code: ");
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

 //tracking code example: 8851959132166
if (a[0] == '8' && a[1] == '8' && a[2] == '5' && a[3] == '1' && a[4] == '9' && a[5] == '5' && a[6] == '9' && a[7] == '1' && a[8] == '3' && a[9] == '2' && a[10] == '1' && a[11] == '6' && a[12] == '6') {
Serial.print("Parcel");
Serial.println("Solenoid Lock 12v");
Serial.println();
}

 //tracking code example: 8851959132173
if (a[0] == '8' && a[1] == '8' && a[2] == '5' && a[3] == '1' && a[4] == '9' && a[5] == '5' && a[6] == '9' && a[7] == '1' && a[8] == '3' && a[9] == '2' && a[10] == '1' && a[11] == '7' && a[12] == '3') {
Serial.print("Parcel");
Serial.println("Keyboard Ps/2 Adapter");
Serial.println();
}
k = 0;
}
}
}

//connecting usb keyboard to arduino
#define CLOCK 6 //D-
#define DATA 7  //D+

#include <LiquidCrystal.h>  //Best imported by library manager

const char keymap[] = {
  0, 0,  0,  0,  0,  0,  0,  0,
  0, 0,  0,  0,  0,  0, '`', 0,
  0, 0 , 0 , 0,  0, 'q','1', 0,
  0, 0, 'z','s','a','w','2', 0,
  0,'c','x','d','e','4','3', 0,
  0,' ','v','f','t','r','5', 0,
  0,'n','b','h','g','y','6', 0,
  0, 0, 'm','j','u','7','8', 0,
  0,',','k','i','o','0','9', 0,
  0,'.','/','l',';','p','-', 0,
  0, 0,'\'', 0,'[', '=', 0, 0,
  0, 0,13, ']', 0, '\\', 0, 0,
  0, 0, 0, 0, 0, 0, 127, 0,
  0,'1', 0,'4','7', 0, 0, 0,
  '0','.','2','5','6','8', 0, 0,
  0,'+','3','-','*','9', 0, 0,
  0, 0, 0, 0 };

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(115200);
  pinMode(CLOCK, INPUT_PULLUP); //For most keyboards the builtin pullups are sufficient, so the 10k pullups can be omitted
  pinMode(DATA, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  lcd.begin(20, 4);
  lcd.cursor();
  lcd.blink();
  bitSet(PCICR, PCIE2); // Enable pin change interrupts on pin D0-D7
  bitSet(PCMSK2, CLOCK); // Pin change interrupt on Clock pin
 }

uint8_t lastscan;
uint8_t line = 0, col = 0;


ISR(PCINT2_vect)
{
  uint16_t scanval = 0;
  for(int i = 0; i<11; i++)
  {
    while(digitalRead(CLOCK));
    scanval |= digitalRead(DATA) << i;
    while(!digitalRead(CLOCK));
  }
  scanval >>= 1;
  scanval &= 0xFF;
  Serial.println(scanval, HEX);
  if(lastscan != 0xF0 && scanval != 0xF0)
  switch(scanval)
  {
    case 0x5A: //Enter
      lcd.setCursor(0, ++line & 0x03);
      col = 0;
      break;
    case 0x66: //Backspace
      lcd.setCursor(--col, line);
      lcd.write(' ');
      lcd.setCursor(col, line);
    break;
    default:
      lcd.write(keymap[scanval]);
      col++;
  }
  lastscan = scanval;
  bitSet(PCIFR, PCIF2);
}

void loop()
{
  /*digitalWrite(13, LOW);
  delay(500);  
  digitalWrite(13, HIGH);
  delay(500);*/
}
