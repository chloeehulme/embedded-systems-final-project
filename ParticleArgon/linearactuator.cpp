/**
   Describes the functions required to operate the linear actuator.
   Author: Chloe Hulme
*/

#include "Particle.h"

void retract(const int IN3, const int IN4)
{
    analogWrite(IN3, 255);
    analogWrite(IN4, 0);
}

void extend(const int IN3, const int IN4)
{
    analogWrite(IN3, 0);
    analogWrite(IN4, 255);
}

void stop(const int IN3, const int IN4)
{
    analogWrite(IN3, 0);
    analogWrite(IN4, 0);
}
