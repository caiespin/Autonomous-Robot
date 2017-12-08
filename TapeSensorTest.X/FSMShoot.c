
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
#include "FSMShoot.h"
#include "IO_Ports.h"
#include "RC_Servo.h"
#include "motors.h"
#include "pwm.h"
#include "bumper_service.h"
#include "FSMShoot.h"
#include "stdio.h"

/*******************************************************************************
 * MODULE #DEFINES                                                             *
 ******************************************************************************/

#define STOP_TIME 100
#define START_MOTOR_HIGH_TIME 1000
//#define START_MOTOR_LOW_TIME 3000
#define START_MOTOR_LOW_TIME 5000
#define LOAD_BALL_TIME 480
#define  RAISE_SHOOTER_TIME 1000
#define STUCK_BALL_TIME 5000

#define SHOOT_POWER_HIGH_PWM 700//800
#define SHOOT_POWER_MED_PWM 420
#define SHOOT_POWER_LOW_PWM 250
static int start_motor_low_time = 5000;

typedef enum {
    InitPSubState,
    Stop,
    StartMotorFast,
    StartMotorSlow,
    // RaiseShooterExtension,
    LoadBall,
    Stuck_Ball_State,



} TemplateSubHSMState_t;

static const char *StateNames[] = {
	"InitPSubState",
	"Stop",
	"StartMotorFast",
	"StartMotorSlow",
	"LoadBall",
	"Stuck_Ball_State",
};



/*******************************************************************************
 * PRIVATE FUNCTION PROTOTYPES                                                 *
 ******************************************************************************/
/* Prototypes for private functions for this machine. They should be functions
   relevant to the behavior of this state machine */
/*******************************************************************************/


/*******************************************************************************
 * PRIVATE MODULE VARIABLES                                                            *
 ******************************************************************************/

/* You will need MyPriority and the state variable; you may need others as well.
 * The type of state variable should match that of enum in header file. */

typedef enum {
    ATM6,
    REN,
} shoot_mode_t;


static TemplateSubHSMState_t CurrentState = InitPSubState; // <- change name to match ENUM
static uint8_t MyPriority;
static shoot_mode_t mode = ATM6;
static int first_time = TRUE;

/*******************************************************************************
 * PUBLIC FUNCTIONS                                                            *
 ******************************************************************************/
void set_atm6_config() {
    // RC_SetPulseTime(SERVO_TILT_PIN, MAXPULSE);
    set_atm6_tilt();
    start_motor_low_time = 2000;
    mode = ATM6;
    first_time = TRUE;

}

void set_ren_config() {
    //  RC_SetPulseTime(SERVO_TILT_PIN, MINPULSE);
    set_ren_tilt();
    start_motor_low_time = 5000;
    mode = REN;
    first_time = TRUE;
}

