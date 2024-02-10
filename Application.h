/* 
 * File:   Application.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 7:04 PM
 */

#ifndef APPLICATION_H
#define	APPLICATION_H

/* Section :  Includes */

#include "Ecua_Layer/LED/ecu_led.h"
#include "Ecua_Layer/BUTTON/ecu_button.h"
#include "Ecua_Layer/RELAY/ecu_relay.h"
#include "Ecua_Layer/DC_MOTOR/ecu_dc_motor.h"
#include "Ecua_Layer/7_SEGMENT/ecu_seven_seg.h"
#include "Ecua_Layer/KEYPAD/ecu_keypad.h"
#include "Ecua_Layer/LCD/ecu_lcd.h"
#include <xc.h>


 /* Section : Macros */
#define _XTAL_FREQ 8000000
#define ADD  '+'
#define SUBB '-'
#define MUL  '*'
#define DIV  '/'
#define EQL  '='
#define CLR  '#'

/* Section : Macros Functions */


/* Section : Data type Declaration */


/* Section : Functions Declaration */

void APPLICATION_INTIALIZE(void);
void Get_Number_one(uint32 *number_one);
void Get_Number_Two(uint32 *number_two );
void Get_Func(uint32 *number_one, uint32 *res ,uint32 *op);
void Equal(uint32 *res , uint32 *str);
void clear(uint32 *number_one , uint32 *number_two);
//void clear(void);*/
#endif	/* APPLICATION_H */

