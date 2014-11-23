#include <Servo.h>

Servo servoR;
Servo servoL;

int servoPinR = 10;    // pin motor derecho
int servoPinL = 9;   // pin motor izquierdo

// avanzar
void advance()
{
    servoR.write(160);
    servoL.write(20);
}

// girar a la derecha
void turnR()
{
    servoR.write(180);
    servoL.write(90);
}

void setup()
{
    Serial.begin(9600); // abrir el puerto serie con una velocidad de 9600 baudios
    servoR.attach(servoPinR);
    servoL.attach(servoPinL);
    Serial.flush();    // vaciar el puerto serie
}

void loop()
{
    advance();
    delay(2000);
    turnR();
    delay(1000);
}