void shooter_init() {
    // IO_PortsSetPortOutputs(PORTX, SHOOTER_MOTOR_PIN);
    PWM_AddPins(SHOOTER_MOTOR_PIN);
    IO_PortsSetPortOutputs(SHOOT_PORT, SERVO_DELIVER_PIN);
    IO_PortsSetPortOutputs(SHOOT_PORT, RAISE_EXTENSION_MOTOR_PIN);
    IO_PortsClearPortBits(SHOOT_PORT, RAISE_EXTENSION_MOTOR_PIN);

    // IO_PortsClearPortBits(PORTX, SERVO_DELIVER_PIN | SHOOTER_MOTOR_PIN);
    IO_PortsClearPortBits(SHOOT_PORT, SERVO_DELIVER_PIN);
    PWM_AddPins(SERVO_TILT_PIN);
    PWM_SetFrequency(MIN_PWM_FREQ);
    set_atm6_tilt();

    //RC_SetPulseTime(SERVO_TILT_PIN, MAXPULSE);


    // RC_SetPulseTime(SERVO_TILT_PIN, MINPULSE);
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
uint8_t InitFSMShoot(void) {
    ES_Event returnEvent;

    CurrentState = InitPSubState;
    returnEvent = RunFSMShoot(INIT_EVENT);
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
ES_Event RunFSMShoot(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE; // use to flag transition
    TemplateSubHSMState_t nextState; // <- change type to correct enum

    ES_Tattle(); // trace call stack

    switch (CurrentState) {
        case InitPSubState: // If current state is initial Psedudo State
            if (ThisEvent.EventType == ES_INIT)// only respond to ES_Init
            {
                // this is where you would put any actions associated with the
                // transition from the initial pseudo-state into the actual
                // initial state

                // now put the machine into the actual initial state
                nextState = Stop;
                makeTransition = TRUE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case Stop: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(SHOOT_FSM_TIMER, STOP_TIME);
                    stop();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SHOOT_FSM_TIMER) {

                        nextState = StartMotorFast;

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

        case StartMotorFast: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:

                    ES_Timer_InitTimer(SHOOT_FSM_TIMER, START_MOTOR_HIGH_TIME);
                    printf("startMotorFast, first_time --------> %d\r\n", first_time);
                    if (first_time == TRUE) {
                        if (mode == REN) {
                            start_raise_extension();
                        }
                        first_time = FALSE;
                        start_ball_accelerator_fast();
                    } else {
                        nextState = StartMotorSlow;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SHOOT_FSM_TIMER) {

                        nextState = StartMotorSlow;
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
        case StartMotorSlow: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(SHOOT_FSM_TIMER, start_motor_low_time);
                    start_ball_accelerator_slow();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SHOOT_FSM_TIMER) {
                        // nextState = RaiseShooterExtension;
                        stop_raise_extension();
                        nextState = LoadBall;
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

            //        case RaiseShooterExtension: // in the first state, replace this with correct names
            //            switch (ThisEvent.EventType) {
            //                case ES_ENTRY:
            //                    ES_Timer_InitTimer(SHOOT_FSM_TIMER, RAISE_SHOOTER_TIME);
            //                    start_raise_motor();
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_TIMEOUT:
            //                    if (ThisEvent.EventParam == SHOOT_FSM_TIMER) {
            //                        stop_raise_motor();
            //                        nextState = LoadBall;
            //                        makeTransition = TRUE;
            //                        ThisEvent.EventType = ES_NO_EVENT;
            //                    }
            //                    break;
            //
            //                case ES_TIMERACTIVE:
            //                case ES_TIMERSTOPPED:
            //                    ThisEvent.EventType = ES_NO_EVENT;
            //                    break;
            //                case ES_NO_EVENT:
            //                default: // all unhandled events pass the event back up to the next level
            //                    break;
            //            }
            //            break;

        case LoadBall: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    // ES_Timer_InitTimer(SHOOT_FSM_TIMER, LOAD_BALL_TIME);
                    //Start Servo that triggers
                    start_trigger_motor();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case REN_BUMPER_RELEASE:
                    if (ThisEvent.EventParam == REN_CENTER_PIN) {
                        stop_trigger_motor();
                        if (mode == ATM6) {
                            ThisEvent.EventType = SHOT_ATM6;
                            ThisEvent.EventParam = 0;
                            PostTopHSM(ThisEvent);
                            ThisEvent.EventType = ES_NO_EVENT;
                        } else {
                            //                            ThisEvent.EventType = SHOT_REN;
                            //                            ThisEvent.EventParam = 0;
                            //                            PostTopHSM(ThisEvent);
                            //                            ThisEvent.EventType = ES_NO_EVENT;
                            nextState = Stuck_Ball_State;
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

        case Stuck_Ball_State: // in the first state, replace this with correct names
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    ES_Timer_InitTimer(SHOOT_FSM_TIMER, STUCK_BALL_TIME);

                    start_ball_accelerator_med();
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SHOOT_FSM_TIMER) {

                        ThisEvent.EventType = SHOT_REN;
                        ThisEvent.EventParam = 0;
                        PostTopHSM(ThisEvent);
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





        default: // all unhandled states fall into here
            break;
    } // end switch on Current State

    if (makeTransition == TRUE) { // making a state transition, send EXIT and ENTRY
        // recursively call the current state with an exit event
        RunFSMShoot(EXIT_EVENT); // <- rename to your own Run function
        CurrentState = nextState;
        RunFSMShoot(ENTRY_EVENT); // <- rename to your own Run function
    }

    ES_Tail(); // trace call stack end
    return ThisEvent;
}

/*******************************************************************************
 * PRIVATE FUNCTIONS                                                           *
 ******************************************************************************/
void start_ball_accelerator_fast() {
    // IO_PortsSetPortBits(SHOOT_PORT, SHOOTER_MOTOR_PIN);
    PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, SHOOT_POWER_HIGH_PWM);
}

void start_ball_accelerator_med() {
    // IO_PortsSetPortBits(SHOOT_PORT, SHOOTER_MOTOR_PIN);
    PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, SHOOT_POWER_MED_PWM);
}

void start_ball_accelerator_slow() {
    // IO_PortsSetPortBits(SHOOT_PORT, SHOOTER_MOTOR_PIN);
    PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, SHOOT_POWER_LOW_PWM);
}

void start_trigger_motor() {
    IO_PortsSetPortBits(SHOOT_PORT, SERVO_DELIVER_PIN);
}

void start_raise_extension() {
    IO_PortsSetPortBits(SHOOT_PORT, RAISE_EXTENSION_MOTOR_PIN);
}

void stop_raise_extension() {
    IO_PortsClearPortBits(SHOOT_PORT, RAISE_EXTENSION_MOTOR_PIN);
}

void stop_trigger_motor() {
    IO_PortsClearPortBits(SHOOT_PORT, SERVO_DELIVER_PIN);
}

void stop_ball_accelerator() {
    //IO_PortsClearPortBits(SHOOT_PORT, SHOOTER_MOTOR_PIN);
    PWM_SetDutyCycle(SHOOTER_MOTOR_PIN, 0);
}

void set_atm6_tilt() {
    PWM_SetDutyCycle(SERVO_TILT_PIN, TILT_UP_PWM);
}

void set_ren_tilt() {
    PWM_SetDutyCycle(SERVO_TILT_PIN, TILT_DOWN_PWM);
}

