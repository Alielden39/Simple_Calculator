/* 
 * File:   ecu_lcd.c
 * Author: Alielden
 *
 * Created on September 28, 2023, 6:25 PM
 */


#include "ecu_lcd.h"
static Std_ReturnType lcd_send_4bit(lcd_4bit_t *lcd , uint8 command);
static Std_ReturnType lcd_8bit_send_enable(lcd_8bit_t *lcd);
static Std_ReturnType lcd_4bit_send_enable(lcd_4bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(lcd_8bit_t *lcd , uint8 row , uint8 column ); 
static Std_ReturnType lcd_4bit_set_cursor(lcd_4bit_t *lcd , uint8 row , uint8 column ) ;
/**
 * 
 * @param lcd
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_intialize(lcd_4bit_t *lcd)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        gpio_pin_intialize(& (lcd->lcd_rs) ) ;
        gpio_pin_intialize(& (lcd->lcd_en) ) ;
        for( counter = 0 ; counter < 4 ; counter++ )
        {
             gpio_pin_intialize(& (lcd->lcd_data[counter]) ) ;
        } 
    }
    /*********************INTIALIZING*****************************/
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_SET ) ;
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_SET ) ;
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd , _LCD_8BIT_SET ) ;
        /*************************************************************/
        ret = lcd_4bit_send_command(lcd , _LCD_CLEAR );
        ret = lcd_4bit_send_command(lcd , _LCD_CURSOR_HOME );
        ret = lcd_4bit_send_command(lcd , _LCD_ENTRY_MODE_INCREMENT );
        ret = lcd_4bit_send_command(lcd , _LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF );
        ret = lcd_4bit_send_command(lcd , _LCD_4BIT_SET ) ; 
        ret = lcd_4bit_send_command(lcd , _LCD_CURSOR_HOME );
    
    return ret ;
    
}

/**
 * 
 * @param lcd
 * @param command
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_send_command(lcd_4bit_t *lcd , uint8 command)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW ) ;
        ret = lcd_send_4bit(lcd , command >> 4 ) ;
        ret = lcd_4bit_send_enable(lcd) ;
        ret = lcd_send_4bit(lcd , command  ) ;
        ret = lcd_4bit_send_enable(lcd) ; 
    }
    
    return ret ;
}




/**
 * 
 * @param lcd
 * @param data
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_send_char_data(lcd_4bit_t *lcd , uint8 data)
{
     Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{ 
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH ) ;
        ret = lcd_send_4bit(lcd , data >> 4 ) ;
        ret = lcd_4bit_send_enable(lcd) ;
        ret = lcd_send_4bit(lcd , data  ) ;
        ret = lcd_4bit_send_enable(lcd) ; 
    }
    
    return ret ;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_send_char_data_pos(lcd_4bit_t *lcd ,uint8 row , uint8 column , uint8 data)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd ,row,column ) ;
        ret = lcd_4bit_send_char_data(lcd , data ) ;
        
    } 
    return ret ;
}

/**
 * 
 * @param lcd
 * @param str
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_send_string_data(lcd_4bit_t *lcd , uint8 *str)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        while( *str !=  '\0' )
        {
            ret = lcd_4bit_send_char_data(lcd , *str  );
            str++ ;
        }
        
        
    }
    return ret ;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_send_string_data_pos(lcd_4bit_t *lcd ,uint8 row , uint8 column , uint8 *str)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = lcd_4bit_set_cursor(lcd ,row,column ) ;
        ret = lcd_4bit_send_string_data(lcd , str ) ;
 
    }
    return ret ;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_4bit_send_custom_char_data_pos(lcd_4bit_t *lcd ,uint8 row , uint8 column , uint8 chr[] , uint8 mem_pos)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = lcd_4bit_send_command( lcd , (_LCD_CGRAM_START_ADDRESS) + (8 * mem_pos ) ) ;
        
        for( counter = 0 ; counter < 8 ; counter++ )
        {
            ret = lcd_4bit_send_char_data( lcd , chr[counter] );
        }
        ret = lcd_4bit_send_char_data_pos(lcd , row , column , mem_pos) ;
        
    } 
    return ret ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @param lcd
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_8bit_intialize(lcd_8bit_t *lcd)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        gpio_pin_intialize(& (lcd->lcd_rs) ) ;
        gpio_pin_intialize(& (lcd->lcd_en) ) ;
        for( counter = 0 ; counter < 8 ; counter++ )
        {
             gpio_pin_intialize(& (lcd->lcd_data[counter]) ) ;
        } 
        /*********************INTIALIZING*****************************/
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_SET ) ;
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_SET ) ;
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd , _LCD_8BIT_SET ) ;
        /*************************************************************/
        ret = lcd_8bit_send_command(lcd , _LCD_CLEAR );
        ret = lcd_8bit_send_command(lcd , _LCD_CURSOR_HOME );
        ret = lcd_8bit_send_command(lcd , _LCD_ENTRY_MODE_INCREMENT );
        ret = lcd_8bit_send_command(lcd , _LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF );
 
    }
    
    return ret ;
    
    
}

