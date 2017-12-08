/*
 * File:   main.c
 * Author: igonzalo
 *
 * Created on October 26, 2017, 3:21 PM
 */
#include <xc.h>
#include <BOARD.h>
#include <stdio.h>
#include <AD.h>
#include "IO_Ports.h"
#include "LED.h"
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "pwm.h"
#include "RC_Servo.h"
#include "motors.h"
#include "event_checker.h"
#include "tape_detector_fsm_service.h"
#include "FSMShoot.h"
//
//#define TEST_TAPE_SENSOR
#define TEST_TAPE_SENSOR_WITH_ES_FRAMEWORK
//#define TEST_BUMPER
//#define TEST_DRIVING_MOTORS
//#define TEST_SERVO_TILT
//#define TEST_SERVO
//#define TEST_DRIVING_MOTORS_HELPER_FUNCTIONS
//#define TEST_DRIVING_MOTORS_HELPER_FUNCTIONS2
//#define TEST_TRACKWIRE
//#define TEST_SHOOTER
//#define TEST_AD_BUG


#define TAPE_PIN_1 AD_PORTW3

#define  FRONT_LEFT_BUMPER_PIN PIN3
#define  FRONT_RIGHT_BUMPER_PIN PIN4
#define  BACK_LEFT_BUMPER_PIN PIN5
#define  BACK_RIGHT_BUMPER_PIN PIN6




#define TAPE_HIGH_THRESHOLD 25
#define TAPE_LOW_THRESHOLD 5
#define ALL_LEDS 0xF


#ifdef TEST_TAPE_SENSOR
#include <timers.h>
#define Servo_Pin RC_PORTW08

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    LED_Init();

    int tape1AdcValHigh = 0;
    int tape1AdcValLow = 0;
    int diff = 0;
    ///////
    //Initialize Analog inputs
    AD_Init();
    AD_AddPins(TAPE_PIN_5);

    IO_PortsSetPortOutputs(TAPE_PORT, LED_PIN);


    LED_AddBanks(LED_BANK1);
    LED_OffBank(LED_BANK1, ALL_LEDS);
    //  IO_PortsClearPortBits(PORTX, LED_PIN);

    // IO_PortsSetPortBits(PORTX, LED_PIN);
    // int pot_val =
    while (1) {

        IO_PortsSetPortBits(TAPE_PORT, LED_PIN);
        delay(8000);
        tape1AdcValHigh = AD_ReadADPin(TAPE_PIN_5);
        printf("tape1AdcVal = %d\r\n", tape1AdcValHigh);
        delay(100000);
        IO_PortsClearPortBits(TAPE_PORT, LED_PIN);
        delay(8000);
        tape1AdcValLow = AD_ReadADPin(TAPE_PIN_5);
        diff = tape1AdcValLow - tape1AdcValHigh;
        printf("tape1AdcVal diff = %d\r\n", diff);
        delay(100000);

        if (diff < TAPE_HIGH_THRESHOLD && diff > TAPE_LOW_THRESHOLD) {
            LED_SetBank(LED_BANK1, ALL_LEDS);
        } else {
            LED_OffBank(LED_BANK1, ALL_LEDS);
        }





    }
}
#endif

#ifdef TEST_TAPE_SENSOR_WITH_ES_FRAMEWORK

int main() {

    ES_Return_t ErrorType;

    BOARD_Init();
    PWM_Init();
    motors_init(); //PWM_Init goes first
    AD_Init();
    init_tape_sensors(); // AD goes before this 
    RC_Init();
    ES_Timer_Init();
    trackwire_init();
    shooter_init();
    beacon_init();





    printf("Starting ES Framework Template\r\n");
    printf("using the 2nd Generation Events & Services Framework\r\n");


    // Your hardware initialization function calls go here

    // now initialize the Events and Services Framework and start it running
    ErrorType = ES_Initialize();
    if (ErrorType == Success) {
        ErrorType = ES_Run();

    }
    //if we got to here, there was an error
    switch (ErrorType) {
        case FailedPointer:
            printf("Failed on NULL pointer");
            break;
        case FailedInit:
            printf("Failed Initialization");
            break;
        default:
            printf("Other Failure: %d", ErrorType);
            break;
    }
    for (;;)
        ;
}
#endif


#ifdef TEST_BUMPER
#define  FRONT_LEFT_BUMPER_PIN PIN3
#define  FRONT_RIGHT_BUMPER_PIN PIN4
#define  BACK_LEFT_BUMPER_PIN PIN5
#define  BACK_RIGHT_BUMPER_PIN PIN6

#define  SHIFT_AMOUNT 3

