/**
   Describes the functions required to operate the linear actuator.
   Author: Chloe Hulme
*/

#ifndef LINEAR_ACTUATOR
#define LINEAR_ACTUATOR

/**
 * Runs the DC motor attached to the linear actuator,
 * to extend the linear actuator.
 */
void retract(const int IN3, const int IN4);

/**
 * Runs the DC motor attached to the linear actuator,
 * to retract the linear actuator
 */
void extend(const int IN3, const int IN4);

/**
 * Runs the DC motor attached to the linear actuator,
 * to stop the linear actuator's motion.
 */
void stop(const int IN3, const int IN4);

#endif
