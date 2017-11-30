#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=main.c C:/CMPE118/src/AD.c C:/CMPE118/src/BOARD.c C:/CMPE118/src/LED.c C:/CMPE118/src/RC_Servo.c C:/CMPE118/src/pwm.c C:/CMPE118/src/roach.c C:/CMPE118/src/serial.c C:/CMPE118/src/timers.c IO_Ports.c Stepper.c C:/CMPE118/src/ES_CheckEvents.c C:/CMPE118/src/ES_Framework.c C:/CMPE118/src/ES_KeyboardInput.c C:/CMPE118/src/ES_PostList.c C:/CMPE118/src/ES_Queue.c C:/CMPE118/src/ES_TattleTale.c C:/CMPE118/src/ES_Timers.c tape_detector_fsm_service.c bumper_service.c FSM_Line_Follower.c motors.c TopHSM.c FSM_Find_Line.c FSMCollisionAvoidance.c FSMAlignATM6.c FSM_Mini_Avoid.c FSMShoot.c event_checker.c FSMExitShooter.c FSMAttackRen.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/331920610/AD.o ${OBJECTDIR}/_ext/331920610/BOARD.o ${OBJECTDIR}/_ext/331920610/LED.o ${OBJECTDIR}/_ext/331920610/RC_Servo.o ${OBJECTDIR}/_ext/331920610/pwm.o ${OBJECTDIR}/_ext/331920610/roach.o ${OBJECTDIR}/_ext/331920610/serial.o ${OBJECTDIR}/_ext/331920610/timers.o ${OBJECTDIR}/IO_Ports.o ${OBJECTDIR}/Stepper.o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o ${OBJECTDIR}/_ext/331920610/ES_Framework.o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o ${OBJECTDIR}/_ext/331920610/ES_PostList.o ${OBJECTDIR}/_ext/331920610/ES_Queue.o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o ${OBJECTDIR}/_ext/331920610/ES_Timers.o ${OBJECTDIR}/tape_detector_fsm_service.o ${OBJECTDIR}/bumper_service.o ${OBJECTDIR}/FSM_Line_Follower.o ${OBJECTDIR}/motors.o ${OBJECTDIR}/TopHSM.o ${OBJECTDIR}/FSM_Find_Line.o ${OBJECTDIR}/FSMCollisionAvoidance.o ${OBJECTDIR}/FSMAlignATM6.o ${OBJECTDIR}/FSM_Mini_Avoid.o ${OBJECTDIR}/FSMShoot.o ${OBJECTDIR}/event_checker.o ${OBJECTDIR}/FSMExitShooter.o ${OBJECTDIR}/FSMAttackRen.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/_ext/331920610/AD.o.d ${OBJECTDIR}/_ext/331920610/BOARD.o.d ${OBJECTDIR}/_ext/331920610/LED.o.d ${OBJECTDIR}/_ext/331920610/RC_Servo.o.d ${OBJECTDIR}/_ext/331920610/pwm.o.d ${OBJECTDIR}/_ext/331920610/roach.o.d ${OBJECTDIR}/_ext/331920610/serial.o.d ${OBJECTDIR}/_ext/331920610/timers.o.d ${OBJECTDIR}/IO_Ports.o.d ${OBJECTDIR}/Stepper.o.d ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/331920610/ES_Framework.o.d ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/331920610/ES_PostList.o.d ${OBJECTDIR}/_ext/331920610/ES_Queue.o.d ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d ${OBJECTDIR}/_ext/331920610/ES_Timers.o.d ${OBJECTDIR}/tape_detector_fsm_service.o.d ${OBJECTDIR}/bumper_service.o.d ${OBJECTDIR}/FSM_Line_Follower.o.d ${OBJECTDIR}/motors.o.d ${OBJECTDIR}/TopHSM.o.d ${OBJECTDIR}/FSM_Find_Line.o.d ${OBJECTDIR}/FSMCollisionAvoidance.o.d ${OBJECTDIR}/FSMAlignATM6.o.d ${OBJECTDIR}/FSM_Mini_Avoid.o.d ${OBJECTDIR}/FSMShoot.o.d ${OBJECTDIR}/event_checker.o.d ${OBJECTDIR}/FSMExitShooter.o.d ${OBJECTDIR}/FSMAttackRen.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/_ext/331920610/AD.o ${OBJECTDIR}/_ext/331920610/BOARD.o ${OBJECTDIR}/_ext/331920610/LED.o ${OBJECTDIR}/_ext/331920610/RC_Servo.o ${OBJECTDIR}/_ext/331920610/pwm.o ${OBJECTDIR}/_ext/331920610/roach.o ${OBJECTDIR}/_ext/331920610/serial.o ${OBJECTDIR}/_ext/331920610/timers.o ${OBJECTDIR}/IO_Ports.o ${OBJECTDIR}/Stepper.o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o ${OBJECTDIR}/_ext/331920610/ES_Framework.o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o ${OBJECTDIR}/_ext/331920610/ES_PostList.o ${OBJECTDIR}/_ext/331920610/ES_Queue.o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o ${OBJECTDIR}/_ext/331920610/ES_Timers.o ${OBJECTDIR}/tape_detector_fsm_service.o ${OBJECTDIR}/bumper_service.o ${OBJECTDIR}/FSM_Line_Follower.o ${OBJECTDIR}/motors.o ${OBJECTDIR}/TopHSM.o ${OBJECTDIR}/FSM_Find_Line.o ${OBJECTDIR}/FSMCollisionAvoidance.o ${OBJECTDIR}/FSMAlignATM6.o ${OBJECTDIR}/FSM_Mini_Avoid.o ${OBJECTDIR}/FSMShoot.o ${OBJECTDIR}/event_checker.o ${OBJECTDIR}/FSMExitShooter.o ${OBJECTDIR}/FSMAttackRen.o

