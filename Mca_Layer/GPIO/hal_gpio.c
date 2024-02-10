/* 
 * File:   hal_gpio.c
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:23 PM
 */

#include "hal_gpio.h"

volatile uint8 *tris_reg[] = { &TRISA , &TRISB , &TRISC , &TRISD , &TRISE } ;
volatile uint8 *lat_reg[] =  { &LATA , &LATB , &LATC , &LATD , &LATE } ;
volatile uint8 *port_reg[] = { &PORTA , &PORTB , &PORTC , &PORTD , &PORTE } ;


/**
 * 
 * @param pin_config
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_pin_direction_intialize(pin_config_t *pin_config){
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == pin_config ) ||  (pin_config->port > NUMBER_PORTS_MAX-1)   ||   (pin_config->pin  > NUMBER_PINS_MAX-1 )   )
    {
        ret = STD_NOT_OK ;
    }
    else{
        
        switch(pin_config->direction){
            case  GPIO_OUTPUT :
                CLEAR_BIT(*tris_reg[pin_config->port] , pin_config->pin ) ;
                break;
            
            case GPIO_INPUT  :
                SET_BIT(*tris_reg[pin_config->port] , pin_config->pin ) ;
                break;
              
            default :
                ret = STD_NOT_OK ;
        }
    }
      
    return ret ;
    
}

/**
 * 
 * @param pin_config
 * @param direction
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_pin_get_direction_status(pin_config_t *pin_config ,direction_t  *direction ){
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == pin_config ) ||  (NULL == direction)  ||  (pin_config->port > NUMBER_PORTS_MAX-1)   ||   (pin_config->pin  > NUMBER_PINS_MAX-1 )   )
    {
        ret = STD_NOT_OK ;
    }
    else{
        *direction = READ_BIT(*tris_reg[pin_config->port] , pin_config->pin ) ;
        
    }
        
    return ret ;

}

/**
 * 
 * @param pin_config
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_pin_write_logic(pin_config_t *pin_config , logic_t  logic){
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == pin_config )  ||  (pin_config->port > NUMBER_PORTS_MAX-1)   ||   (pin_config->pin  > NUMBER_PINS_MAX-1 )   )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        switch(logic){
            case  GPIO_LOW :
                CLEAR_BIT(*lat_reg[pin_config->port] , pin_config->pin ) ;
                break;
            
            case GPIO_HIGH  :
                SET_BIT(*lat_reg[pin_config->port] , pin_config->pin ) ;
                break;
              
            default :
                ret = STD_NOT_OK ;
        }
    }
       
    return ret ;
}
/**
 * 
 * @param pin_config
 * @param logic
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_pin_read_logic(pin_config_t *pin_config,logic_t  *logic){
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == pin_config ) ||   (NULL==logic)   ||  (pin_config->port > NUMBER_PORTS_MAX-1)   ||   (pin_config->pin  > NUMBER_PINS_MAX-1 )   )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        *logic = READ_BIT(*port_reg[pin_config->port] , pin_config->pin ) ;
    }
    
    return ret ;

}

/**
 * 
 * @param pin_config
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_pin_toggle_logic(pin_config_t *pin_config){
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == pin_config )   ||  (pin_config->port > NUMBER_PORTS_MAX-1)   ||   (pin_config->pin  > NUMBER_PINS_MAX-1 )   )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        TOGGLE_BIT(*lat_reg[pin_config->port] , pin_config->pin ) ;
    }

    return ret ;

}


/**
 * 
 * @param pin_config
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_pin_intialize(pin_config_t *pin_config ) {
    Std_ReturnType ret = STD_OK ;
    if( ( NULL == pin_config )  ||  (pin_config->port > NUMBER_PORTS_MAX-1)   ||   (pin_config->pin  > NUMBER_PINS_MAX-1 )   )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        ret = gpio_pin_direction_intialize(pin_config);
        ret = gpio_pin_write_logic(pin_config , pin_config->logic );
    }

    return ret ;

}

/**
 * 
 * @param port
 * @param direction
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_port_direction_intialize(port_index_t port , uint8  direction ){
     Std_ReturnType ret = STD_OK ;
    if(   ( port > NUMBER_PORTS_MAX-1)     )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        *tris_reg[port] = direction ;
    }
     
     return ret ;
}


/**
 * 
 * @param port
 * @param direction
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_port_get_direction_status(port_index_t port ,uint8  *direction ){
    Std_ReturnType ret = STD_OK ;
    if(   ( port > NUMBER_PORTS_MAX-1)  ||  (NULL == direction)     )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        *direction = *tris_reg[port] ;
    }
     
     return ret ;
}


/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_port_write_logic(port_index_t port,uint8  logic){
    Std_ReturnType ret = STD_OK ;
    if(   ( port > NUMBER_PORTS_MAX-1)     )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        *lat_reg[port] = logic ;
    }
     
     return ret ;
}


/**
 * 
 * @param port
 * @param logic
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_port_read_logic(port_index_t port,uint8  *logic){
    Std_ReturnType ret = STD_OK ;
    if(   ( port > NUMBER_PORTS_MAX-1)  ||   (NULL == logic)    )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
        *logic = *port_reg[port] ;
    }
    return ret ;
}


/**
 * 
 * @param port
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType gpio_port_toggle_logic(port_index_t port){
    Std_ReturnType ret = STD_OK ;
    if(   ( port > NUMBER_PORTS_MAX-1)   )
    {
        ret = STD_NOT_OK ;
    }
    
    else{
       *lat_reg[port] ^=  0xFF  ;
    }
    return ret ;
}