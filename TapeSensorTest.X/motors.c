#include <BOARD.h>
#include "motors.h"
#include "IO_Ports.h"
#include "pwm.h"

#define DRIVING_MOTOR_PORT  PORTY
#define ENABLE_A PWM_PORTY12  
#define DIRECTION_A PIN11

#define MOT0R_A_SPEED 1000
//#define MOT0R_B_SPEED 920
#define MOT0R_B_SPEED 994

#define ENABLE_B PWM_PORTY10 
#define DIRECTION_B PIN9


//Sets up the pins for driving the motors.

void motors_init() {
   
    IO_PortsSetPortOutputs(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
    PWM_AddPins(ENABLE_A | ENABLE_B);
    PWM_SetFrequency(MIN_PWM_FREQ);
}

void turn_right() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B, MOT0R_B_SPEED);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void turn_left() {
    PWM_SetDutyCycle(ENABLE_A, MOT0R_A_SPEED);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void tank_turn_right() {
    PWM_SetDutyCycle(ENABLE_A, MOT0R_A_SPEED);
    PWM_SetDutyCycle(ENABLE_B, MOT0R_B_SPEED);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void tank_turn_left() {
    PWM_SetDutyCycle(ENABLE_A, MOT0R_A_SPEED);
    PWM_SetDutyCycle(ENABLE_B, MOT0R_B_SPEED);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void turn_back_right() {
    PWM_SetDutyCycle(ENABLE_A, MOT0R_A_SPEED);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void turn_back_left() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B, MOT0R_B_SPEED);
   IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}
void reverse() {
    PWM_SetDutyCycle(ENABLE_A, MOT0R_A_SPEED);
    PWM_SetDutyCycle(ENABLE_B, MOT0R_B_SPEED);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void forwards() {
    PWM_SetDutyCycle(ENABLE_A, MOT0R_A_SPEED);
    PWM_SetDutyCycle(ENABLE_B, MOT0R_B_SPEED);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void stop() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}