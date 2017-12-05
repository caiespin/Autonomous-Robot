
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

#include "ES_Configure.h"
#include "ES_Framework.h"

#include "FSM_Line_Follower.h"
#include "tape_detector_fsm_service.h"

#include <BOARD.h>
#include "motors.h"
#include <stdio.h>
//#include "LED.h"
#include "ES_Timers.h"


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define WIGGLE_LEFT_TIME 400
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
    on_line,
    on_left_side,
    on_right_side,
    corner_detected,
    turning_corner,
    wiggle_left,
    reverse_state,
    InchRight,
    InchLeft,
} TemplateFSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"on_line",
	"on_left_side",
	"on_right_side",
	"corner_detected",
	"turning_corner",
	"wiggle_left",
	"reverse_state",
	"InchRight",
	"InchLeft",
};


static TemplateFSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;

#define ALL_LEDS 0xF
#define REVERSE_TIME 600
#define INCH_RIGHT_TIME 3
#define INCH_LEFT_TIME 3
#define CORNER_DETECTED_TIMEOUT_TIME 500
#define TURNING_RIGHT_TIMEOUT_TIME 4000
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
uint8_t InitFSMLineFollower(uint8_t Priority) {
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
uint8_t PostFSMLineFollower(ES_Event ThisEvent) {
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
ES_Event RunFSMLineFollower(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateFSMState_t nextState; // <- need to change enum type here

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_ENTRY)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = on_line;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case on_line: // 
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    forwards();
                    //  LED_SetBank(LED_BANK1, 1);
                    // LED_OffBank(LED_BANK2, ALL_LEDS);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case RIGHT_TAPE_SENSOR:

                            if (get_front_tape_status() == on_tape) {
                                nextState = corner_detected;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            } else if (get_front_tape_status() == off_tape) {
                                nextState = on_left_side;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }


                            break;
                        case LEFT_TAPE_SENSOR:

                            if (get_front_tape_status() == off_tape) {
                                nextState = on_right_side;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }


                            break;
                    }

                    // printf("Tape Detected , param=%d\r\n", ThisEvent.EventParam);

                    break;
                case TAPE_LOST:

                    switch (ThisEvent.EventParam) {
                        case CENTER_TAPE_SENSOR:

                            if ((get_front_tape_status() == off_tape) && (get_left_tape_status() == off_tape) &&
                                    (get_right_tape_status() == off_tape)) {
                                //  LED_SetBank(LED_BANK3, 1);
                                //LED_OffBank(LED_BANK2, ALL_LEDS);

                                nextState = reverse_state;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            break;
                    }




                    // printf("Tape Lost , param=%d\r\n", ThisEvent.EventParam);

                    break;
            }
            break;

        case on_left_side:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_right();
                   // tank_turn_right();
                            
                            
                    // LED_SetBank(LED_BANK1, 2);
                    // LED_OffBank(LED_BANK2, ALL_LEDS);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            nextState = InchRight;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }

            break;
        case on_right_side:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //tank_turn_left();
                    turn_left();
                    // LED_SetBank(LED_BANK1, 4);
                    //  LED_OffBank(LED_BANK2, ALL_LEDS);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            nextState = InchLeft;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;
        case corner_detected:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    forwards();
                    //  LED_SetBank(LED_BANK1, 8);
                    //   LED_OffBank(LED_BANK2, ALL_LEDS);

                    ES_Timer_InitTimer(TAPE_FOLLOWER_TIMER, CORNER_DETECTED_TIMEOUT_TIME);
                    break;
                case TAPE_LOST:
                    switch (ThisEvent.EventParam) {
                        case RIGHT_TAPE_SENSOR:
                            ES_Timer_StopTimer(TAPE_FOLLOWER_TIMER);
                            nextState = turning_corner;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }


                    break;
            }
            break;
        case turning_corner:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(TAPE_FOLLOWER_TIMER, TURNING_RIGHT_TIMEOUT_TIME);
                    //  LED_SetBank(LED_BANK2, 1);
                    //   LED_OffBank(LED_BANK1, ALL_LEDS);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            ES_Timer_StopTimer(TAPE_FOLLOWER_TIMER);
                            nextState = InchRight;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:

                    if (ThisEvent.EventParam == TAPE_FOLLOWER_TIMER) {
                        ES_Timer_StopTimer(TAPE_FOLLOWER_TIMER);
                        nextState = InchRight;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

              
                case ES_EXIT:
                    // LED_OffBank(LED_BANK3, 0xf);
                    break;
            }
            break;

        case InchRight: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //tank_turn_right();
                    turn_right();
                    ES_Timer_InitTimer(TAPE_FOLLOWER_TIMER, INCH_RIGHT_TIME);

                    break;
                case ES_TIMEOUT:

                    if (ThisEvent.EventParam == TAPE_FOLLOWER_TIMER) {
                        nextState = on_line;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case InchLeft: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    //tank_turn_left();
                    turn_left();
                    ES_Timer_InitTimer(TAPE_FOLLOWER_TIMER, INCH_LEFT_TIME);

                    break;
                case ES_TIMEOUT:

                    if (ThisEvent.EventParam == TAPE_FOLLOWER_TIMER) {
                        nextState = on_line;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case reverse_state:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    reverse();
                    ES_Timer_InitTimer(TAPE_FOLLOWER_TIMER, REVERSE_TIME);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == TAPE_FOLLOWER_TIMER) {
                        nextState = wiggle_left;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }

            break;

        case wiggle_left:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_left();
                    ES_Timer_InitTimer(TAPE_FOLLOWER_TIMER, WIGGLE_LEFT_TIME);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            ES_Timer_StopTimer(TAPE_FOLLOWER_TIMER);
                            nextState = on_line;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == TAPE_FOLLOWER_TIMER) {
                        nextState = turning_corner;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
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
        ES_Timer_InitTimer(OH_SHIT_TIMER, OH_SHIT_TIME);
        RunFSMLineFollower(EXIT_EVENT);
        CurrentState = nextState;
        RunFSMLineFollower(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