# Source Files
SOURCEFILES=main.c C:/CMPE118/src/AD.c C:/CMPE118/src/BOARD.c C:/CMPE118/src/LED.c C:/CMPE118/src/RC_Servo.c C:/CMPE118/src/pwm.c C:/CMPE118/src/roach.c C:/CMPE118/src/serial.c C:/CMPE118/src/timers.c IO_Ports.c Stepper.c C:/CMPE118/src/ES_CheckEvents.c C:/CMPE118/src/ES_Framework.c C:/CMPE118/src/ES_KeyboardInput.c C:/CMPE118/src/ES_PostList.c C:/CMPE118/src/ES_Queue.c C:/CMPE118/src/ES_TattleTale.c C:/CMPE118/src/ES_Timers.c tape_detector_fsm_service.c bumper_service.c FSM_Line_Follower.c motors.c TopHSM.c FSM_Find_Line.c FSMCollisionAvoidance.c FSMAlignATM6.c FSM_Mini_Avoid.c FSMShoot.c event_checker.c FSMExitShooter.c FSMAttackRen.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

# The following macros may be used in the pre and post step lines
Device=PIC32MX320F128H
ProjectDir="C:\Users\igonzalo\Desktop\git\Autonomous-Robot\TapeSensorTest.X"
ConfName=default
ImagePath="dist\default\${IMAGE_TYPE}\TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ImageDir="dist\default\${IMAGE_TYPE}"
ImageName="TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}"
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IsDebug="true"
else
IsDebug="false"
endif

