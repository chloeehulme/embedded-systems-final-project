/**
   Describes the functions required for the system's operation.
   Author: Chloe Hulme
*/

#ifndef FUNCTIONS
#define FUNCTIONS

/**
 * Runs the DC motor attached to the linear actuator,
 * to push a cup through the cup holder.
 */
void dispenseCup(const int pin, const int pin2);

/**
 * Runs the servo responsible for swinging the claw under the dispenser.
 */
void clawSwing(Servo servo, int pos);

/**
 * Resets the claw to the correct position using the servo.
 */
void clawReset(Servo servo, int pos);

/**
 * Activates the relay allowing the pump to dispense the correct amount of liquid unto the cup.
 */
void pourDrink(int relay);

/**
 * Runs the DC motor attached to the linear actuator,
 * to retract it back up through the cup holder.
 */
void retractActuator(const int pin1, const int pin2);

#endif
