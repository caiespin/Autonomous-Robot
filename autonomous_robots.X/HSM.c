/*
 * File: TemplateSubHSM.c
 * Author: J. Edward Carryer
 * Modified: Gabriel Elkaim and Soja-Marie Morgens
 *
 * Template file to set up a Heirarchical State Machine to work with the Events and
 * Services Framework (ES_Framework) on the Uno32 for the CMPE-118/L class. Note that
 * this file will need to be modified to fit your exact needs, and most of the names
 * will have to be changed to match your code.
 *
 * There is another template file for the SubHSM's that is slightly differet, and
 * should be used for all of the subordinate state machines (flat or heirarchical)
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
#include "HSM.h"
#include "Sub_HSM_Escape.h"
#include "Sub_HSM_Run.h" //#include all sub state machines called
#include <stdio.h>
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/



typedef enum {
    Stop_State,
    Run_State,
    Escape_State,
} HSMState_t;

static const char *StateNames[] = {
	"Stop_State",
	"Run_State",
	"Escape_State",
};


/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine
   Example: char RunAway(uint_8 seconds);*/
/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/
/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

static HSMState_t CurrentState = Stop_State; // <- change enum name to match ENUM
static uint8_t MyPriority;


/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

/**
 * @Function InitTemplateHSM(uint8_t Priority)
 * @param Priority - internal variable to track which event queue to use
 * @return TRUE or FALSE
 * @brief This will get called by the framework at the beginning of the code
 *        execution. It will post an ES_INIT event to the appropriate event
 *        queue, which will be handled inside RunTemplateFSM function. Remember
 *        to rename this to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t Init_HSM_Service(uint8_t Priority) {
    MyPriority = Priority;
    // put us into the Initial PseudoState
    CurrentState = Stop_State;
    // post the initial transition event
    if (ES_PostToService(MyPriority, INIT_EVENT) == TRUE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/**
 * @Function PostTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t Post_HSM_Service(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
}

void startRunning() {
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(100);
}

void Turn_Right() {
    Roach_LeftMtrSpeed(100);
    Roach_RightMtrSpeed(60);
}

void Turn_Left() {
    Roach_LeftMtrSpeed(60);
    Roach_RightMtrSpeed(100);
}

void Turn_Back_Right() {
    Roach_LeftMtrSpeed(-60);
    Roach_RightMtrSpeed(-100);
}

void Turn_Back_Left() {
    Roach_LeftMtrSpeed(-100);
    Roach_RightMtrSpeed(-60);
}

void startRunningBackwards() {
    Roach_LeftMtrSpeed(-100);
    Roach_RightMtrSpeed(-100);
}

void startSpinning() {
    Roach_LeftMtrSpeed(-100);
    Roach_RightMtrSpeed(100);
}

void stopRunning() {
    Roach_LeftMtrSpeed(0);
    Roach_RightMtrSpeed(0);
}

/**
 * @Function RunTemplateHSM(ES_Event ThisEvent)
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
ES_Event Run_HSM_Service(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    HSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case Stop_State: // If current state is initial Pseudo State
            switch (ThisEvent.EventType) {

                case ES_INIT:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_ENTRY:
                    printf("Entered Stop State.\r\n");
                    stopRunning();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    printf("Exited Stop State.\r\n");
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case INTO_LIGHT:

                    nextState = Run_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMPER_PRESSED:

                    nextState = Escape_State;
                    switch (ThisEvent.EventParam) {
                        case Rear_Left:
                            Turn_Right();
                            break;
                        case Rear_Right:
                            printf("Rear hit!!\r\n");
                            Turn_Left();

                            break;
                        case Front_Left:
                            Turn_Back_Right();
                            break;
                        case Front_Right:
                            Turn_Back_Left();
                            printf("Front hit!!\r\n");
                            break;
                    }

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

            }
            break;

        case Run_State: // in the first state, replace this with correct names
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            ThisEvent = Run_Sub_HSM_Run(ThisEvent);
            switch (ThisEvent.EventType) {
                case INTO_DARK:
                    nextState = Stop_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMPER_PRESSED:


                    switch (ThisEvent.EventParam) {
                        case Rear_Left:
                            Turn_Right();
                            break;
                        case Rear_Right:
                            //printf("Rear hit!!\r\n");
                            Turn_Left();

                            break;
                        case Front_Left:
                            Turn_Back_Right();
                            break;
                        case Front_Right:
                            Turn_Back_Left();
                            // printf("Front hit!!\r\n");
                            break;
                    }
                    nextState = Escape_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;
        case Escape_State: // in the first state, replace this with correct names
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            ThisEvent = Run_Sub_HSM_Escape(ThisEvent);
            switch (ThisEvent.EventType) {
                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Escape_State.\r\n");
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Exited Escape_State.\r\n");
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case GO_TO_RUN: // If current state is initial Psedudo State
                    printf("Exited Escape_State.\r\n");
                    nextState = Run_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case GO_TO_STOP: // If current state is initial Psedudo State
                    printf("Exited Escape_State.\r\n");
                    nextState = Stop_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        Run_HSM_Service(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        Run_HSM_Service(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
