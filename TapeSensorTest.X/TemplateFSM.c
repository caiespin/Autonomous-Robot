/*
 * File: TemplateFSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Flat State Machine to work with the Events and Services
 * Frameword (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that this file
 * will need to be modified to fit your exact needs, and most of the names will have
 * to be changed to match your code.
 *
 * This is provided as an example and a good place to start.
 *
 *Generally you will just be modifying the statenames and the run function
 *However make sure you do a find and replace to convert every instance of
 *  "Template" to your current state machine's name
 * History
 * When           Who     What/Why
 * -------------- ---     --------
 * 09/13/13 15:17 ghe      added tattletail functionality and recursive calls
 * 01/15/12 11:12 jec      revisions for Gen2 framework
 * 11/07/11 11:26 jec      made the queue static
 * 10/30/11 17:59 jec      fixed references to CurrentEvent in RunTemplateSM()
 * 10/23/11 18:20 jec      began conversion from SMTemplate.c (02/20/07 rev)
 */


/*******************************************************************************
 * MODULE #INCLUDE                                                             *
 ******************************************************************************/

#include <BOARD.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "IO_Ports.h"
#include "LED.h"
#include "TemplateFSM.h"

#include <AD.h>
//Uncomment these for the Roaches
//#include "roach.h"
//#include "RoachFrameworkEvents.h"
#include <stdio.h>


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define TAPE_PIN_1 AD_PORTW3
#define TAPE_PIN_2 AD_PORTW4
#define TAPE_PIN_3 AD_PORTW5
#define TAPE_PIN_4 AD_PORTW6
#define TAPE_PIN_5 AD_PORTW7


#define LED_PIN PIN3
#define TAPE_HIGH_THRESHOLD 400
#define TAPE_LOW_THRESHOLD 300
#define ALL_LEDS 0xF

#define ONE_MILLISECOND 2
#define FIFTY_MILLISECOND 25
/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine.*/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/

/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

typedef enum {
    InitPState,
    On,
    OnReading,
    Off,
    OffReading,
} TemplateFSMState_t;

static const char *StateNames[] = {
    "InitPState",
    "On",
    "OnReading",
    "Off",
    "OffReading",
};

struct {
    int pin;
    int high_val;
    int low_val;
    int last;
}tape_sensor;


static TemplateFSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;


static int tape1AdcValHigh = 0;
static int tape1AdcValLow = 0;
static int diff = 0;



/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateFSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitTemplateFSM(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = InitPState;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {

        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateFSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTemplateFSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

/**
 * @Function RunTemplateFSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the flat state machine,
 *        as this is called any time a new event is passed to the event queue. This
 *        function will be called recursively to implement the correct order for a
 *        state transition to be: exit current state -> enter next state using the
 *        ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       Returns ES_NO_EVENT if the event have been "consumed."
 * @author J. Edward Carryer, 2011.10.23 19:25 */
ES_Event RunTemplateFSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateFSMState_t nextState; // <- need to change enum type here

    ES_Tattle(); // trace call stack

    switch (CurrentState) {

        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                LED_Init();
                //Initialize Analog inputs
                AD_Init();
                AD_AddPins(TAPE_PIN_1);
                AD_AddPins(TAPE_PIN_2);
                AD_AddPins(TAPE_PIN_3);
                AD_AddPins(TAPE_PIN_4);
                AD_AddPins(TAPE_PIN_5);
                
                ES_Timer_Init();
                IO_PortsSetPortOutputs(PORTX, LED_PIN);


                LED_AddBanks(LED_BANK1);
                LED_OffBank(LED_BANK1, ALL_LEDS);
                ThisEvent.EventType = ES_NO_EVENT;


                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = On;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;




        case On: // If current state is initial Psedudo State

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    printf("enter on_entry\r\n");
                    IO_PortsSetPortBits(PORTX, LED_PIN); //turn on the LED on the IR sensor

                    int rc = ES_Timer_InitTimer(TAPE_SENSOR_TIMER, ONE_MILLISECOND);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    nextState = OnReading;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State

                case ES_TIMERACTIVE:
                    printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

            }

            break;

        case OnReading:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    tape1AdcValHigh = AD_ReadADPin(TAPE_PIN_1);
                    ES_Timer_InitTimer(TAPE_SENSOR_TIMER, FIFTY_MILLISECOND);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    nextState = Off;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

            }

            break;


        case Off: // 
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    printf("Off_enter on_entry\r\n");
                    IO_PortsClearPortBits(PORTX, LED_PIN); //turn on the LED on the IR sensor
                    int rc = ES_Timer_InitTimer(TAPE_SENSOR_TIMER, ONE_MILLISECOND);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    nextState = OffReading;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

            }
            break;

        case OffReading: //
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    tape1AdcValLow = AD_ReadADPin(TAPE_PIN_1);
                    ES_Timer_InitTimer(TAPE_SENSOR_TIMER, FIFTY_MILLISECOND);
                    ThisEvent.EventType = ES_NO_EVENT;



                    diff = tape1AdcValLow - tape1AdcValHigh;
                    if (diff < TAPE_LOW_THRESHOLD) {
                        LED_SetBank(LED_BANK1, ALL_LEDS);
                    } else if (diff > TAPE_HIGH_THRESHOLD) {
                        LED_OffBank(LED_BANK1, ALL_LEDS);
                    }

                    printf("diff-----------------> %d \r\n", diff);
                    break;
                case ES_TIMEOUT:
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    nextState = On;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

            }
            break;


        default: // all unhandled states fall into here
            break;
    } // end switch on Current State
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunTemplateFSM(EXIT_EVENT);
        CurrentState = nextState;
        RunTemplateFSM(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
