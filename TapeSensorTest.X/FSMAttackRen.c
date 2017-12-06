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
#define REVERSE_TIME 2000
#define TWIST_RIGHT_TIME 250//280
#define TWIST_LEFT_TIME 400
#define  FORWARDS_TIME 200
#define REVERSE_LEFT_INTO_REN_TIME 500
#define REVERSE_RIGHT_INTO_REN_TIME 500

#define STOP_TIME 200
//#define INCH_FOWARDS1_TIME 200
//#define INCH_FOWARDS2_TIME 200
#define TANK_RIGHT_1_TIME (800)

#define TANK_LEFT_WU_1_TIME 400
#define TANK_LEFT_WU_2_TIME 200
#define TANK_RIGHT_WU_1_TIME 400
#define TANK_RIGHT_WU_2_TIME 200
#define INCH_FORWARDS_1_TIME 200
#define INCH_FORWARDS_2_TIME 200

typedef enum {
    InitPSubState,
    ReverseIntoRenState,
    ForwardsState,
    TwistLeftState,
    TwistRightState,
    TurnRight1State,
    TurnLeft1State,
    TankRight1State,
    TankRight2State,
    Attack_Ren_TankLeft1State,
    Attack_Ren_TankLeft2State,
    InchForwards1State,
    InchForwards2State,
    StopState_1,
    StopState_2,




    //  ShootRen,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"ReverseIntoRenState",
	"ForwardsState",
	"TwistLeftState",
	"TwistRightState",
	"TurnRight1State",
	"TurnLeft1State",
	"TankRight1State",
	"TankRight2State",
	"Attack_Ren_TankLeft1State",
	"Attack_Ren_TankLeft2State",
	"InchForwards1State",
	"InchForwards2State",
	"StopState_1",
	"StopState_2",
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
static int first_time = TRUE;


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
                nextState = TurnRight1State;
                first_time = TRUE;
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

                case BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & BACK_BUMPERS) {
                        case BACK_LEFT_BUMPER_PIN:
                            //nextState = TankRight1State;
                            nextState = ForwardsState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case BACK_RIGHT_BUMPER_PIN:
                            //nextState = Attack_Ren_TankLeft1State;
                           nextState = ForwardsState; 
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;

                case REN_BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & ALL_TRUE_REN_BUMPERS) {
                        case REN_LEFT_PIN:
                           // nextState = TankRight1State;
                            nextState = ForwardsState; 
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                        case REN_RIGHT_PIN:
                            //nextState = Attack_Ren_TankLeft2State;
                            nextState = ForwardsState; 
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                            break;
                    }
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        ThisEvent.EventType = GO_TO_FIND_LINE;
                        ThisEvent.EventParam = 0;
                        PostTopHSM(ThisEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case TAPE_DETECTED:
                    if (is_on_T() == TRUE) {
                        ThisEvent.EventType = REN_ALIGNED;
                        ThisEvent.EventParam = 0;
                        PostTopHSM(ThisEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    //                    switch (ThisEvent.EventParam) {
                    //
                    //
                    //                        case CENTER_TAPE_SENSOR:
                    //                            if ((get_left_tape_status() == off_tape) && (get_right_tape_status() == off_tape)
                    //                                    && (get_front_tape_status() == off_tape) && (get_back_tape_status() == off_tape)) {
                    //                                // first_time = FALSE;
                    //                                nextState = TurnLeft1State;
                    //                                makeTransition = TRUE;
                    //                                ThisEvent.EventType = ES_NO_EVENT;
                    //                            }
                    //                            break;
                    //
                    //                    }
                    break;
                case ES_EXIT:
                    first_time = FALSE;
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
                        nextState = StopState_1;
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
                        nextState = StopState_2;
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

        case TurnRight1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TANK_RIGHT_1_TIME);
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



        case TurnLeft1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_left();
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            ThisEvent.EventType = GO_TO_FIND_LINE;
                            ThisEvent.EventParam = 0;
                            PostTopHSM(ThisEvent);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                    }
                    break;

                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;


        case TankRight1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TANK_RIGHT_WU_1_TIME);
                    break;


                case BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & BACK_BUMPERS) {
                        case BACK_RIGHT_BUMPER_PIN:
                            nextState = ForwardsState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;

                case REN_BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & ALL_TRUE_REN_BUMPERS) {
                        case REN_RIGHT_PIN:
                            nextState = ForwardsState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                            break;
                    }
                    break;





                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = InchForwards1State;
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

        case Attack_Ren_TankLeft1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_left();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TANK_LEFT_WU_1_TIME);
                    break;


                case BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & BACK_BUMPERS) {
                        case BACK_LEFT_BUMPER_PIN:
                            nextState = ForwardsState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;

                case REN_BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & ALL_TRUE_REN_BUMPERS) {
                        case REN_LEFT_PIN:
                            nextState = ForwardsState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                            break;
                    }
                    break;





                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = InchForwards2State;
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

        case InchForwards1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, INCH_FORWARDS_1_TIME);
                    forwards();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = TankRight2State;
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

        case InchForwards2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, INCH_FORWARDS_2_TIME);
                    forwards();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = Attack_Ren_TankLeft2State;
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

        case TankRight2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TANK_RIGHT_WU_2_TIME);
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

        case Attack_Ren_TankLeft2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    tank_turn_right();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TANK_LEFT_WU_2_TIME);
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
        case StopState_1:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = TwistLeftState;
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

        case StopState_2:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, 1000);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = ReverseIntoRenState;
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