#define BUMPER_PORT PORTZ

#define ALL_BUMPER_PINS (FRONT_LEFT_BUMPER_PIN | FRONT_RIGHT_BUMPER_PIN | BACK_LEFT_BUMPER_PIN |  BACK_RIGHT_BUMPER_PIN)

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    IO_PortsSetPortInputs(BUMPER_PORT, FRONT_LEFT_BUMPER_PIN);
    IO_PortsSetPortInputs(BUMPER_PORT, FRONT_RIGHT_BUMPER_PIN);
    IO_PortsSetPortInputs(BUMPER_PORT, BACK_LEFT_BUMPER_PIN);
    IO_PortsSetPortInputs(BUMPER_PORT, BACK_RIGHT_BUMPER_PIN);

    while (1) {
        printf("Status:%d \r\n", ((IO_PortsReadPort(BUMPER_PORT)) & ALL_BUMPER_PINS) >> SHIFT_AMOUNT);
        delay(1000000);
    }
    for (;;)
        ;
}
#endif

#ifdef TEST_DRIVING_MOTORS

#define SHOOTER_MOTOR_PIN PWM_PORTZ06



#define ENABLE_B PWM_PORTY10 
#define DIRECTION_B PIN9

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    PWM_Init();

    //    IO_PortsSetPortOutputs(DRIVING_MOTOR_PORT, DIRECTION_A | DIRECTION_B);
    PWM_AddPins(SHOOTER_MOTOR_PIN);

    //IO_PortsSetPortOutput(BUMPER_PORT,  FRONT_LEFT_BUMPER_PIN);
    //IO_PortsSetPortOutput(BUMPER_PORT,   FRONT_RIGHT_BUMPER_PIN);
    //IO_PortsSetPortInputs(BUMPER_PORT,  BACK_LEFT_BUMPER_PIN);
    //  IO_PortsSetPortInputs(BUMPER_PORT,  BACK_RIGHT_BUMPER_PIN);
    PWM_SetFrequency(MIN_PWM_FREQ);

    //    PWM_SetDutyCycle(ENABLE_B, 950);
    //    IO_PortsWritePort(DRIVING_MOTOR_PORT, DIRECTION_A);
    //    IO_PortsClearPortBits(DRIVING_MOTOR_PORT, DIRECTION_B);
    
    
    //PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, 50);
    for (;;) {
        
         PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, 50);
          delay(1000000);
        PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, 180);
         delay(1000000);
        //        int i = 0;
        //        for (i = 0; i <= 1000; i += 10) {
        //            PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, i);
        //            delay(200000);
        //        }



    }

}

#endif



#ifdef TEST_SERVO_TILT
#include "FSMShoot.h"

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    PWM_Init();
    shooter_init();
  
    for (;;) {
        
        set_atm6_tilt();
          delay(1000000);
         set_ren_tilt();
         delay(1000000);
        //        int i = 0;
        //        for (i = 0; i <= 1000; i += 10) {
        //            PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, i);
        //            delay(200000);
        //        }



    }

}

#endif














#ifdef TEST_SERVO
#define SERVO_TILT_PIN RC_PORTZ09

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    RC_Init();



    //#define MINPULSE 550
    //#define MAXPULSE 2450 metsl serv


    // RC_SetPulseTime(SERVO_TILT_PIN, 1500);
    //    delay(3000000);
    //    RC_SetPulseTime(SERVO_TILT_PIN, MAXPULSE);
    //    delay(100000);

    //    IO_PortsSetPortOutputs(SHOOT_PORT, SERVO_TILT_PIN);
    //    IO_PortsSetPortBits(SHOOT_PORT, SERVO_TILT_PIN);
    //    delay(2000000);

    RC_AddPins(SERVO_TILT_PIN);
    for (;;) {
        int i = 0;
        for (i = MINPULSE; i <= MAXPULSE; i += 10) {
            RC_SetPulseTime(SERVO_TILT_PIN, i);
            delay(200000);
        }



    }

}
#endif



#ifdef TEST_DRIVING_MOTORS_HELPER_FUNCTIONS

#include "motors.h"

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    motors_init();
    forwards();

    for (;;) {
        ;

    }

}

#endif

#ifdef TEST_TRACKWIRE

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    AD_Init();

    trackwire_init();

    for (;;) {

        uint16_t side_trackwire_val = AD_ReadADPin(SIDE_TRACKWIRE_PIN);
        uint16_t back_trackwire_val = AD_ReadADPin(BACK_TRACKWIRE_PIN);

        if ((side_trackwire_val == ((uint16_t) ERROR)) || (back_trackwire_val == ((uint16_t) ERROR))) {
            continue;
        }
        printf("Side:%d,  back:%d, diff:%d\r\n", side_trackwire_val, back_trackwire_val, side_trackwire_val - back_trackwire_val);
        delay(1000000);
    }

}

