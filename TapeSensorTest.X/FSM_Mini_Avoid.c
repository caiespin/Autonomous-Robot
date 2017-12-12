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
#include "FSM_Mini_Avoid.h"
#include "motors.h"
#include "FSMExitShooter.h"
#include "stdio.h"
#include "ES_Timers.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define STOP_TIME 100
#define ADJUST_TIME 0
//#define REVERSE_TIME 100

#define REVERSE_TIME 150
#define TANK_RIGHT_TIME 550
#define TANK_RIGHT_SMALL_TIME 450
#define TANK_TURN_LEFT_TIME 450

#define TANK_LEFT_TIME 1700
#define FORWARDS1_TIME 1000
#define ARC_LEFT_TIME 5000
#define  ARC_LEFT_SLOW_TIME 7000
#define FORWARDS2_TIME 2000
#define TURN_180_1_TIME 1600
#define TURN_90_1_TIME 700
#define LINE_FOLLOWER_STATE 2
#define SWEEP_LEFT_1_TIME 800
#define SWEEP_RIGHT_1_TIME 1100
#define SWEEP_RIGHT_2_TIME 1100
#define INCH_BACK_TIME 200
#define INCH_FOWARDS_TIME 100

#define ARC_LEFT_2_TIME 600
#define ARC_LEFT_3_TIME 1200
#define INCH_FORWARDS_3_TIME 650

typedef enum {
    InitPSubState,
    Stop1State,
    ReverseState,
    Stop2State,
    TankRightState,
    Stop3State,
    ArcLeftState,

    InchForwards3State,
    ArcLeftState_2,
    ArcLeftState_3,
    Stop6State,
    Stop7State,
    TankLeft2State,
    Turn_180_1,
    Turn_90_1,
    InchBackState,
    InchForwardsState,
    Stop4State,
    TankTurnLeftState,
    StopState_6,




} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Stop1State",
	"ReverseState",
	"Stop2State",
	"TankRightState",
	"Stop3State",
	"ArcLeftState",
	"InchForwards3State",
	"ArcLeftState_2",
	"ArcLeftState_3",
	"Stop6State",
	"Stop7State",
	"TankLeft2State",
	"Turn_180_1",
	"Turn_90_1",
	"InchBackState",
	"InchForwardsState",
	"Stop4State",
	"TankTurnLeftState",
	"StopState_6",
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

