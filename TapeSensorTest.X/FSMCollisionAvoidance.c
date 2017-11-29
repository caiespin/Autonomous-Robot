
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
#include "FSMCollisionAvoidance.h"
#include "bumper_service.h"
#include "motors.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/
#define EXTRA_WEIGHT 300

#define STOP_TIME 100
#define REVERSE_TIME (300 + EXTRA_WEIGHT)
//#define TURN_TIME 840
#define TankTurnRight1_TIME (1000 + EXTRA_WEIGHT)

#define TankTurnLeft3_TIME (1400 + EXTRA_WEIGHT)
#define TankTurnLeft4_TIME (1100 + EXTRA_WEIGHT)

//#define TURN2_TIME 940
#define RAM_TIME (500 + EXTRA_WEIGHT)
#define TankTurnRight2_TIME (1300 + EXTRA_WEIGHT)

#define TankTurnLeft1_TIME (1100 + EXTRA_WEIGHT)
#define TankTurnLeft2_TIME (1100 + EXTRA_WEIGHT)
#define FORWARDS_1_TIME (1200 + EXTRA_WEIGHT)
#define FORWARDS_2_TIME (1600 + EXTRA_WEIGHT)
#define FORWARDS_3_TIME (1100 + EXTRA_WEIGHT)
#define INCH_TIME ( 100)
#define REVERSE_2_TIME (800 + EXTRA_WEIGHT)
#define MINI_FORWARDS_TIME (300 + EXTRA_WEIGHT)

typedef enum {
    InitPSubState,
    RamIntoItState,
    Stop1State,
    Reverse1State,
    Stop2State,
    TankTurnRight1State,
    Stop3State,
    Forwards1State,
    Stop4State,
    TankTurnLeft1State,
    Stop5State,
    Forwards2State,
    Stop6State,
    //  TankTurnRight2State,
    TankTurnLeft2State,
    FoundTapeState,
    InchForwardsState,
    Stop7State,
    TankTurnRight2State,
    Stop8State,
    Reverse2State,
    Stop9State,
    MiniForwardState,
    Stop10State,
    TankTurnLeft3State,
    Stop11State,
    Forwards3State,
    Stop12State,
    TankTurnLeft4State,

} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"RamIntoItState",
	"Stop1State",
	"Reverse1State",
	"Stop2State",
	"TankTurnRight1State",
	"Stop3State",
	"Forwards1State",
	"Stop4State",
	"TankTurnLeft1State",
	"Stop5State",
	"Forwards2State",
	"Stop6State",
	"TankTurnLeft2State",
	"FoundTapeState",
	"InchForwardsState",
	"Stop7State",
	"TankTurnRight2State",
	"Stop8State",
	"Reverse2State",
	"Stop9State",
	"MiniForwardState",
	"Stop10State",
	"TankTurnLeft3State",
	"Stop11State",
	"Forwards3State",
	"Stop12State",
	"TankTurnLeft4State",
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
uint8_t InitFSMCollisionAvoidance(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFSMCollisionAvoidance(INIT_EVENT);
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
ES_Event RunFSMCollisionAvoidance(ES_Event ThisEvent) {
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
                nextState = RamIntoItState;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;
        case RamIntoItState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, RAM_TIME);
                    forwards();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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
        case Stop1State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Reverse1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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
        case Reverse1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, REVERSE_TIME);
                    reverse();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop2State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = TankTurnRight1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case TankTurnRight1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, TankTurnRight1_TIME);
                    tank_turn_right();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop3State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop3State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Forwards1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Forwards1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, FORWARDS_1_TIME);
                    forwards();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop4State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop4State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = TankTurnLeft1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case TankTurnLeft1State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, TankTurnLeft1_TIME);
                    tank_turn_left();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop5State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop5State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Forwards2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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


        case Forwards2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, FORWARDS_2_TIME);
                    forwards();
                    break;

                case BUMPER_PRESSED:
                    bumpers = ThisEvent.EventParam & (FRONT_BUMPERS);
                    if ((bumpers == FRONT_LEFT_BUMPER_PIN) || (bumpers == FRONT_RIGHT_BUMPER_PIN) || (bumpers == FRONT_BUMPERS)) {
                        nextState = Stop1State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case FRONT_TAPE_SENSOR:
                            nextState = FoundTapeState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop6State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop6State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = TankTurnLeft2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case TankTurnLeft2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, TankTurnLeft2_TIME);
                    tank_turn_left();
                    break;
                case ES_TIMEOUT:

                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        ThisEvent.EventType = OBSTACLE_AVOIDED;
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
        case FoundTapeState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    forwards();
                    break;
                case TAPE_DETECTED:
                    switch (ThisEvent.EventParam) {
                        case CENTER_TAPE_SENSOR:
                            nextState = InchForwardsState;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    case BUMPER_PRESSED:
                    bumpers = (ThisEvent.EventParam & (FRONT_BUMPERS));
                    if ((bumpers == FRONT_LEFT_BUMPER_PIN) || (bumpers == FRONT_RIGHT_BUMPER_PIN) || (bumpers == FRONT_BUMPERS)) {
                        //NEED to MODIFY THIS ADD FRONT BUMPER , or LEFT OR RIGHT
                        nextState =Stop1State ;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;


                case ES_NO_EVENT:
                default: // all unhandled events pass the event back up to the next level
                    break;
            }
            break;

        case InchForwardsState: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    forwards();
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, INCH_TIME);
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop7State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop7State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = TankTurnRight2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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


        case TankTurnRight2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, TankTurnRight2_TIME);
                    tank_turn_right();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop8State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop8State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Reverse2State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Reverse2State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, REVERSE_2_TIME);
                    reverse();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop9State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop9State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = MiniForwardState;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case MiniForwardState:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, MINI_FORWARDS_TIME);
                    forwards();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop10State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop10State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = TankTurnLeft3State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case TankTurnLeft3State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, TankTurnLeft3_TIME);
                    tank_turn_left();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop11State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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


        case Stop11State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Forwards3State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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













        case Forwards3State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, FORWARDS_3_TIME);
                    forwards();
                    break;


                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = Stop12State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case Stop12State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, STOP_TIME);
                    stop();
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        nextState = TankTurnLeft4State;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
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

        case TankTurnLeft4State:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(COLLISION_AVOIDANCE_TIMER, TankTurnLeft4_TIME);
                    tank_turn_left();
                    break;
                case ES_TIMEOUT:

                    if (ThisEvent.EventParam == COLLISION_AVOIDANCE_TIMER) {
                        ThisEvent.EventType = OBSTACLE_AVOIDED;
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
        RunFSMCollisionAvoidance(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFSMCollisionAvoidance(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}


/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/

