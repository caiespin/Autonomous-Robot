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
#include "TopHSM.h"
//#include "TemplateSubHSM.h" //#include all sub state machines called
#include "FSM_Line_Follower.h"
#include "FSM_Find_Line.h"
#include "FSMCollisionAvoidance.h"
//#include "LED.h"
#include "FSMAlignATM6.h"
#include "FSMShoot.h"
#include "FSMExitShooter.h"
#include "FSM_Mini_Avoid.h"

#include "FSMAttackRen.h"
#include "FSMStartWar.h"
#include "motors.h"
#include "tape_detector_fsm_service.h"
#include "bumper_service.h"
#include "stdio.h"
/*******************************************************************************
 * PRIVATE #DEFINES                                                            *
 ******************************************************************************/
//Include any defines you need to do
#define BOOT_TIME 100
#define UNSTUCK_TIME 600
#define RESET_BUMPER_COUNTER_TIME 7000
/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
//#define HSM_TIME 100

typedef enum {
    InitPState,
    FindLineState,
    LineFollowerState,
    CollisionAvoidanceState,
    AlignATM6,
    Shoot,
    Exit_Shoot,
    MiniAvoidState,
    ATTACK_REN,
    Start_War_State,
    Debug_Stop_State,
    Unstuck_State,

} TemplateHSMState_t;

static const char *StateNames[] = {
	"InitPState",
	"FindLineState",
	"LineFollowerState",
	"CollisionAvoidanceState",
	"AlignATM6",
	"Shoot",
	"Exit_Shoot",
	"MiniAvoidState",
	"ATTACK_REN",
	"Start_War_State",
	"Debug_Stop_State",
	"Unstuck_State",
};



static int Last_Top_State = FindLineState;

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

