/**
   A finite state machine that is able to dispense a cup and water.
   Author: Chloe Hulme
*/

#include "functions.h"

// Initialise objects and set pins
Servo clawServo;
int clawPos = 0;
const int IN3 = D5;
const int IN4 = D6;
const int clawPin = D4;
const int relay = D8;

// Switches
bool cupInFront = false;
bool begin = false;
bool _retract = false;

// States in the finite state machine, handled in loop()
enum State {
    STATE_WAIT_FOR_WEBHOOK = 0,
    STATE_DISPENSE_CUP,
    STATE_ROTATE_CLAW,
    STATE_CUP_IN_FRONT,
    STATE_POUR_DRINK,
    STATE_RESET,
    STATE_WAIT_TO_TAKE,
    STATE_RETRACT
};

// Initialise to first state
State state = STATE_WAIT_FOR_WEBHOOK;

void setup() {
    
    clawServo.attach(clawPin);
    pinMode (IN3, OUTPUT);
    pinMode (IN4, OUTPUT);
    pinMode(relay, OUTPUT);
    digitalWrite(relay, HIGH);
    Particle.subscribe("cup_in_front", cupInPos);
    Particle.subscribe("not_in_front", notInPos);
    Particle.subscribe("water", dispenser_handler);
    Particle.subscribe("retract", retract_handler);
}

void loop() {
    switch(state) {
            
        // An idle state; waiting to receive 'water' or 'retract' events    
        case STATE_WAIT_FOR_WEBHOOK:
            if(begin)
            {
                begin = false;
                state = STATE_DISPENSE_CUP;
            }
            if(_retract)
            {
                _retract = false;
                state = STATE_RETRACT;
            }
            break;
            
        // Dispenses cup   
        case STATE_DISPENSE_CUP:
            dispenseCup(IN3, IN4);
            state = STATE_ROTATE_CLAW;
            break;
        
        // Swings claw under water dispenser    
        case STATE_ROTATE_CLAW:
            clawSwing(clawServo, clawPos);
            state = STATE_CUP_IN_FRONT;
            break;
        
        // Checks if cup is in correct position, reset to get cup if not
        case STATE_CUP_IN_FRONT:
            delay(15000);
            if (cupInFront)
            {
                state = STATE_POUR_DRINK;
            }
            else
            {
                state = STATE_RESET;
            }
            break;
            
        // Pour water into cup by activating relay
        case STATE_POUR_DRINK:
            pourDrink(relay);
            state = STATE_WAIT_TO_TAKE;
            break;
        
        // Resets claw under cup dispenser
        case STATE_RESET:
            clawReset(clawServo, clawPos);
            state = STATE_DISPENSE_CUP;
            break;
        
        // An idle state; waiting until cup is taken by user
        case STATE_WAIT_TO_TAKE:
            if (!cupInFront)
            {
                clawReset(clawServo, clawPos);
                state = STATE_WAIT_FOR_WEBHOOK;
            }
            break;
        
        // Retracts linear actuator so machine can be reloaded with cups    
        case STATE_RETRACT:
            retractActuator(IN3, IN4);
            state = STATE_WAIT_FOR_WEBHOOK;
            break;
    }       
}


/**
   Event handlers
*/

// Handles 'water' event
void dispenser_handler(const char *event, const char *data)
{
    begin = true;
}

// Handles 'retract' event
void retract_handler(const char *event, const char *data)
{
    _retract = true;
}

// Handles 'cup in front' event
void cupInPos(const char *event, const char *data)
{
    cupInFront = true;
}

// Handles 'not in front' event
void notInPos(const char *event, const char *data)
{
    cupInFront = false;
}
