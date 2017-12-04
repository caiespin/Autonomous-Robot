/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel H Elkaim
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is for a substate machine. Make sure it has a unique name
 *
 * This is provided as an example and a good place to start.
 *
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
#include "BOARD.h"
#include "TopHSM.h"
#include "FSM_Find_Line.h"
#include "motors.h"
//#include "LED.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define INCH_RIGHT_TIME 200

typedef enum {
    InitPSubState,
    DrivingForwardState,
    TurnLeftState,
    TurnRightState,
    DrivingForward2State,
    TurnRight2State,
    InchRight,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"DrivingForwardState",
	"TurnLeftState",
	"TurnRightState",
	"DrivingForward2State",
	"TurnRight2State",
	"InchRight",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */

/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateSubHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t InitFSMFindLine(void) {
    ES_Event returnEvent;
    //    LED_Init();
    //
    //    LED_AddBanks(LED_BANK1);
    //    LED_AddBanks(LED_BANK2);
    //    LED_AddBanks(LED_BANK3);
    //    LED_OffBank(LED_BANK1, ALL_LEDS);
    //    LED_OffBank(LED_BANK2, ALL_LEDS);
    //    LED_OffBank(LED_BANK3, ALL_LEDS);


    CurrentState = InitPSubState;
    returnEvent = RunFSMFindLine(INIT_EVENT);
    if (returnEvent.EventType == ES_NO_EVENT) {
        return TRUE;
    }
    return FALSE;
}

/**
 * @Function RunTemplateSubHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be responded.
 * @return Event - return event (type and param), in general should be ES_NO_EVENT
 * @brief This function is where you implement the whole of the heirarchical state
 *        machine, as this is called any time a new event is passed to the event
 *        queue. This function will be called recursively to implement the correct
 *        order for a state transition to be: exit current state -> enter next state
 *        using the ES_EXIT and ES_ENTRY events.
 * @note Remember to rename to something appropriate.
 *       The lower level state machines are run first, to see if the event is dealt
 *       with there rather than at the current level. ES_EXIT and ES_ENTRY events are
 *       not consumed as these need to pass pack to the higher level state machine.
 * @author J. Edward Carryer, 2011.10.23 19:25
 * @author Gabriel H Elkaim, 2011.10.23 19:25 */
ES_Event RunFSMFindLine(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = DrivingForwardState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case DrivingForwardState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    if ((get_front_tape_status() == on_tape) && (get_center_tape_status() == on_tape)) {
                        ThisEvent.EventType = LINE_FOUND;
                    } else if ((get_front_tape_status() == on_tape) && (get_center_tape_status() == off_tape)) {
                        nextState = DrivingForward2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else {
                        forwards();
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case RIGHT_TAPE_SENSOR:
                            nextState = TurnRightState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                            break;
                        case FRONT_TAPE_SENSOR:
                            nextState = DrivingForward2State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;


                            break;
                        case LEFT_TAPE_SENSOR:
                            nextState = TurnLeftState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;


                            break;
                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case TurnRightState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_right();
                    // LED_SetBank(LED_BANK1, 2);
                    //LED_OffBank(LED_BANK2, ALL_LEDS);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {


                        case FRONT_TAPE_SENSOR:
                            nextState = DrivingForward2State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case TurnLeftState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_left();
                    //  LED_SetBank(LED_BANK1, 4);
                    //  LED_OffBank(LED_BANK2, ALL_LEDS);
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {


                        case FRONT_TAPE_SENSOR:
                            nextState = DrivingForward2State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case DrivingForward2State: // in the first state, replace this with correct names


            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ThisEvent.EventType = ES_NO_EVENT;
                    if ((get_front_tape_status() == on_tape) && (get_center_tape_status() == on_tape)) {
                        ThisEvent.EventType = LINE_FOUND;
                    } else if (get_center_tape_status() == on_tape) {
                        nextState = TurnRight2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    forwards();
                    //   LED_SetBank(LED_BANK1, 8);
                    //  LED_OffBank(LED_BANK2, ALL_LEDS);

                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {


                        case CENTER_TAPE_SENSOR:
                            nextState = TurnRight2State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;
        case TurnRight2State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    //   LED_SetBank(LED_BANK2, 1);
                    //   LED_OffBank(LED_BANK1, ALL_LEDS);

                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {


                        case FRONT_TAPE_SENSOR:

                            nextState = InchRight;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case InchRight: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(FIND_LINE_TIMER, INCH_RIGHT_TIME);

                    break;
                case ES_TIMEOUT:

                    switch (ThisEvent.EventParam) {
                        case FIND_LINE_TIMER:
                            ThisEvent.EventType = LINE_FOUND;
                            break;
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

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        ES_Timer_InitTimer(OH_SHIT_TIMER, OH_SHIT_TIME);
        // recursively call the current state with an exit event
        RunFSMFindLine(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFSMFindLine(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

