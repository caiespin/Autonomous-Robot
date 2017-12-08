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
#include "FSMExitShooter.h"
#include "event_checker.h"
#include <stdio.h>
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define TANK_TURN_TIME 880

#define  WAIT_TIME 1500
#define REVERSE_TIME 1000

typedef enum {
    InitPSubState,
    TankTurnLeft,
    Waiting,
    Reverse,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"TankTurnLeft",
	"Waiting",
	"Reverse",
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

static int ATM6_Counter = 0;
//static int  ATM6_Counter=3;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/

int get_ATM6_Counter() {
    return ATM6_Counter;

}

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
uint8_t InitFSMExitShooter(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFSMExitShooter(INIT_EVENT);
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
ES_Event RunFSMExitShooter(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum
    static int atm6_hit = FALSE;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = Waiting;
                makeTransition = TRUE;
                atm6_hit = FALSE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;



        case Waiting: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    stop_ball_accelerator();
                    stop();
                    ES_Timer_InitTimer(EXIT_SHOOTER_TIMER, WAIT_TIME);


                    break;

                case ES_TIMEOUT:
                    if (get_back_track_wire_on() == FALSE) {
                        atm6_hit = TRUE;

                    }
                    nextState = TankTurnLeft;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;


                    break;
                    //                case TRACKWIRE_LOST:
                    //                    ThisEvent.EventType = GO_TO_ON_LINE;
                    //                    ThisEvent.EventParam = 0;
                    //                    PostTopHSM(ThisEvent);
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    ATM6_Counter++;
                    //                    printf("\r\nATM6 DOWN1!!!!!!!, counter= %d\r\n", ATM6_Counter);
                    //                    break;
                case TRACKWIRE_LOST:
                    if (ThisEvent.EventParam == BACK_TRACKWIRE) {
                        atm6_hit = TRUE;
                        nextState = TankTurnLeft;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;
                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            };

            break;

        case TankTurnLeft: // in the first state, replace this with correct names

            switch (ThisEvent.EventType) {
                case ES_ENTRY:

                    //  LED_SetBank(LED_BANK1, 0xf);
                    //  ES_Timer_InitTimer(EXIT_SHOOTER_TIMER, TANK_TURN_TIME);
                    tank_turn_left();

                    break;

                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            if (atm6_hit == TRUE) {
                                ThisEvent.EventType = GO_TO_ON_LINE;
                                ThisEvent.EventParam = 0;
                                PostTopHSM(ThisEvent);
                                ThisEvent.EventType = ES_NO_EVENT;
                                ATM6_Counter++;
                                printf("\r\nATM6 DOWN2!!!!!!!,--------------------> counter= %d\r\n", ATM6_Counter);
                            } else {

                                nextState = Reverse;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            break;
                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            };

            break;



        case Reverse: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:

                    //  LED_SetBank(LED_BANK1, 0xf);
                    ES_Timer_InitTimer(EXIT_SHOOTER_TIMER, REVERSE_TIME);
                    reverse();
                    break;

                case ES_TIMEOUT:
                    ThisEvent.EventType = GO_TO_ON_LINE;
                    ThisEvent.EventParam = 0;
                    PostTopHSM(ThisEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            };
            break;


        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFSMExitShooter(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFSMExitShooter(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

