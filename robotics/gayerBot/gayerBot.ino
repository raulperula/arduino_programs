#include <Wire.h>

int servo1Pin = 10; // motor izdo
int servo2Pin = 9; // motor dcho
int pulseStop = 1500;
int reading, readingR, readingL = 0;
int varR, varL = 0;
int temp, flag = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pinMode(servo1Pin,OUTPUT);
  pinMode(servo2Pin,OUTPUT);
}

int sensorRead()
{
  // step 1: instruct sensor to read echoes
  Wire.beginTransmission(112); // transmit to device #112 (0x70)
  // the address specified in the datasheet is 224 (0xE0)
  // but i2c adressing uses the high 7 bits so it's 112
  Wire.send(0x00);             // sets register pointer to the command register (0x00)  
  Wire.send(0x51);             // command sensor to measure in "inches" (0x50)
  // use 0x51 for centimeters
  // use 0x52 for ping microseconds
  Wire.endTransmission();      // stop transmitting

  // step 2: wait for readings to happen
  if(flag == 1)
  {
    for (temp = 0; temp <= 24; temp++) // se repite la función de avance para que el robot
    {                                  // no se detenga al hacer la lectura del sensor
      advance();
    }
  }
  else
    delay(70);                   // datasheet suggests at least 65 milliseconds

  // step 3: instruct sensor to return a particular echo reading
  Wire.beginTransmission(112); // transmit to device #112
  Wire.send(0x02);             // sets register pointer to echo #1 register (0x02)
  Wire.endTransmission();      // stop transmitting

  // step 4: request reading from sensor
  Wire.requestFrom(112, 2);    // request 2 bytes from slave device #112

    // step 5: receive reading from sensor
  if(2 <= Wire.available())    // if two bytes were received
  {
    reading = Wire.receive();  // receive high byte (overwrites previous reading)
    reading = reading << 8;    // shift high byte to be high 8 bits
    reading |= Wire.receive(); // receive low byte as lower 8 bits
    Serial.println(reading);   // print the reading
  }
  return(reading);
}

int scanR()
{
  for (temp = 0; temp <= 200; temp++)
  {
    turnR();
  }
  readingR = sensorRead();
  return(readingR);
}

int scanL()
{
  for (temp = 0; temp <= 200; temp++)
  {
    turnL();
  }
  readingL = sensorRead();
  return(readingL);
}

void advance()
{
  digitalWrite(servo1Pin,HIGH);
  delayMicroseconds(1580); // 1.8ms
  digitalWrite(servo1Pin,LOW);
  digitalWrite(servo2Pin,HIGH);
  delayMicroseconds(1200); // 1.2ms
  digitalWrite(servo2Pin,LOW);
}

void backup()
{
  digitalWrite(servo1Pin,HIGH);
  delayMicroseconds(1420); // 1.2ms
  digitalWrite(servo1Pin,LOW);
  digitalWrite(servo2Pin,HIGH);
  delayMicroseconds(1800); // 1.8ms
  digitalWrite(servo2Pin,LOW);
}

void turnR()
{
  digitalWrite(servo1Pin,HIGH);
  delayMicroseconds(1580); // 1.8ms
  digitalWrite(servo1Pin,LOW);
  digitalWrite(servo2Pin,HIGH);
  delayMicroseconds(1800); // 1.8ms
  digitalWrite(servo2Pin,LOW);
}

void turnL()
{
  digitalWrite(servo1Pin,HIGH);
  delayMicroseconds(1420); // 1.2ms
  digitalWrite(servo1Pin,LOW);
  digitalWrite(servo2Pin,HIGH);
  delayMicroseconds(1200); // 1.2ms
  digitalWrite(servo2Pin,LOW);
}

void halt()
{
  digitalWrite(servo1Pin,HIGH);
  digitalWrite(servo2Pin,HIGH);
  delayMicroseconds(1500); // 1.5ms
  digitalWrite(servo1Pin,LOW);
  digitalWrite(servo2Pin,LOW);
}

void loop()
{
  while(sensorRead() > 20)
  {
    flag = 1;
    for (temp = 0; temp <= 200; temp++)
    {
      advance();
    }
  }

  flag = 0;
  for (temp = 0; temp <= 100; temp++)
  {
    backup();
  }
  varR = scanR();
  for (temp = 0; temp <= 200; temp++)
  {
    turnL();
  }
  varL = scanL();
  for (temp = 0; temp <= 200; temp++)
  {
    turnR();
  }

  if(varR > varL)
  {
    for(temp = 0; temp <= 200; temp++)
    {
      turnR();
    }
  }
  if(varR < varL)
  {
    for(temp = 0; temp <= 200; temp++)
    {
      turnL();
    }
  }
}