/**
 * 
 * @param lcd
 * @param command
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_8bit_send_command(lcd_8bit_t *lcd , uint8 command)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_LOW ) ;
        
        for( counter = 0 ; counter < 8 ; counter++ )
        {
            ret = gpio_pin_write_logic( &(lcd->lcd_data[counter]) , ( command >> counter ) & (uint8)0x01  );
        }
        ret = lcd_8bit_send_enable(lcd) ;
        
    }
    
    return ret ;
}

/**
 * 
 * @param lcd
 * @param data
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_8bit_send_char_data(lcd_8bit_t *lcd , uint8 data)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_write_logic(&(lcd->lcd_rs) , GPIO_HIGH ) ;
        
        for( counter = 0 ; counter < 8 ; counter++ )
        {
            ret = gpio_pin_write_logic( &(lcd->lcd_data[counter]) , ( data >> counter ) & (uint8)0x01  );
        }
        ret = lcd_8bit_send_enable(lcd) ;
        
    }
    return ret ;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param data
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_8bit_send_char_data_pos(lcd_8bit_t *lcd ,uint8 row , uint8 column , uint8 data)
{
   Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd ,row,column ) ;
        ret = lcd_8bit_send_char_data(lcd , data ) ;
        
    } 
    return ret ;
}

/**
 * 
 * @param lcd
 * @param str
 * @return 
 */
Std_ReturnType lcd_8bit_send_string_data(lcd_8bit_t *lcd , uint8 *str)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        while( *str !=  '\0' )
        {
            ret = lcd_8bit_send_char_data(lcd , *str  );
            str++ ;
        }
        
        
    }
    return ret ;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param str
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_8bit_send_string_data_pos(lcd_8bit_t *lcd ,uint8 row , uint8 column , uint8 *str)
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = lcd_8bit_set_cursor(lcd ,row,column ) ;
        ret = lcd_8bit_send_string_data(lcd , str ) ;
 
    }
    return ret ;
}