static int bumper_pressed_counter = 0;
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
uint8_t InitFSMMiniAvoid(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFSMMiniAvoid(INIT_EVENT);
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
ES_Event RunFSMMiniAvoid(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum
    static uint32_t start_time = 0;
    static uint32_t end_time = 0;
    static int first_time_flag = 0;
    uint32_t difference_time = 0;
    static int forward_flag = 0;
    first_time_flag = 0;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                bumper_pressed_counter++;
                nextState = ReverseState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;

            }
            break;

            //        case Stop1State: // in the first state, replace this with correct names
            //            switch (ThisEvent.EventType) {
            //
            //
            //                case ES_ENTRY:
            //
            //                    ES_Timer_InitTimer(MINI_AVOID_TIMER, STOP_TIME);
            //                    stop();
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_TIMEOUT:
            //                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
            //                        nextState = ReverseState;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //
            //                case ES_TIMERACTIVE:
            //                case ES_TIMERSTOPPED:
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //
            //
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;


        case ReverseState:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, REVERSE_TIME);
                    reverse();
                    ThisEvent.EventType = ES_NO_EVENT;

                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {

                        nextState = Stop2State;
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

        case Stop2State:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {

                        nextState = TankRightState;
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

        case TankRightState:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    if (first_time_flag == 0) {
                        ES_Timer_InitTimer(MINI_AVOID_TIMER, TANK_RIGHT_TIME);
                        first_time_flag = 1;
                    } else {
                        ES_Timer_InitTimer(MINI_AVOID_TIMER, TANK_RIGHT_SMALL_TIME);
                    }
                    tank_turn_right();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        nextState = Stop3State;
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
        case Stop3State:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        nextState = ArcLeftState;
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
        case ArcLeftState:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    if (first_time_flag == 0) {
                       arc_left();
                        first_time_flag = 1;
                    } else {
                        arc_steep_left();
                    }
                    //    if (get_ATM6_Counter() >= 3) {
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, ARC_LEFT_TIME);
                   
                    static int start_time;
                    start_time = ES_Timer_GetTime();
                    //                    } else {
                    //                        ES_Timer_InitTimer(MINI_AVOID_TIMER, ARC_LEFT_SLOW_TIME);
                    //                        arc_left_long();
                    //                    }

                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case RIGHT_TAPE_SENSOR:
                        case FRONT_TAPE_SENSOR:
                        case LEFT_TAPE_SENSOR:
                            if ((ES_Timer_GetTime() - start_time) > 1000 && ((ES_Timer_GetTime() - start_time) < 1800)) {
                                printf("\r\nTIME IS:%d -------->>\r\n", ES_Timer_GetTime() - start_time);
                                //1272
                                //1653
                                //1714
                                //1564
                                nextState = Stop4State;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            } else {
                                ThisEvent.EventType = OBSTACLE_AVOIDED;
                                ThisEvent.EventParam = 0;
                                PostTopHSM(ThisEvent);
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            break;
                    }
                    break;


                case BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & FRONT_BUMPERS) {
                        case FRONT_BUMPERS:
                        case FRONT_LEFT_BUMPER_PIN:
                        case FRONT_RIGHT_BUMPER_PIN:
                            bumper_pressed_counter = 0;
                            nextState = ReverseState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                    }
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        ThisEvent.EventType = OBSTACLE_AVOIDED;
                        ThisEvent.EventParam = 0;
                        PostTopHSM(ThisEvent);
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }


            break;

        case Stop4State:

            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        if (get_ATM6_Counter() >= 3) {
                            ThisEvent.EventType = GO_TO_ATTACK_REN;
                            ThisEvent.EventParam = 0;
                            PostTopHSM(ThisEvent);
                            ThisEvent.EventType = ES_NO_EVENT;

                        } else {
                            nextState = InchForwards3State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;

                        }

                    }
                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }


            break;


            //        case TankTurnLeftState:
            //
            //            switch (ThisEvent.EventType) {
            //
            //                case ES_ENTRY:
            //                    ES_Timer_InitTimer(MINI_AVOID_TIMER, TANK_TURN_LEFT_TIME);
            //                    tank_turn_left();
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_TIMEOUT:
            //
            //                    ThisEvent.EventType = GO_TO_FIND_LINE;
            //                    ThisEvent.EventParam = 0;
            //                    PostTopHSM(ThisEvent);
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //
            //                    break;
            //
            //                case ES_TIMERACTIVE:
            //                case ES_TIMERSTOPPED:
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //            }
            //
            //
            //            break;
        case InchForwards3State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, INCH_FORWARDS_3_TIME);
                    forwards();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        nextState = StopState_6;
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

        case StopState_6:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(MINI_AVOID_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {

                        nextState = ArcLeftState_2;
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

        case ArcLeftState_2:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:


                    ES_Timer_InitTimer(MINI_AVOID_TIMER, ARC_LEFT_2_TIME);
                    arc_steep_left();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        nextState = ArcLeftState_3;
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

        case ArcLeftState_3:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:


                    ES_Timer_InitTimer(MINI_AVOID_TIMER, ARC_LEFT_3_TIME);
                    arc_steep_left();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case RIGHT_TAPE_SENSOR:
                        case FRONT_TAPE_SENSOR:
                        case LEFT_TAPE_SENSOR:
                            ThisEvent.EventType = GO_TO_FIND_LINE;
                            ThisEvent.EventParam = 0;
                            PostTopHSM(ThisEvent);
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                    }
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == MINI_AVOID_TIMER) {
                        ThisEvent.EventType = GO_TO_FIND_LINE;
                        ThisEvent.EventParam = 0;
                        PostTopHSM(ThisEvent);
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
        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFSMMiniAvoid(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFSMMiniAvoid(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

void reset_bumper_counter() {
    bumper_pressed_counter = 0;
}
/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

