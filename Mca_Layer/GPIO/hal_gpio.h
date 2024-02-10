/* 
 * File:   hal_gpio.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:41 PM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/* Section :  Includes */

#include "pic18f4620.h"
#include "../mcal_std_types.h"
#include "../device_config.h"

 /* Section : Macros */

#define BIT_MASK   0x01

/* Section : Macros Functions */

#define  HWREG(x)        ( *(volatile uint8 *)(x) )

#define  NUMBER_PORTS_MAX    5
#define  NUMBER_PINS_MAX     8

#define  SET_BIT( REG , BIT_POSITION )         ( REG  |=    (BIT_MASK<<BIT_POSITION) )
#define  CLEAR_BIT( REG , BIT_POSITION )       ( REG  &=   ~(BIT_MASK<<BIT_POSITION) )
#define  TOGGLE_BIT( REG , BIT_POSITION )      ( REG  ^=    (BIT_MASK<<BIT_POSITION) )
#define  READ_BIT( REG , BIT_POSITION )        ( ( REG  >>  BIT_POSITION ) & BIT_MASK)

/* Section : Data type Declaration */

typedef enum {
    GPIO_LOW = 0 ,
    GPIO_HIGH 
}logic_t;

typedef enum {
    GPIO_OUTPUT = 0 ,
    GPIO_INPUT 
}direction_t;

typedef enum {
    GPIO_PIN0 = 0 ,
    GPIO_PIN1 ,
    GPIO_PIN2 ,
    GPIO_PIN3 ,
    GPIO_PIN4 ,
    GPIO_PIN5 ,
    GPIO_PIN6 ,
    GPIO_PIN7 
}pin_index_t;


typedef enum {
    GPIO_PORTA = 0 ,
    GPIO_PORTB ,
    GPIO_PORTC ,
    GPIO_PORTD ,
    GPIO_PORTE
}port_index_t;


typedef struct {
    uint8 port       : 3  ;
    uint8 pin        : 3  ;
    uint8 direction  : 1  ;
    uint8 logic      : 1  ;
}pin_config_t;


/* Section : Functions Declaration */

Std_ReturnType gpio_pin_intialize(pin_config_t *pin_config ) ;
Std_ReturnType gpio_pin_direction_intialize(pin_config_t *pin_config);
Std_ReturnType gpio_pin_get_direction_status(pin_config_t *pin_config ,direction_t  *direction );
Std_ReturnType gpio_pin_write_logic(pin_config_t *pin_config , logic_t  logic);
Std_ReturnType gpio_pin_read_logic(pin_config_t *pin_config,logic_t  *logic);
Std_ReturnType gpio_pin_toggle_logic(pin_config_t *pin_config);


Std_ReturnType gpio_port_direction_intialize(port_index_t port , uint8  direction );
Std_ReturnType gpio_port_get_direction_status(port_index_t port ,uint8  *direction );
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8  logic);
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8  *logic);
Std_ReturnType gpio_port_toggle_logic(port_index_t port);




#endif	/* HAL_GPIO_H */

