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
#include "EventChecker.h"
#include "FSM_Service.h"
#include "MyService.h"
#include "roach.h"
#include <BOARD.h>
//Uncomment these for the Roaches
//#include "roach.h"
//#include "RoachFrameworkEvents.h"
#include <stdio.h>


/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define ESCAPE_TIME 500
#define STUCK_DETECTOR 5000

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
    Stop_State,
    Run_State,
    Escape_State,
    Spin_State,
} FSMState_t;

static const char *StateNames[] = {
	"Stop_State",
	"Run_State",
	"Escape_State",
	"Spin_State",
};


static FSMState_t CurrentState = Stop_State; // <- change enum name to match ENUM
static uint8_t MyPriority;



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
uint8_t Init_FSM_Service(uint8_t Priority) {
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
 * @Function PostTemplateFSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t Post_FSM_Service(ES_Event ThisEvent) {
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
int Escape_Collision_Counter = 0;

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
ES_Event Run_FSM_Service(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    FSMState_t nextState; // <- need to change enum type here

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
            printf("Received Event %d\r\n", ThisEvent);
        case Stop_State: // If current state is initial Psedudo State

            switch (ThisEvent.EventType) {

                case ES_INIT: // If current state is initial Psedudo State
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Stop State.\r\n");
                    stopRunning();

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Exited Stop State.\r\n");

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case INTO_LIGHT: // If current state is initial Psedudo State
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    nextState = Run_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMPER_PRESSED: // If current state is initial Psedudo State
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
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

        case Run_State: // in the first state, replace this with appropriate state

            switch (ThisEvent.EventType) {
                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Run State.\r\n");
                    startRunning();

                    ES_Timer_InitTimer(SERVICE_TIMER, STUCK_DETECTOR);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Exited Run State.\r\n");


                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case INTO_DARK: // If current state is initial Psedudo State
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    nextState = Stop_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMPER_PRESSED: // If current state is initial Psedudo State
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
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

                case ES_TIMEOUT:

                    nextState = Spin_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;



            }


            break;

        case Escape_State:

            switch (ThisEvent.EventType) {

                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Escape State.\r\n");
                    ES_Timer_InitTimer(FSM_SERVICE_TIMER, ESCAPE_TIME);

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Exited Escape State.\r\n");

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    break;

                case ES_TIMEOUT:
                    if (get_light_status() == FALSE) {
                        nextState = Stop_State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;


                    } else {
                        nextState = Run_State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    }
                    break;
                case BUMPER_PRESSED: // If current state is initial Psedudo State
                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state

                    // now put the machine into the actual initial state
                    
                    ES_Timer_InitTimer(FSM_SERVICE_TIMER, ESCAPE_TIME);
                   

                    switch (ThisEvent.EventParam) {
                        case Rear_Left:
                        case Rear_Right:
                            printf("Rear hit!!\r\n");
                            nextState = Run_State;
                            makeTransition = TRUE;
                          

                            break;
                        case Front_Left:
                            Turn_Back_Right();
                            break;
                        case Front_Right:
                            Turn_Back_Left();
                            printf("Front hit!!\r\n");
                            break;
                    }

                   
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


            }
            break;
        case Spin_State:

            switch (ThisEvent.EventType) {

                case ES_ENTRY: // If current state is initial Psedudo State
                    printf("Entered Spin State.\r\n");
                    ES_Timer_InitTimer(FSM_SERVICE_TIMER, 1000);

                    startSpinning();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT: // If current state is initial Psedudo State
                    printf("Exited Spin State.\r\n");

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    break;

                case ES_TIMEOUT:
                    if (get_light_status() == FALSE) {
                        nextState = Stop_State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;


                    } else {
                        nextState = Run_State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    }
                    break;


            }
            break;

        default: // all unhandled states fall into here
            break;
    } // end switch on Current State
    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        Run_FSM_Service(EXIT_EVENT);
        CurrentState = nextState;
        Run_FSM_Service(ENTRY_EVENT);
    }
    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