/**
 * 
 * @param lcd
 * @param row
 * @param column
 * @param chr
 * @param mem_pos
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType lcd_8bit_send_custom_char_data_pos(lcd_8bit_t *lcd ,uint8 row , uint8 column , uint8 chr[] , uint8 mem_pos)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = lcd_8bit_send_command( lcd , (_LCD_CGRAM_START_ADDRESS) + (8 * mem_pos ) ) ;
        
        for( counter = 0 ; counter < 8 ; counter++ )
        {
            ret = lcd_8bit_send_char_data( lcd , chr[counter] );
        }
        ret = lcd_8bit_send_char_data_pos(lcd , row , column , mem_pos) ;
        
    } 
    return ret ;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 
 * @param lcd
 * @param command
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
static Std_ReturnType lcd_send_4bit(lcd_4bit_t *lcd , uint8 command)
{
    Std_ReturnType ret = STD_OK ;
    uint8 counter = 0 ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        for( counter = 0 ; counter < 4 ; counter++ )
        {
            ret = gpio_pin_write_logic( &(lcd->lcd_data[counter]) , ( command >> counter ) & (uint8)0x01  );
        }
    }
    
    return ret ;
}



/**
 * 
 * @param lcd
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
static Std_ReturnType lcd_8bit_send_enable(lcd_8bit_t *lcd) 
{
   Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_write_logic( &(lcd->lcd_en) , GPIO_HIGH ) ;
        __delay_us(5);
         ret = gpio_pin_write_logic( &(lcd->lcd_en) , GPIO_LOW ) ;
    }
    
    return ret ; 
}


/**
 * 
 * @param lcd
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
  static Std_ReturnType lcd_4bit_send_enable(lcd_4bit_t *lcd) 
{
   Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        ret = gpio_pin_write_logic( &(lcd->lcd_en) , GPIO_HIGH ) ;
        __delay_us(5);
         ret = gpio_pin_write_logic( &(lcd->lcd_en) , GPIO_LOW ) ;
    }
    
    return ret ; 
}

/**
 * 
 * @param lcd
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
static Std_ReturnType lcd_8bit_set_cursor(lcd_8bit_t *lcd , uint8 row , uint8 column ) 
{
   Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        column-- ;
        switch(row)
        {
            case 1 :
                ret = lcd_8bit_send_command(lcd , 0x80 + column ) ;
                break;
            case 2 :
                ret = lcd_8bit_send_command(lcd , 0xC0 + column ) ;
                break;
            case 3 :
                ret = lcd_8bit_send_command(lcd , 0x94 + column ) ;
                break;
            case 4 :
                ret = lcd_8bit_send_command(lcd , 0xD4 + column ) ;
                break;
            default :
                ret = STD_NOT_OK ;
                
                
        }
                
    }
    
    return ret ; 
}


/**
 * 
 * @param lcd
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
static Std_ReturnType lcd_4bit_set_cursor(lcd_4bit_t *lcd , uint8 row , uint8 column ) 
{
   Std_ReturnType ret = STD_OK ;
    if( NULL == lcd ){
         ret = STD_NOT_OK ;
    }
    else{
        column-- ;
        switch(row)
        {
            case 1 :
                ret = lcd_4bit_send_command(lcd , 0x80 + column ) ;
                break;
            case 2 :
                ret = lcd_4bit_send_command(lcd , 0xC0 + column ) ;
                break;
            case 3 :
                ret = lcd_4bit_send_command(lcd , 0x94 + column ) ;
                break;
            case 4 :
                ret = lcd_4bit_send_command(lcd , 0xD4 + column ) ;
                break;
        }
                
    }
    
    return ret ; 
}



/**
 * 
 * @param value
 * @param str
 * @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType convert_byte_to_string( uint8 value , uint8 *str )
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == str ){
         ret = STD_NOT_OK ;
    }
    else{
            memset(str , '\0' , 4 );
            sprintf(str , "%i" , value) ;
    }
    
    return ret ; 
}

/**
 * 
 * @param value
 * @param str
* @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType convert_short_to_string( uint16 value , uint8 *str )
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == str ){
         ret = STD_NOT_OK ;
    }
    else{
            memset(str , '\0' , 6 );
            sprintf(str , "%i" , value) ;
    }
    
    return ret ; 
}


/**
 * 
 * @param value
 * @param str
* @return status of function
 *        STD_NOT_OK : the function has issue .
 *        STD_OK     : the function is done successfully .      
 */
Std_ReturnType convert_int_to_string( uint32 value , uint8 *str )
{
    Std_ReturnType ret = STD_OK ;
    if( NULL == str ){
         ret = STD_NOT_OK ;
    }
    else{
            memset(str , '\0' , 11 );
            sprintf(str , "%i" , value) ;
    }
    
    return ret ; 
}