.build-conf:  .pre ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/AD.o: C:/CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/AD.o.d" -o ${OBJECTDIR}/_ext/331920610/AD.o C:/CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/BOARD.o: C:/CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/BOARD.o.d" -o ${OBJECTDIR}/_ext/331920610/BOARD.o C:/CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/LED.o: C:/CMPE118/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/LED.o.d" -o ${OBJECTDIR}/_ext/331920610/LED.o C:/CMPE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/RC_Servo.o: C:/CMPE118/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/331920610/RC_Servo.o C:/CMPE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/pwm.o: C:/CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/pwm.o.d" -o ${OBJECTDIR}/_ext/331920610/pwm.o C:/CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/roach.o: C:/CMPE118/src/roach.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/roach.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/roach.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/roach.o.d" -o ${OBJECTDIR}/_ext/331920610/roach.o C:/CMPE118/src/roach.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/serial.o: C:/CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/serial.o.d" -o ${OBJECTDIR}/_ext/331920610/serial.o C:/CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/timers.o: C:/CMPE118/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/timers.o.d" -o ${OBJECTDIR}/_ext/331920610/timers.o C:/CMPE118/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/IO_Ports.o: IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/IO_Ports.o.d" -o ${OBJECTDIR}/IO_Ports.o IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Stepper.o: Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stepper.o.d 
	@${RM} ${OBJECTDIR}/Stepper.o 
	@${FIXDEPS} "${OBJECTDIR}/Stepper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/Stepper.o.d" -o ${OBJECTDIR}/Stepper.o Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o: C:/CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o C:/CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Framework.o: C:/CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Framework.o C:/CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o: C:/CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o C:/CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_PostList.o: C:/CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_PostList.o C:/CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Queue.o: C:/CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Queue.o C:/CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_TattleTale.o: C:/CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o C:/CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Timers.o: C:/CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Timers.o C:/CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/tape_detector_fsm_service.o: tape_detector_fsm_service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tape_detector_fsm_service.o.d 
	@${RM} ${OBJECTDIR}/tape_detector_fsm_service.o 
	@${FIXDEPS} "${OBJECTDIR}/tape_detector_fsm_service.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/tape_detector_fsm_service.o.d" -o ${OBJECTDIR}/tape_detector_fsm_service.o tape_detector_fsm_service.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/bumper_service.o: bumper_service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bumper_service.o.d 
	@${RM} ${OBJECTDIR}/bumper_service.o 
	@${FIXDEPS} "${OBJECTDIR}/bumper_service.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/bumper_service.o.d" -o ${OBJECTDIR}/bumper_service.o bumper_service.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSM_Line_Follower.o: FSM_Line_Follower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSM_Line_Follower.o.d 
	@${RM} ${OBJECTDIR}/FSM_Line_Follower.o 
	@${FIXDEPS} "${OBJECTDIR}/FSM_Line_Follower.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSM_Line_Follower.o.d" -o ${OBJECTDIR}/FSM_Line_Follower.o FSM_Line_Follower.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/motors.o: motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motors.o.d 
	@${RM} ${OBJECTDIR}/motors.o 
	@${FIXDEPS} "${OBJECTDIR}/motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/motors.o.d" -o ${OBJECTDIR}/motors.o motors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TopHSM.o: TopHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/TopHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/TopHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/TopHSM.o.d" -o ${OBJECTDIR}/TopHSM.o TopHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSM_Find_Line.o: FSM_Find_Line.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSM_Find_Line.o.d 
	@${RM} ${OBJECTDIR}/FSM_Find_Line.o 
	@${FIXDEPS} "${OBJECTDIR}/FSM_Find_Line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSM_Find_Line.o.d" -o ${OBJECTDIR}/FSM_Find_Line.o FSM_Find_Line.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMCollisionAvoidance.o: FSMCollisionAvoidance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMCollisionAvoidance.o.d 
	@${RM} ${OBJECTDIR}/FSMCollisionAvoidance.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMCollisionAvoidance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMCollisionAvoidance.o.d" -o ${OBJECTDIR}/FSMCollisionAvoidance.o FSMCollisionAvoidance.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMAlignATM6.o: FSMAlignATM6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMAlignATM6.o.d 
	@${RM} ${OBJECTDIR}/FSMAlignATM6.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMAlignATM6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMAlignATM6.o.d" -o ${OBJECTDIR}/FSMAlignATM6.o FSMAlignATM6.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSM_Mini_Avoid.o: FSM_Mini_Avoid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSM_Mini_Avoid.o.d 
	@${RM} ${OBJECTDIR}/FSM_Mini_Avoid.o 
	@${FIXDEPS} "${OBJECTDIR}/FSM_Mini_Avoid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSM_Mini_Avoid.o.d" -o ${OBJECTDIR}/FSM_Mini_Avoid.o FSM_Mini_Avoid.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMShoot.o: FSMShoot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMShoot.o.d 
	@${RM} ${OBJECTDIR}/FSMShoot.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMShoot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMShoot.o.d" -o ${OBJECTDIR}/FSMShoot.o FSMShoot.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/event_checker.o: event_checker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/event_checker.o.d 
	@${RM} ${OBJECTDIR}/event_checker.o 
	@${FIXDEPS} "${OBJECTDIR}/event_checker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/event_checker.o.d" -o ${OBJECTDIR}/event_checker.o event_checker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMExitShooter.o: FSMExitShooter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMExitShooter.o.d 
	@${RM} ${OBJECTDIR}/FSMExitShooter.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMExitShooter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMExitShooter.o.d" -o ${OBJECTDIR}/FSMExitShooter.o FSMExitShooter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMAttackRen.o: FSMAttackRen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMAttackRen.o.d 
	@${RM} ${OBJECTDIR}/FSMAttackRen.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMAttackRen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMAttackRen.o.d" -o ${OBJECTDIR}/FSMAttackRen.o FSMAttackRen.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/main.o.d" -o ${OBJECTDIR}/main.o main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/AD.o: C:/CMPE118/src/AD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/AD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/AD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/AD.o.d" -o ${OBJECTDIR}/_ext/331920610/AD.o C:/CMPE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/BOARD.o: C:/CMPE118/src/BOARD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/BOARD.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/BOARD.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/BOARD.o.d" -o ${OBJECTDIR}/_ext/331920610/BOARD.o C:/CMPE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/LED.o: C:/CMPE118/src/LED.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/LED.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/LED.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/LED.o.d" -o ${OBJECTDIR}/_ext/331920610/LED.o C:/CMPE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/RC_Servo.o: C:/CMPE118/src/RC_Servo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/RC_Servo.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/331920610/RC_Servo.o C:/CMPE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/pwm.o: C:/CMPE118/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/pwm.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/pwm.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/pwm.o.d" -o ${OBJECTDIR}/_ext/331920610/pwm.o C:/CMPE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/roach.o: C:/CMPE118/src/roach.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/roach.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/roach.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/roach.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/roach.o.d" -o ${OBJECTDIR}/_ext/331920610/roach.o C:/CMPE118/src/roach.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/serial.o: C:/CMPE118/src/serial.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/serial.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/serial.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/serial.o.d" -o ${OBJECTDIR}/_ext/331920610/serial.o C:/CMPE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/timers.o: C:/CMPE118/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/timers.o.d" -o ${OBJECTDIR}/_ext/331920610/timers.o C:/CMPE118/src/timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/IO_Ports.o: IO_Ports.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/IO_Ports.o 
	@${FIXDEPS} "${OBJECTDIR}/IO_Ports.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/IO_Ports.o.d" -o ${OBJECTDIR}/IO_Ports.o IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/Stepper.o: Stepper.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/Stepper.o.d 
	@${RM} ${OBJECTDIR}/Stepper.o 
	@${FIXDEPS} "${OBJECTDIR}/Stepper.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/Stepper.o.d" -o ${OBJECTDIR}/Stepper.o Stepper.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o: C:/CMPE118/src/ES_CheckEvents.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_CheckEvents.o C:/CMPE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Framework.o: C:/CMPE118/src/ES_Framework.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Framework.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Framework.o C:/CMPE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o: C:/CMPE118/src/ES_KeyboardInput.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_KeyboardInput.o C:/CMPE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_PostList.o: C:/CMPE118/src/ES_PostList.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_PostList.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_PostList.o C:/CMPE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Queue.o: C:/CMPE118/src/ES_Queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Queue.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Queue.o C:/CMPE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_TattleTale.o: C:/CMPE118/src/ES_TattleTale.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_TattleTale.o C:/CMPE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/_ext/331920610/ES_Timers.o: C:/CMPE118/src/ES_Timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/331920610" 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/331920610/ES_Timers.o 
	@${FIXDEPS} "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/_ext/331920610/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/331920610/ES_Timers.o C:/CMPE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/tape_detector_fsm_service.o: tape_detector_fsm_service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/tape_detector_fsm_service.o.d 
	@${RM} ${OBJECTDIR}/tape_detector_fsm_service.o 
	@${FIXDEPS} "${OBJECTDIR}/tape_detector_fsm_service.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/tape_detector_fsm_service.o.d" -o ${OBJECTDIR}/tape_detector_fsm_service.o tape_detector_fsm_service.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/bumper_service.o: bumper_service.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/bumper_service.o.d 
	@${RM} ${OBJECTDIR}/bumper_service.o 
	@${FIXDEPS} "${OBJECTDIR}/bumper_service.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/bumper_service.o.d" -o ${OBJECTDIR}/bumper_service.o bumper_service.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSM_Line_Follower.o: FSM_Line_Follower.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSM_Line_Follower.o.d 
	@${RM} ${OBJECTDIR}/FSM_Line_Follower.o 
	@${FIXDEPS} "${OBJECTDIR}/FSM_Line_Follower.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSM_Line_Follower.o.d" -o ${OBJECTDIR}/FSM_Line_Follower.o FSM_Line_Follower.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/motors.o: motors.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/motors.o.d 
	@${RM} ${OBJECTDIR}/motors.o 
	@${FIXDEPS} "${OBJECTDIR}/motors.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/motors.o.d" -o ${OBJECTDIR}/motors.o motors.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/TopHSM.o: TopHSM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopHSM.o.d 
	@${RM} ${OBJECTDIR}/TopHSM.o 
	@${FIXDEPS} "${OBJECTDIR}/TopHSM.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/TopHSM.o.d" -o ${OBJECTDIR}/TopHSM.o TopHSM.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSM_Find_Line.o: FSM_Find_Line.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSM_Find_Line.o.d 
	@${RM} ${OBJECTDIR}/FSM_Find_Line.o 
	@${FIXDEPS} "${OBJECTDIR}/FSM_Find_Line.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSM_Find_Line.o.d" -o ${OBJECTDIR}/FSM_Find_Line.o FSM_Find_Line.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMCollisionAvoidance.o: FSMCollisionAvoidance.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMCollisionAvoidance.o.d 
	@${RM} ${OBJECTDIR}/FSMCollisionAvoidance.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMCollisionAvoidance.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMCollisionAvoidance.o.d" -o ${OBJECTDIR}/FSMCollisionAvoidance.o FSMCollisionAvoidance.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMAlignATM6.o: FSMAlignATM6.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMAlignATM6.o.d 
	@${RM} ${OBJECTDIR}/FSMAlignATM6.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMAlignATM6.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMAlignATM6.o.d" -o ${OBJECTDIR}/FSMAlignATM6.o FSMAlignATM6.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSM_Mini_Avoid.o: FSM_Mini_Avoid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSM_Mini_Avoid.o.d 
	@${RM} ${OBJECTDIR}/FSM_Mini_Avoid.o 
	@${FIXDEPS} "${OBJECTDIR}/FSM_Mini_Avoid.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSM_Mini_Avoid.o.d" -o ${OBJECTDIR}/FSM_Mini_Avoid.o FSM_Mini_Avoid.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMShoot.o: FSMShoot.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMShoot.o.d 
	@${RM} ${OBJECTDIR}/FSMShoot.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMShoot.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMShoot.o.d" -o ${OBJECTDIR}/FSMShoot.o FSMShoot.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/event_checker.o: event_checker.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/event_checker.o.d 
	@${RM} ${OBJECTDIR}/event_checker.o 
	@${FIXDEPS} "${OBJECTDIR}/event_checker.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/event_checker.o.d" -o ${OBJECTDIR}/event_checker.o event_checker.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMExitShooter.o: FSMExitShooter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMExitShooter.o.d 
	@${RM} ${OBJECTDIR}/FSMExitShooter.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMExitShooter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMExitShooter.o.d" -o ${OBJECTDIR}/FSMExitShooter.o FSMExitShooter.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/FSMAttackRen.o: FSMAttackRen.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FSMAttackRen.o.d 
	@${RM} ${OBJECTDIR}/FSMAttackRen.o 
	@${FIXDEPS} "${OBJECTDIR}/FSMAttackRen.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"C:/CMPE118/include" -I"C:/CMPE118/src" -I"." -MMD -MF "${OBJECTDIR}/FSMAttackRen.o.d" -o ${OBJECTDIR}/FSMAttackRen.o FSMAttackRen.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x0:0x1FC -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC024FF  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=10,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=10,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/TapeSensorTest.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif

.pre:
	@echo "--------------------------------------"
	@echo "User defined pre-build step: [python C:\CMPE118\scripts\Enum_To_String.py]"
	@python C:\CMPE118\scripts\Enum_To_String.py
	@echo "--------------------------------------"

# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
