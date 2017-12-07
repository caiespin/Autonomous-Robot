/* 
 * File:   motors.h
 * Author: igonzalo
 *
 * Created on November 24, 2017, 5:35 PM
 */

#ifndef MOTORS_H
#define	MOTORS_H

void motors_init();
void turn_right();
void turn_left();
void tank_turn_right();
void tank_turn_left();

void tank_turn_left();

void turn_back_right();
void forwards();
void reverse();
void slow_reverse();
void stop();
void adjust_pwm();
void  arc_left();
void arc_left_long();
void slow_forwards();
void mid_speed_forwards();


#endif	/* MOTORS_H */

