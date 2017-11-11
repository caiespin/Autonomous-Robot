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
#include "HSM.h"
#include "Sub_HSM_Escape.h"
#include <stdio.h>

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define RELEASE_BUMPER_TIME 200
#define  BACKOUT_TIME 500

typedef enum {
    Release_Bumper_State,
    Backout_State,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"Release_Bumper_State",
	"Backout_State",
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

static TemplateSubHSMState_t CurrentState = Release_Bumper_State; // <- change name to match ENUM
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
uint8_t Init_Sub_HSM_Escape(void) {
    ES_Event returnEvent;

    CurrentState = Release_Bumper_State;
    returnEvent = Run_Sub_HSM_Escape(INIT_EVENT);
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
ES_Event Run_Sub_HSM_Escape(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum

    static int Bumper_Released = FALSE;
    static int Bumper_Released_Timed_Out = FALSE;

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case Release_Bumper_State: // If current state is initial Psedudo State
            switch (ThisEvent.EventType) {
                case ES_INIT: // If current state is initial Psedudo State
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Forward_State.\r\n");
                    Bumper_Released = FALSE;
                    Bumper_Released_Timed_Out = FALSE;


                    ES_Timer_InitTimer(SUB_HSM_RUN_SERVICE_TIMER, RELEASE_BUMPER_TIME);
                    ES_Timer_InitTimer(SUB_HSM_RUN_SERVICE_SECONDARY_TIMER, RELEASE_BUMPER_TIME * 2);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Exited Forward_State.\r\n");
                    ES_Timer_StopTimer(SUB_HSM_RUN_SERVICE_TIMER);
                    ES_Timer_StopTimer(SUB_HSM_RUN_SERVICE_SECONDARY_TIMER);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SUB_HSM_RUN_SERVICE_SECONDARY_TIMER) {
                        nextState = Backout_State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;


                    } else if (ThisEvent.EventParam == SUB_HSM_RUN_SERVICE_TIMER) {
                        Bumper_Released_Timed_Out = TRUE;
                        if (Bumper_Released == TRUE) {
                            nextState = Backout_State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                    }

                    break;
                case BUMPER_RELEASED:
                    Bumper_Released = TRUE;
                    if (Bumper_Released_Timed_Out == TRUE) {
                        nextState = Backout_State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;
            }
            break;

        case Backout_State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Backout_State.\r\n");
                    ES_Timer_InitTimer(SUB_HSM_RUN_SERVICE_TIMER, BACKOUT_TIME);
                    startRunningBackwards();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Backout_State.\r\n");
                    ES_Timer_StopTimer(SUB_HSM_RUN_SERVICE_TIMER);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SUB_HSM_RUN_SERVICE_TIMER) {

                        if (get_light_status() == FALSE) {
                            ThisEvent.EventType = GO_TO_STOP;


                        } else {
                            ThisEvent.EventType = GO_TO_RUN;

                        }


                    }

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
        // recursively call the current state with an exit event
        Run_Sub_HSM_Escape(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        Run_Sub_HSM_Escape(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

