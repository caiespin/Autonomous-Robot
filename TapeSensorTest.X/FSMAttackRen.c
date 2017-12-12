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
#include "event_checker.h"
#include "motors.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define ADJUST_TURNING_COUNT 2

#define REVERSE_TIME 2000
#define FAST_TWIST_RIGHT_TIME 200//230//250//280
#define FAST_TWIST_LEFT_TIME 350//400
#define SLOW_TWIST_RIGHT_TIME 150//280
#define SLOW_TWIST_LEFT_TIME 300



#define  FORWARDS_TIME 150//200
#define REVERSE_LEFT_INTO_REN_TIME 500
#define REVERSE_RIGHT_INTO_REN_TIME 500

#define STOP_TIME 200
//#define INCH_FOWARDS1_TIME 200
//#define INCH_FOWARDS2_TIME 200
#define TANK_RIGHT_1_TIME (600) //800
//#define TANK_RIGHT_2_TIME (500) //800

#define TANK_LEFT_WU_1_TIME 400
#define TANK_LEFT_WU_2_TIME 200
#define TANK_RIGHT_WU_1_TIME 400
#define TANK_RIGHT_WU_2_TIME 200
#define INCH_FORWARDS_1_TIME 200
#define INCH_FORWARDS_2_TIME 200
#define ADJUST_LEFT_1_TIME 300//350 //150
#define ADJUST_RIGHT_1_TIME 300//350

#define INCH_FORWARDS_3_TIME 320//340//350//380//440//490 //600
#define BACK_UP_GET_IN_POSITION_TIME 500

#define ARC_LEFT_1_TIME 600
#define ARC_LEFT_2_TIME 1200
#define TANK_TURN_1_TIME 370//400//500

typedef enum {
    InitPSubState,
    ReverseIntoRenState,
    ForwardsState,
    TwistLeftState,
    TwistRightState,
    TurnRight1State,
    TurnRight2State,
    TurnLeft1State,

    StopState_1,
    StopState_2,
    StopState_3,
    StopState_4,
    StopState_5,
    StopState_6,
    StopState_7,
    StopState_8,
    StopState_9,
    AdjustLeftState1,
    AdjustRightState1,
    InchForwards3State,
    ArcLeftState_1,
    ArcLeftState_2,
    TankTurnLeftState_1,



    //  ShootRen,
} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"ReverseIntoRenState",
	"ForwardsState",
	"TwistLeftState",
	"TwistRightState",
	"TurnRight1State",
	"TurnRight2State",
	"TurnLeft1State",
	"StopState_1",
	"StopState_2",
	"StopState_3",
	"StopState_4",
	"StopState_5",
	"StopState_6",
	"StopState_7",
	"StopState_8",
	"StopState_9",
	"AdjustLeftState1",
	"AdjustRightState1",
	"InchForwards3State",
	"ArcLeftState_1",
	"ArcLeftState_2",
	"TankTurnLeftState_1",
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
static int back_right_bumper_counter = 0;
static int back_left_bumper_counter = 0;
static int go_to_reverse = FALSE;

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

