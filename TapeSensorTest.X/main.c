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


//#define TEST_TAPE_SENSOR
#define TEST_TAPE_SENSOR_WITH_ES_FRAMEWORK
//#define TEST_BUMPER


#define TAPE_PIN_1 AD_PORTW3

#define  FRONT_LEFT_BUMPER_PIN PIN3
#define  FRONT_RIGHT_BUMPER_PIN PIN4
#define  BACK_LEFT_BUMPER_PIN PIN5
#define  BACK_RIGHT_BUMPER_PIN PIN6



#define LED_PIN PIN3
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
    AD_AddPins(TAPE_PIN_1);

    IO_PortsSetPortOutputs(PORTX, LED_PIN);


    LED_AddBanks(LED_BANK1);
    LED_OffBank(LED_BANK1, ALL_LEDS);
    //  IO_PortsClearPortBits(PORTX, LED_PIN);

    // IO_PortsSetPortBits(PORTX, LED_PIN);
    // int pot_val =
    while (1) {

        IO_PortsSetPortBits(PORTX, LED_PIN);
        delay(8000);
        tape1AdcValHigh = AD_ReadADPin(TAPE_PIN_1);
        //printf("tape1AdcVal = %d\r\n", tape1AdcVal);
        delay(100000);
        IO_PortsClearPortBits(PORTX, LED_PIN);
        delay(8000);
        tape1AdcValLow = AD_ReadADPin(TAPE_PIN_1);
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

#define BUMPER_PORT PORTY

#define ALL_BUMPER_PINS (FRONT_LEFT_BUMPER_PIN | FRONT_RIGHT_BUMPER_PIN | BACK_LEFT_BUMPER_PIN |  BACK_RIGHT_BUMPER_PIN)


void delay(int x) {
    int i = 0;
    while (i < x) {
        i++;
    }
}

int main() {
    BOARD_Init();
    IO_PortsSetPortInputs(BUMPER_PORT,  FRONT_LEFT_BUMPER_PIN);
    IO_PortsSetPortInputs(BUMPER_PORT,   FRONT_RIGHT_BUMPER_PIN);
    IO_PortsSetPortInputs(BUMPER_PORT,  BACK_LEFT_BUMPER_PIN);
    IO_PortsSetPortInputs(BUMPER_PORT,  BACK_RIGHT_BUMPER_PIN);

    while (1) {
        printf("Status:%d \r\n", ((IO_PortsReadPort(BUMPER_PORT)) & ALL_BUMPER_PINS) >> SHIFT_AMOUNT );
        delay(1000000);
    }
    for (;;)
        ;
}
#endif
