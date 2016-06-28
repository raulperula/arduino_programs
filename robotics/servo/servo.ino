#include <Servo.h>

Servo motor1;
//Servo motor2;

void setup()
{
  motor1.attach(8);
  //motor2.attach(9);
}

void loop()
{
    motor1.write(90);
    //motor2.write(90);
    //motor1.writeMicroseconds(1500);
    //motor2.writeMicroseconds(1500);
}