static TemplateHSMState_t CurrentState = InitPState; // <- change enum name to match ENUM
static uint8_t MyPriority;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/
int get_last_top_state() {
    return Last_Top_State;
}

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
uint8_t InitTopHSM(uint8_t Priority) {
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
 * @Function PostTemplateHSM(ES_Event ThisEvent)
 * @param ThisEvent - the event (type and param) to be posted to queue
 * @return TRUE or FALSE
 * @brief This function is a wrapper to the queue posting function, and its name
 *        will be used inside ES_Configure to point to which queue events should
 *        be posted to. Remember to rename to something appropriate.
 *        Returns TRUE if successful, FALSE otherwise
 * @author J. Edward Carryer, 2011.10.23 19:25 */
uint8_t PostTopHSM(ES_Event ThisEvent) {
    return ES_PostToService(MyPriority, ThisEvent);
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
ES_Event RunTopHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateHSMState_t nextState; // <- change type to correct enum
    int bumpers;
    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPState: // If current state is initial Pseudo State
            switch (ThisEvent.EventType) {
                case ES_INIT:// only respond to ES_Init

                    // this is where you would put any actions associated with the
                    // transition from the initial pseudo-state into the actual
                    // initial state
                    // Initialize all sub-state machines

                    //                InitFSMLineFollower(MyPriority);
                    //                InitFSMFindLine();
                    //                InitFSMCollisionAvoidance();
                    //                InitFSMAlignAtm6();
                    //                InitFSMShoot();

                    // now put the machine into the actual initial state

                    ES_Timer_InitTimer(TOP_HSM_TIMER, BOOT_TIME);

                    //  set_atm6_config();

                    break;
                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case TOP_HSM_TIMER:

                            nextState = Start_War_State;
                           // nextState = FindLineState;
                            // nextState = Debug_Stop_State;
                           //  nextState = ATTACK_REN;
                            //                            nextState=Shoot;
                            //                            set_ren_config();

                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;


                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;
        case Debug_Stop_State:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    stop();

                    nextState = Debug_Stop_State;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                default:
                    if (is_on_T() == TRUE) {
                        printf("On T!!!\r\n");
                    }
                    break;
            }

            break;
        case Start_War_State:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMStartWar();
                    break;
            }
            ThisEvent = RunFSMStartWar(ThisEvent);
            switch (ThisEvent.EventType) {
                case GO_TO_FIND_LINE:

                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;


                case ES_NO_EVENT:
                default:
                    break;
            }
            break;


        case FindLineState:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMFindLine();
                    break;
            }
            ThisEvent = RunFSMFindLine(ThisEvent);
            switch (ThisEvent.EventType) {
                case LINE_FOUND:
                    //   LED_SetBank(LED_BANK3, 0xf);
                    nextState = LineFollowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (FRONT_BUMPERS));
                    if ((bumpers == FRONT_LEFT_BUMPER_PIN) || (bumpers == FRONT_RIGHT_BUMPER_PIN) || (bumpers == FRONT_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState = MiniAvoidState;

                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case OH_SHIT_TIMER:
                            nextState = Unstuck_State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;

                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;




                case ES_NO_EVENT:
                default:
                    break;
            }
            break;


        case LineFollowerState: // in the first state, replace this with correct names
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(RESET_BUMPER_COUNTER_TIMER, RESET_BUMPER_COUNTER_TIME);
                    InitFSMLineFollower(MyPriority);
                    break;
            }
            ThisEvent = RunFSMLineFollower(ThisEvent);
            switch (ThisEvent.EventType) {

                case GO_TO_FIND_LINE:

                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case TRACKWIRE_DETECTED:
                    //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                    nextState = AlignATM6;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (FRONT_BUMPERS));
                    if ((bumpers == FRONT_LEFT_BUMPER_PIN) || (bumpers == FRONT_RIGHT_BUMPER_PIN) || (bumpers == FRONT_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState = MiniAvoidState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case OH_SHIT_TIMER:
                            nextState = Unstuck_State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;
                        case RESET_BUMPER_COUNTER_TIMER:
                            reset_bumper_counter();
                            break;

                    }
                    break;

                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_EXIT:
                    ES_Timer_StopTimer(RESET_BUMPER_COUNTER_TIMER);
                    break;
                case ES_NO_EVENT:
                default:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case CollisionAvoidanceState: // in the first state, replace this with correct names
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMCollisionAvoidance();
                    break;
                case TRACKWIRE_DETECTED:
                    //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                    nextState = AlignATM6;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            ThisEvent = RunFSMCollisionAvoidance(ThisEvent);
            switch (ThisEvent.EventType) {
                case OBSTACLE_AVOIDED:

                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case T_FOUND:
                    nextState = ATTACK_REN;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case GO_TO_FIND_LINE:
                    printf("GO_TO_FIND_LINE\r\n");
                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case GO_TO_ON_LINE:
                    printf("GO_TO_ON_LINE\r\n");
                    nextState = LineFollowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_TIMEOUT:
                    switch (ThisEvent.EventParam) {
                        case OH_SHIT_TIMER:
                            nextState = Unstuck_State;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                            break;

                    }
                    break;

                case ES_TIMERACTIVE:
                    // printf("enter on_ES_TIMERACTIVE\r\n");
                case ES_TIMERSTOPPED:
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }

            break;
        case AlignATM6: // in the first state, replace this with correct names
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMAlignAtm6();
                    break;


            }
            ThisEvent = RunFSMAlignAtm6(ThisEvent);
            switch (ThisEvent.EventType) {

                case ATM6_ALIGNED:
                    set_atm6_config();
                    nextState = Shoot;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }


            break;

        case Shoot:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMShoot();
                    break;
            }
            ThisEvent = RunFSMShoot(ThisEvent);
            switch (ThisEvent.EventType) {

                case SHOT_ATM6:
                    nextState = Exit_Shoot;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case SHOT_REN:
                    nextState = Shoot;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case Exit_Shoot:
            // run sub-state machine for this state
            //NOTE: the SubState Machine runs and responds to events before anything in the this
            //state machine does
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMExitShooter();
                    break;
            }
            ThisEvent = RunFSMExitShooter(ThisEvent);
            switch (ThisEvent.EventType) {
                case GO_TO_ON_LINE:
                    nextState = LineFollowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }
            break;

        case MiniAvoidState:

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMMiniAvoid();
                    break;
            }
            ThisEvent = RunFSMMiniAvoid(ThisEvent);
            switch (ThisEvent.EventType) {
                case OBSTACLE_AVOIDED:
                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    //                case T_FOUND:
                    //                    nextState = Debug_Stop_State;
                    //                    //nextState= ATTACK_REN;
                    //                    makeTransition = TRUE;
                    //                    ThisEvent.EventType = ES_NO_EVENT;
                    //                    break;

                case GO_TO_ALIGN_REN:
                    nextState = Debug_Stop_State;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case GO_TO_ATTACK_REN:
                    nextState = ATTACK_REN;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case GO_TO_FIND_LINE:
                    //   LED_SetBank(LED_BANK3, 0xf);
                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case ES_NO_EVENT:
                default:
                    break;
            }

            break;
        case ATTACK_REN:

            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    InitFSMAttackRen();
                    break;
            }
            ThisEvent = RunFSMAttackRen(ThisEvent);
            switch (ThisEvent.EventType) {
                case REN_ALIGNED:
                    set_ren_config();
                    nextState = Shoot;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case GO_TO_FIND_LINE:
                    //   LED_SetBank(LED_BANK3, 0xf);
                    nextState = FindLineState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case GO_TO_ON_LINE:
                    printf("GO_TO_ON_LINE\r\n");
                    nextState = LineFollowerState;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_NO_EVENT:
                default:
                    break;
            }

            break;

        case Unstuck_State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    if (Last_Top_State == ATTACK_REN) {
                        forwards();
                    } else if (are_front_bumpers_pressed() == TRUE) {
                        reverse();
                        printf("Unstuck_state, front bumpers pressed reach if ---------->\r\n");
                    } else {
                        printf("Unstuck_state, reach else ---------->\r\n");
                        turn_back_left();
                    }

                    ES_Timer_InitTimer(UNSTUCK_TIMER, UNSTUCK_TIME);
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == UNSTUCK_TIMER) {
                        if (Last_Top_State == ATTACK_REN) {
                            set_ATTACK_REN_to_reverse();
                            nextState = ATTACK_REN;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            nextState = FindLineState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                    }
                    break;

                case ES_TIMERACTIVE:
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
        RunTopHSM(EXIT_EVENT); // <- rename to your own Run function
        adjust_pwm();
        Last_Top_State = CurrentState;
        CurrentState = nextState;
        RunTopHSM(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
