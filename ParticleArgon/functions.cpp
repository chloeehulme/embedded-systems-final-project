/**
   Describes the functions required for the system's operation.
   Author: Chloe Hulme
*/

#include "Particle.h"
#include "functions.h"
#include "linearactuator.h"

void dispenseCup(const int pin1, const int pin2)
{
    extend(pin1, pin2);
    delay(10000);
    stop(pin1, pin2);
}

void clawSwing(Servo servo, int pos)
{
    for(pos = 0; pos < 200; pos += 1)
    {                         
        servo.write(pos);
        delay(15);
    }
}

void pourDrink(int relay)
{
    digitalWrite(relay, LOW);
    delay(5000);
    digitalWrite(relay, HIGH);
}

void clawReset(Servo servo, int pos)
{
    for(pos = 200; pos>=1; pos-=1)     
    {
        servo.write(pos);           
        delay(10);              
    }
}

void retractActuator(const int pin1, const int pin2)
{
    retract(pin1, pin2);
    delay(30000);
    stop(pin1, pin2);
}
