/* 
 * File:   ecu_keypad.c
 * Author: Alielden
 *
 * Created on September 26, 2023, 5:17 PM
 */

#include "ecu_keypad.h"


static const uint8 keypad_value[NUMBER_OF_ROWS][NUMBER_OF_COLUMNS]={
    { '7' , '8' , '9' , '/'},
    { '4' , '5' , '6' , '*'},
    { '1' , '2' , '3' , '-'},
    { '#' , '0' , '=' , '+'}
};

/**
 * 
 * @param keypad
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType keypad_intialize(keypad_t *keypad)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == keypad ){
         ret = STD_NOT_OK ;
    }
    else{
        
        for( counter = 0 ; counter < NUMBER_OF_ROWS ; counter++ )
        {
            ret = gpio_pin_intialize(&(keypad->rows_pins[counter]));
        }
        
        for( counter = 0 ; counter < NUMBER_OF_COLUMNS ; counter++ )
        {
            ret = gpio_pin_direction_intialize(&(keypad->columns_pins[counter]));
        }
        
    }
    
    return ret ;
}

/**
 * 
 * @param keypad
 * @param value
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType keypad_get_value(keypad_t *keypad , uint8 *value)
{
    Std_ReturnType ret = STD_OK ;
    uint8 row_counter = 0 , column_counter = 0 , counter = 0 , logic = 0  ;
    if( (NULL == keypad)  ||  (NULL == value) ){
         ret = STD_NOT_OK ;
    }
    else{
     
       
            for( row_counter = 0 ; row_counter < NUMBER_OF_ROWS ; row_counter++ )
            {
                for( counter = 0 ; counter < NUMBER_OF_ROWS ; counter++ )
                {
                    ret = gpio_pin_write_logic( &(keypad->rows_pins[counter]) , GPIO_LOW );
                }
                
                ret = gpio_pin_write_logic( &(keypad->rows_pins[row_counter]) , GPIO_HIGH );
                
                
                for( column_counter = 0 ; column_counter < NUMBER_OF_COLUMNS ; column_counter++ )
                {
                    ret = gpio_pin_read_logic( &(keypad->columns_pins[column_counter]) , &logic ) ;
                    if( GPIO_HIGH ==  logic )
                    {
                        *value = keypad_value[row_counter][column_counter] ;
                    }
                }
                
            }
    }
            
        
       
    
    return ret ;
}