void set_ATTACK_REN_to_reverse() {
    go_to_reverse = TRUE;
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
    static int Twist_Right_Time = FAST_TWIST_RIGHT_TIME;
    static int Twist_Left_Time = FAST_TWIST_LEFT_TIME;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                //nextState = TurnRight1State;
                if (go_to_reverse == TRUE) {
                    nextState = ReverseIntoRenState;
                } else {
                    nextState = InchForwards3State;
                }
                first_time = TRUE;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;


        case InchForwards3State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, INCH_FORWARDS_3_TIME);
                    forwards();
                    break;

                case ES_TIMEOUT:
                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = StopState_6;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    //                case TAPE_DETECTED:
                    //                    switch (ThisEvent.EventParam) {
                    //                        case RIGHT_TAPE_SENSOR:
                    //                        case FRONT_TAPE_SENSOR:
                    //                        case LEFT_TAPE_SENSOR:
                    //                            if ((get_front_tape_status() == on_tape) && (get_left_tape_status() == on_tape) && (get_right_tape_status() == on_tape)) {
                    //                                ThisEvent.EventType = GO_TO_FIND_LINE;
                    //                                ThisEvent.EventParam = 0;
                    //                                PostTopHSM(ThisEvent);
                    //                                ThisEvent.EventType = ES_NO_EVENT;
                    //                            }
                    //                            break;
                    //                    }
                    //                    break;

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
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = TurnRight1State;
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

        case ReverseIntoRenState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, REVERSE_TIME);
                    //reverse();
                    slow_reverse();
                    break;

                case BUMPER_PRESSED:
                    switch (ThisEvent.EventParam & BACK_BUMPERS) {
                        case BACK_LEFT_BUMPER_PIN:

                            nextState = StopState_5;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            back_left_bumper_counter++;
                            back_right_bumper_counter = 0;
                            break;
                        case BACK_RIGHT_BUMPER_PIN:

                            nextState = StopState_5;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            back_right_bumper_counter++;
                            back_left_bumper_counter = 0;
                            break;

                    }
                    break;

                    //                case REN_BUMPER_PRESSED:
                    //                    switch (ThisEvent.EventParam & ALL_TRUE_REN_BUMPERS) {
                    //                        case REN_LEFT_PIN:
                    //
                    //                            nextState = StopState_5;
                    //                            makeTransition = TRUE;
                    //                            ThisEvent.EventType = ES_NO_EVENT;
                    //                            back_left_bumper_counter++;
                    //                            back_right_bumper_counter = 0;
                    //                            break;
                    //
                    //                        case REN_RIGHT_PIN:
                    //
                    //                            nextState = StopState_5;
                    //                            makeTransition = TRUE;
                    //                            ThisEvent.EventType = ES_NO_EVENT;
                    //                            back_right_bumper_counter++;
                    //                            back_left_bumper_counter = 0;
                    //
                    //                            break;
                    //                    }
                    //                    break;

                case ES_TIMEOUT:
                    //                    // printf("--------------------FSMAlignATM6, ForwardsState\r\n");
                    //                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                    //                        ThisEvent.EventType = GO_TO_FIND_LINE;
                    //                        ThisEvent.EventParam = 0;
                    //                        PostTopHSM(ThisEvent);
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                    }
                    break;


                case TAPE_DETECTED:
                    printf("REACHED TAPE DETECTED ------------------------------ \r\n");
                    printf("Front = %d\r\n", get_front_tape_status());
                    printf("LEft = %d\r\n", get_left_tape_status());
                    printf("Right = %d\r\n", get_right_tape_status());
                    printf("Center = %d\r\n", get_center_tape_status());
                    printf("Back = %d\r\n", get_back_tape_status());
                    printf("REACHED TAPE DETECTED ------------------------------ \r\n");
                    
                    if (is_on_T() == TRUE) {
                        //                        nextState = StopState_5;
                        //                        makeTransition = TRUE;
                        //                        ThisEvent.EventType = ES_NO_EVENT;
                        //                        Twist_Right_Time = SLOW_TWIST_RIGHT_TIME;
                        //                        Twist_Left_Time = SLOW_TWIST_LEFT_TIME;



                        //                        ThisEvent.EventType = REN_ALIGNED;
                        //                        ThisEvent.EventParam = 0;
                        //                        PostTopHSM(ThisEvent);
                        //                        ThisEvent.EventType = ES_NO_EVENT;


                        nextState = StopState_8;
                        makeTransition = TRUE;
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
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, Twist_Left_Time);
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
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, Twist_Right_Time);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        if (back_right_bumper_counter >= ADJUST_TURNING_COUNT) {
                            nextState = StopState_3;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            //  back_right_bumper_counter = 0;

                        } else if (back_left_bumper_counter >= ADJUST_TURNING_COUNT) {
                            nextState = StopState_4;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            //   back_left_bumper_counter = 0;
                        } else {
                            nextState = StopState_2;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
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
                        if (get_beacon_status() == BEACON_FOUND_STATE) {//&& get_ATM6_Counter() >= 3) {
                            nextState = ReverseIntoRenState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            nextState = StopState_9;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                    }
                    break;
            }
            break;


        case StopState_9:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = TankTurnLeftState_1;
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
        case TankTurnLeftState_1:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:

                    //  LED_SetBank(LED_BANK1, 0xf);
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, TANK_TURN_1_TIME);
                    tank_turn_left();
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = ArcLeftState_1;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                    //                case TRACKWIRE_DETECTED:
                    //                    if (ThisEvent.EventParam == BACK_TRACKWIRE) {
                    //                        ThisEvent.EventType = ATM6_ALIGNED;
                    //                        ThisEvent.EventParam = 0;
                    //                        PostTopHSM(ThisEvent);
                    //                        ThisEvent.EventType = ES_NO_EVENT;
                    //                    }
                    //                    break;



                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case ArcLeftState_1:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:


                    ES_Timer_InitTimer(ATTACK_REN_TIMER, ARC_LEFT_1_TIME);
                    arc_steep_left();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        nextState = ArcLeftState_2;
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

        case ArcLeftState_2:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:


                    ES_Timer_InitTimer(ATTACK_REN_TIMER, ARC_LEFT_2_TIME);
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
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
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
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
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


        case StopState_3:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = AdjustLeftState1;
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

        case AdjustLeftState1:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_left();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, ADJUST_LEFT_1_TIME);
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

        case StopState_4:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {

                        nextState = AdjustRightState1;
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

        case AdjustRightState1:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    turn_right();
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, ADJUST_RIGHT_1_TIME);
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

        case StopState_5:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    if (is_on_T() == TRUE) {
                        nextState = StopState_8;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }


                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == ATTACK_REN_TIMER) {
                        //    if (are_bumpers_ren_aligned() == TRUE) {
                        //                            ThisEvent.EventType = REN_ALIGNED;
                        //                            ThisEvent.EventParam = 0;
                        //                            PostTopHSM(ThisEvent);
                        //                            ThisEvent.EventType = ES_NO_EVENT;

                        //                            nextState = BackUpToGetInPositionState;
                        //                            makeTransition = TRUE;
                        //                            ThisEvent.EventType = ES_NO_EVENT;
                        //                        } else {
                        nextState = ForwardsState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        //}

                    }
                    break;

                case ES_TIMERACTIVE:
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;
        case StopState_8:
            switch (ThisEvent.EventType) {

                case ES_ENTRY:
                    ES_Timer_InitTimer(ATTACK_REN_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_TIMEOUT:
                    ThisEvent.EventType = REN_ALIGNED;
                    ThisEvent.EventParam = 0;
                    PostTopHSM(ThisEvent);
                    ThisEvent.EventType = ES_NO_EVENT;
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
        ES_Timer_InitTimer(OH_SHIT_TIMER, OH_SHIT_TIME);
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

