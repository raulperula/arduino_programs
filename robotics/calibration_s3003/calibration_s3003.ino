#include <Servo.h>

Servo servoR;
Servo servoL;
int servoPinR = 8;
int servoPinL = 9;

void setup()
{
    servoR.attach(servoPinR);
    servoL.attach(servoPinL);
    Serial.begin(9600);
}

void loop()
{
    servoR.write(180);
    servoL.write(0);
    delay(2000);
    servoR.write(0);
    servoL.write(180);
    delay(2000);
}


