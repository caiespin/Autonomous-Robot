#include <BOARD.h>
#include "motors.h"
#include "IO_Ports.h"
#include "AD.h"
#include "pwm.h"
#include "stdio.h"

#define DRIVING_MOTOR_PORT  PORTY
#define ENABLE_A PWM_PORTY12  
#define DIRECTION_A PIN11

//#define MOT0R_A_SPEED 1000
////#define MOT0R_B_SPEED 920
//#define MOT0R_B_SPEED 994
#define MOTOR_OFFSET 0

#define ENABLE_B PWM_PORTY10 
#define DIRECTION_B PIN9




uint16_t Motor_Speed_A = 0;
uint16_t Motor_Speed_B = 0;

uint16_t  Motor_Speed_Tank_B;
uint16_t  Motor_Speed_Tank_A;
//Sets up the pins for driving the motors.

 void arc_left(){
  
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_A);
    PWM_SetDutyCycle(ENABLE_B,  Motor_Speed_B*0.50);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);   
 }

void motors_init() {
   
    IO_PortsSetPortOutputs(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
    AD_AddPins(BAT_VOLTAGE);
    PWM_AddPins(ENABLE_A | ENABLE_B);
    PWM_SetFrequency(MIN_PWM_FREQ);
    adjust_pwm();
}

void turn_right() {

    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_A*0.5);
    PWM_SetDutyCycle(ENABLE_B, Motor_Speed_B);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void turn_left() {
  
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_A);
    PWM_SetDutyCycle(ENABLE_B, Motor_Speed_B*0.5);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void tank_turn_right() {
   
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_Tank_A);
    PWM_SetDutyCycle(ENABLE_B,Motor_Speed_Tank_B);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void tank_turn_left() {
    
    PWM_SetDutyCycle(ENABLE_A,Motor_Speed_Tank_A);
    PWM_SetDutyCycle(ENABLE_B,Motor_Speed_Tank_B);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void turn_back_right() {
   
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_Tank_A);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void turn_back_left() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B,Motor_Speed_Tank_B);
   IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}
void reverse() {
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_A);
    PWM_SetDutyCycle(ENABLE_B, Motor_Speed_B);
    IO_PortsSetPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void forwards() {
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_A);
    PWM_SetDutyCycle(ENABLE_B, Motor_Speed_B);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}


void slow_forwards() {
    PWM_SetDutyCycle(ENABLE_A, Motor_Speed_A*0.7);
    PWM_SetDutyCycle(ENABLE_B, Motor_Speed_B*0.7);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
}

void stop() {
    PWM_SetDutyCycle(ENABLE_A, 0);
    PWM_SetDutyCycle(ENABLE_B, 0);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_A);
    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
}

void adjust_pwm() {
    
    float rawBatVoltage = (AD_ReadADPin(BAT_VOLTAGE) * 33) / 1023; // read the battery voltage
    uint16_t PWM_ALL = (uint16_t)((6.5/(rawBatVoltage - 0.6)) * 1000);
    uint16_t PWM_Tank_Turns = (uint16_t)((7.9/(rawBatVoltage - 0.6)) * 1000);
    if(PWM_ALL>1000){
        PWM_ALL=1000;
    }
     if(PWM_Tank_Turns>1000){
        PWM_Tank_Turns=1000;
    }
    printf("PWM_ALL-------------------> %d\r\n", PWM_ALL);
    Motor_Speed_B=PWM_ALL-MOTOR_OFFSET;
    Motor_Speed_A= Motor_Speed_B;
    
    Motor_Speed_Tank_B=PWM_Tank_Turns;
    Motor_Speed_Tank_A= PWM_Tank_Turns;
    
   
    
}