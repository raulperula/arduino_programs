#include <Servo.h>

Servo servoR;
Servo servoL;
int servoPinR = 12;    // pin motor derecho
int servoPinL = 13;    // pin motor izquierdo

int e = 0;

void setup()
{
    Serial.begin(9600);        // abrir el puerto serie con una velocidad de 9600 baudios
    servoR.attach(servoPinR);
    servoL.attach(servoPinL);
    Serial.flush();            // vaciar el puerto serie
}

void loop()
{
    // calibracion servomotores
    //    int opcion = 0;
    //
    //    // avanzar
    //    if(opcion) {
    //        servoR.write(180);
    //        servoL.write(0);
    //    }
    //    else {
    //        // parar
    //        servoR.write(92);
    //        servoL.write(90);
    //    }

    // aparcamiento

    if (e == 0) {
        // avanzar
        servoL.write(180);
        servoR.write(0);
        delay(2500);

        // girar izq
        servoL.write(90);
        servoR.write(0);
        delay(1000);

        // avanzar
        servoL.write(180);
        servoR.write(0);
        delay(500);

        // girar derecha
        servoL.write(180);
        servoR.write(90);
        delay(1000);

        // parar
        servoL.write(90);
        servoR.write(90);
        delay(1000);

        e = 1;
    }
}


