 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer.h
 *
 * Description: Header file for the configurable Timer1 AVR driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/


#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
/*******************************************************************************
 *                      Types Declaration                                    *
 *******************************************************************************/
typedef enum{
	OVERFLOW,CTC
}Timer1_Mode;
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,XTAL_CLOCK_ON_FALLING,XTAL_CLOCK_ON_RISING
}Timer1_Prescaler;
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
} Timer1_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * description:Function to initialize the Timer driver
 * input :pointer to the configuration structure with type Timer1_ConfigType.
 *
 *
 */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);
/*
 * description: Function to disable the Timer1
 */
void Timer1_deInit(void);
/*
 * description: Function to set the Call Back function address.
 * input:  pointer to Call Back function.
 */
void Timer1_setCallBack(void(*a_ptr)(void));
#endif
