#include <BOARD.h>
#include "motors.h"
#include "IO_Ports.h"
#include "pwm.h"

#define DRIVING_MOTOR_PORT  PORTY
#define ENABLE_A PWM_PORTY12  
#define DIRECTION_A PIN11


#define ENABLE_B PWM_PORTY10 
#define DIRECTION_B PIN9


//Sets up the pins for driving the motors.

void motors_init() {
    PWM_Init();
    IO_PortsSetPortOutputs(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
    PWM_AddPins(ENABLE_A | ENABLE_B);
    PWM_SetFrequency(PWM_500HZ);
}

void turn_right() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B, 1000);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void turn_left() {
    PWM_SetDutyCycle(ENABLE_A, 1000);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void tank_turn_right() {
    PWM_SetDutyCycle(ENABLE_A, 1000);
    PWM_SetDutyCycle(ENABLE_B, 1000);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void tank_turn_left() {
    PWM_SetDutyCycle(ENABLE_A, 1000);
    PWM_SetDutyCycle(ENABLE_B, 1000);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void reverse() {
    PWM_SetDutyCycle(ENABLE_A, 1000);
    PWM_SetDutyCycle(ENABLE_B, 1000);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void forwards() {
    PWM_SetDutyCycle(ENABLE_A, 1000);
    PWM_SetDutyCycle(ENABLE_B, 1000);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void stop() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}