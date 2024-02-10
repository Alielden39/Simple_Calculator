/* 
 * File:   ecu_keypad.h
 * Author: Alielden
 *
 * Created on September 26, 2023, 5:17 PM
 */

#ifndef ECU_KEYPAD_H

/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"

/* Section : Macros */

#define NUMBER_OF_ROWS     4
#define NUMBER_OF_COLUMNS  4

/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef struct
{
    pin_config_t rows_pins[NUMBER_OF_ROWS] ;
    pin_config_t columns_pins[NUMBER_OF_COLUMNS];
    
}keypad_t;



/* Section : Functions Declaration */

Std_ReturnType keypad_intialize(keypad_t *keypad);
Std_ReturnType keypad_get_value(keypad_t *keypad , uint8 *value);



#endif	/* ECU_KEYPAD_H */