#endif

#ifdef TEST_TRACKWIRE2

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    AD_Init();
    motors_init();
    forwards();

    trackwire_init();

    for (;;) {
        forwards();
        uint16_t front_trackwire_val = AD_ReadADPin(FRONT_TRACKWIRE);
        uint16_t back_trackwire_val = AD_ReadADPin(BACK_TRACKWIRE);

        if ((front_trackwire_val == ((uint16_t) ERROR)) || (back_trackwire_val == ((uint16_t) ERROR))) {
            continue;
        }
        printf("FORWARDS front:%d,  back:%d, diff:%d\r\n", front_trackwire_val, back_trackwire_val, front_trackwire_val - back_trackwire_val);
        delay(1000000);

        reverse();

        front_trackwire_val = AD_ReadADPin(FRONT_TRACKWIRE);

        back_trackwire_val = AD_ReadADPin(BACK_TRACKWIRE);
        if ((front_trackwire_val == ((uint16_t) ERROR)) || (back_trackwire_val == ((uint16_t) ERROR))) {
            continue;
        }
        printf("reverse front:%d,  back:%d, diff:%d\r\n", front_trackwire_val, back_trackwire_val, front_trackwire_val - back_trackwire_val);
        delay(1000000);

        stop();

        front_trackwire_val = AD_ReadADPin(FRONT_TRACKWIRE);

        back_trackwire_val = AD_ReadADPin(BACK_TRACKWIRE);
        if ((front_trackwire_val == ((uint16_t) ERROR)) || (back_trackwire_val == ((uint16_t) ERROR))) {
            continue;
        }
        printf("stop front:%d,  back:%d, diff:%d\r\n", front_trackwire_val, back_trackwire_val, front_trackwire_val - back_trackwire_val);
        delay(1000000);
    }

}

#endif


#ifdef TEST_SHOOTER
#include "FSMShoot.h"

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    RC_Init();
    PWM_Init();
    shooter_init();

    // RC_SetPulseTime(SERVO_TILT_PIN, 1800);
    //    //#define MINPULSE 550
    //    //#define MAXPULSE 2450 metsl serv
    //    IO_PortsSetPortBits(PORTX, SHOOTER_MOTOR_PIN);
    //    // IO_PortsClearPortBits(PORTX, SERVO_DELIVER_PIN);
    //    // RC_SetPulseTime(SERVO_TILT_PIN, 1400);
    //    IO_PortsSetPortBits(PORTX, SERVO_DELIVER_PIN);
    //
    //    //    
    //    //   RC_SetPulseTime(SERVO_TILT_PIN, 1800);
    //    //IO_PortsClearPortBits(PORTX, SERVO_DELIVER_PIN);
    //
    //
    //    //RC_SetPulseTime(SERVO_DELIVER_PIN, 1000);
    RC_SetPulseTime(SERVO_TILT_PIN, MINPULSE);
    PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, 350);
    delay(3000000);
    start_trigger_motor();
    delay(300000);
    stop_trigger_motor();
    //start_ball_accelerator();
    for (;;) {
        ;
        // delay(5000000);
        //        //
        //RC_SetPulseTime(SERVO_TILT_PIN, MAXPULSE);
        //delay(3000000);
        //RC_SetPulseTime(SERVO_TILT_PIN, MINPULSE);
        //delay(3000000);
        //    // RC_SetPulseTime(SERVO_TILT_PIN,  MAXPULSE);



    }

}
#endif

#ifdef TEST_DRIVING_MOTORS_HELPER_FUNCTIONS2

#include "motors.h"

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    PWM_Init();
    motors_init();
    tank_turn_right();

    for (;;) {
        ;

    }

}

#endif

#ifdef TEST_AD_BUG

#include "motors.h"

void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    AD_Init();
    int index = 0;
    const int tape_sensor_pins[TAPE_SENSOR_COUNT] = {TAPE_PIN_1, TAPE_PIN_2, TAPE_PIN_3, TAPE_PIN_4, TAPE_PIN_5};

    for (index = 0; index < TAPE_SENSOR_COUNT; index++) {
        int rc = AD_AddPins(tape_sensor_pins[index]);
    }

    for (;;) {
        int val = AD_ReadADPin(AD_AddPins(tape_sensor_pins[4]));
        printf("val=%d\r\n", val);
        delay(100000);


    }

}

#endif