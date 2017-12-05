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
#include "FSMAttackRen.h"
#include "motors.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define REVERSE_TIME 1000
#define TWIST_RIGHT_TIME 300
#define TWIST_LEFT_TIME 400
#define  FORWARDS_TIME 200
#define REVERSE_LEFT_INTO_REN_TIME 500
#define REVERSE_RIGHT_INTO_REN_TIME 500

#define STOP_TIME 200
#define INCH_FOWARDS1_TIME 200
#define INCH_FOWARDS2_TIME 200

typedef enum {
    InitPSubState,
    ReverseIntoRenState,
    ReverseLeftIntoRenState,
    ReverseRightIntoRenState,
    ForwardsState,
    TwistLeftState,
    TwistRightState,
    StopState1,
    StopState2,
    InchFowardsState1,
    InchFowardsState2,
    ReverseRightIntoRen1State,
    ReverseLeftIntoRen1State,


    //  ShootRen,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"ReverseIntoRenState",
	"ReverseLeftIntoRenState",
	"ReverseRightIntoRenState",
	"ForwardsState",
	"TwistLeftState",
	"TwistRightState",
	"StopState1",
	"StopState2",
	"InchFowardsState1",
	"InchFowardsState2",
	"ReverseRightIntoRen1State",
	"ReverseLeftIntoRen1State",
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
uint8_t InitFSMAttackRen(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFSMAttackRen(INIT_EVENT);
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
ES_Event RunFSMAttackRen(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum
    int bumpers;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = ReverseIntoRenState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;



        case ReverseIntoRenState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, REVERSE_TIME);
                    reverse();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = ForwardsState;
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

        case ReverseLeftIntoRenState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, REVERSE_LEFT_INTO_REN_TIME);
                    turn_back_left();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = StopState2;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (BACK_BUMPERS));
                    if ((bumpers == BACK_LEFT_BUMPER_PIN) || (bumpers == BACK_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState = ForwardsState;
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
        case ReverseRightIntoRenState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, REVERSE_RIGHT_INTO_REN_TIME);
                    turn_back_right();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = StopState1;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (BACK_BUMPERS));
                    if ((bumpers == BACK_RIGHT_BUMPER_PIN) || (bumpers == BACK_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState = ForwardsState;
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

        case ForwardsState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, FORWARDS_TIME);
                    forwards();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = TwistLeftState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case BUMPER_RELEASED:
                    bumpers = (ThisEvent.EventParam & (BACK_BUMPERS));
                    if ((bumpers == BACK_LEFT_BUMPER_PIN)) {

                        nextState = ReverseRightIntoRenState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    } else if ((bumpers == BACK_RIGHT_BUMPER_PIN)) {

                        nextState = ReverseLeftIntoRenState;
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
        case TwistLeftState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_left();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TWIST_LEFT_TIME);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = TwistRightState;
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


        case TwistRightState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TWIST_RIGHT_TIME);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = ReverseIntoRenState;
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
        case StopState1:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = InchFowardsState1;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                        //                        nextState = SweepLeft1State;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;

                    }
                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;
        case StopState2:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = InchFowardsState2;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                        //                        nextState = SweepLeft1State;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;

                    }
                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;
        case InchFowardsState1:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, INCH_FOWARDS1_TIME);
                    forwards();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = ReverseRightIntoRen1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case InchFowardsState2:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, INCH_FOWARDS2_TIME);
                    forwards();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = ReverseLeftIntoRen1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }

                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case ReverseRightIntoRen1State:

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_back_right();
                    break;

                case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (BACK_BUMPERS));
                    if ((bumpers == BACK_RIGHT_BUMPER_PIN) || (bumpers == BACK_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState = ForwardsState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }

            break;
        case ReverseLeftIntoRen1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_back_left();
                    break;

                case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (BACK_BUMPERS));
                    if ((bumpers == BACK_LEFT_BUMPER_PIN) || (bumpers == BACK_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState = ForwardsState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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
        RunFSMAttackRen(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFSMAttackRen(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

