 /******************************************************************************
 *
 * Module: Dc motor
 *
 * File Name: dc_motor.c
 *
 * Description: source file for the dc_motor driver
 *
 * Author: Ahmed Magdy
 *
 *******************************************************************************/
#include "gpio.h"
#include "dc_motor.h"
#include "common_macros.h"
/*******************************************************************************
 *                      Functions implementation                                   *
 *******************************************************************************/
/*
 * description
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 *  Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void){
	//set up direction of motor pins
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN_1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_PORT_ID, MOTOR_PIN_2_ID, PIN_OUTPUT);
	//make intial state of motor as stop by writing 0 on both pins
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
}
/*
 * description
 * The function responsible for rotate the DC Motor CW/ or A_CW or stop the motor based
 * on the state input state value.
 * inputs:
 * state: The required DC Motor state, it should be CW or A-CW or stop.
 */
void DcMotor_Rotate(DcMotor_State state){
	if (state == CW){
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_HIGH);
	}
	else if (state==A_CW) {
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_HIGH);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
	}
	else if(state==STOP){
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
	}
	else{
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_1_ID, LOGIC_LOW);
		GPIO_writePin(MOTOR_PORT_ID, MOTOR_PIN_2_ID, LOGIC_LOW);
	}
}
