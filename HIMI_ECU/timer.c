 /******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer.c
 *
 * Description: Source file for the configurable Timer1 AVR driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/
#include "common_macros.h"
#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
static volatile void (*g_callBackPtrT1)(void) = NULL_PTR;
/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
 // in case of using overflow mode
 ISR(TIMER1_OVF_vect){
		if(g_callBackPtrT1!=NULL_PTR)
			(*g_callBackPtrT1)();
 }
 // in case of using CTC mode
 ISR(TIMER1_COMPA_vect){
 	if(g_callBackPtrT1!=NULL_PTR)
 		(*g_callBackPtrT1)();
 }

 /*******************************************************************************
  *                           Function Definition                                  *
  *******************************************************************************/
 void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	 if(Config_Ptr->mode==OVERFLOW){
		 TCCR1A|=(1<<FOC1A);//The FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode.
		 TCCR1B=((TCCR1B) &(0xF8))|((Config_Ptr->prescaler)&(0x07));//to set bits CS0 CS1 CS 2 to set clk
		 TCNT1=Config_Ptr->initial_value;
		 TIMSK|=(1<<TOIE1);//enable interrupt for the overflow mode
		 //TOV1 is automatically cleared when the Timer/Counter1 Overflow interrupt vector is executed
	 }else{
		 TCCR1A|=(1<<FOC1A);//The FOC1A/FOC1B bits are only active when the WGM13:0 bits specifies a non-PWM mode.
		 TCCR1B|=(1<<WGM12);//Choose mode 4 CTC
		 TCCR1B=((TCCR1B) &(0xF8))|((Config_Ptr->prescaler)&(0x07));//to set bits CS0 CS1 CS 2 to set clk
		 TCNT1=Config_Ptr->initial_value;
		 OCR1A=Config_Ptr->compare_value;
		 TIMSK|=(1<<OCIE1A);//enable interrupt for CTC module
		 /*
		 	When this bit is written to one, and the I-flag in the Status Register
		 	is set (interrupts globally enabled), the Timer/Counter1 Output Compare A match interrupt is enable
		 	*/
		 //OCF1A is automatically cleared when the Output Compare Match A Interrupt Vector is executed.
	 }
 }
 void Timer1_setCallBack(void(*a_ptr)(void)){
	 g_callBackPtrT1=a_ptr;
 }
 void Timer1_deInit(void){
		TCCR1A=0;
		TCCR1B= 0; //stop the clock
		TCNT1=0;
		OCR1A=0;
 }
