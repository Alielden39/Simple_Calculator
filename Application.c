/* 
 * File:   Application.c
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:23 PM
 */

#include "Application.h"

keypad_t keypad1 =
{
  .rows_pins[0].port      = GPIO_PORTC  ,
  .rows_pins[0].pin       = GPIO_PIN0   ,
  .rows_pins[0].logic     = GPIO_LOW    ,
  .rows_pins[0].direction = GPIO_OUTPUT ,
  .rows_pins[1].port      = GPIO_PORTC  ,
  .rows_pins[1].pin       = GPIO_PIN1   ,
  .rows_pins[1].logic     = GPIO_LOW    ,
  .rows_pins[1].direction = GPIO_OUTPUT ,
  .rows_pins[2].port      = GPIO_PORTC  ,
  .rows_pins[2].pin       = GPIO_PIN2   ,
  .rows_pins[2].logic     = GPIO_LOW    ,
  .rows_pins[2].direction = GPIO_OUTPUT ,
  .rows_pins[3].port      = GPIO_PORTC  ,
  .rows_pins[3].pin       = GPIO_PIN3   ,
  .rows_pins[3].logic     = GPIO_LOW    ,
  .rows_pins[3].direction = GPIO_OUTPUT ,
  
  .columns_pins[0].port      = GPIO_PORTC  ,
  .columns_pins[0].pin       = GPIO_PIN4   ,
  .columns_pins[0].logic     = GPIO_LOW    ,
  .columns_pins[0].direction = GPIO_INPUT ,
  .columns_pins[1].port      = GPIO_PORTC  ,
  .columns_pins[1].pin       = GPIO_PIN5   ,
  .columns_pins[1].logic     = GPIO_LOW    ,
  .columns_pins[1].direction = GPIO_INPUT ,
  .columns_pins[2].port      = GPIO_PORTC  ,
  .columns_pins[2].pin       = GPIO_PIN6   ,
  .columns_pins[2].logic     = GPIO_LOW    ,
  .columns_pins[2].direction = GPIO_INPUT ,
  .columns_pins[3].port      = GPIO_PORTC  ,
  .columns_pins[3].pin       = GPIO_PIN7   ,
  .columns_pins[3].logic     = GPIO_LOW    ,
  .columns_pins[3].direction = GPIO_INPUT ,
};



lcd_8bit_t lcd1 = 
{
  .lcd_rs.port      = GPIO_PORTA ,
  .lcd_rs.pin       = GPIO_PIN0 ,
  .lcd_rs.logic     = GPIO_LOW ,
  .lcd_rs.direction = GPIO_OUTPUT ,
  
  .lcd_en.port      = GPIO_PORTA ,
  .lcd_en.pin       = GPIO_PIN1 ,
  .lcd_en.logic     = GPIO_LOW ,
  .lcd_en.direction = GPIO_OUTPUT ,
  
  .lcd_data[0].port      = GPIO_PORTD ,
  .lcd_data[0].pin       = GPIO_PIN0 ,
  .lcd_data[0].logic     = GPIO_LOW ,
  .lcd_data[0].direction = GPIO_OUTPUT ,
  
  .lcd_data[1].port      = GPIO_PORTD ,
  .lcd_data[1].pin       = GPIO_PIN1 ,
  .lcd_data[1].logic     = GPIO_LOW ,
  .lcd_data[1].direction = GPIO_OUTPUT ,
  
  .lcd_data[2].port      = GPIO_PORTD ,
  .lcd_data[2].pin       = GPIO_PIN2 ,
  .lcd_data[2].logic     = GPIO_LOW ,
  .lcd_data[2].direction = GPIO_OUTPUT ,
  
  .lcd_data[3].port      = GPIO_PORTD ,
  .lcd_data[3].pin       = GPIO_PIN3 ,
  .lcd_data[3].logic     = GPIO_LOW ,
  .lcd_data[3].direction = GPIO_OUTPUT ,
  
  .lcd_data[4].port      = GPIO_PORTD ,
  .lcd_data[4].pin       = GPIO_PIN4 ,
  .lcd_data[4].logic     = GPIO_LOW ,
  .lcd_data[4].direction = GPIO_OUTPUT ,
  
  .lcd_data[5].port      = GPIO_PORTD ,
  .lcd_data[5].pin       = GPIO_PIN5 ,
  .lcd_data[5].logic     = GPIO_LOW ,
  .lcd_data[5].direction = GPIO_OUTPUT ,
  
  .lcd_data[6].port      = GPIO_PORTD ,
  .lcd_data[6].pin       = GPIO_PIN6 ,
  .lcd_data[6].logic     = GPIO_LOW ,
  .lcd_data[6].direction = GPIO_OUTPUT ,
  
  .lcd_data[7].port      = GPIO_PORTD ,
  .lcd_data[7].pin       = GPIO_PIN7 ,
  .lcd_data[7].logic     = GPIO_LOW ,
  .lcd_data[7].direction = GPIO_OUTPUT ,
};


Std_ReturnType ret = 0 ;
uint32 num1 = 0 , num2 = 0 , error = 0 ;
uint32 result = 0 ;
uint32 func[6]={ADD,SUBB,MUL,DIV,EQL,CLR};


int main() {
    
    APPLICATION_INTIALIZE();
    
    
    ret = lcd_8bit_send_string_data(&lcd1 , "Welcome") ;
    __delay_ms(500);
    ret = lcd_8bit_send_command(&lcd1,_LCD_CLEAR) ;
    __delay_ms(100);
    ret = lcd_8bit_send_string_data(&lcd1 , "Welcome") ;
    __delay_ms(500);
    ret = lcd_8bit_send_command(&lcd1,_LCD_CLEAR) ;
    __delay_ms(100);
    ret = lcd_8bit_send_string_data(&lcd1 , "Welcome") ;
    __delay_ms(500);
    ret = lcd_8bit_send_command(&lcd1,_LCD_CLEAR) ;
    __delay_ms(100);
    while(1){
        Get_Number_one(&num1);
   
        
       
    
    }
   
     
  
    
    return (EXIT_SUCCESS);
}



void APPLICATION_INTIALIZE(void){
    Std_ReturnType ret = 0 ;
    ret = keypad_intialize(&keypad1) ;
    ret = lcd_8bit_intialize(&lcd1) ;
}


void Get_Number_one(uint32 *number_one)
{
    uint32 value=0 , sub_value=0 , tens = 1   ;
    uint32 conv=0;
    while((value!='+')  && (value!='-') && (value!='/') && (value!='*') && (value!= '=') && (value!= '#'))
    {
        ret = keypad_get_value(&keypad1,&value);
        conv = atoi(&value);
        if( value != sub_value )
        {
            {
                if( ( (value=='+')  || (value=='-') || (value=='/') || (value=='*') || (value== '=') ) && (*number_one==0) )
                {
                    ret = lcd_8bit_send_command(&lcd1,_LCD_CLEAR);
                    ret = lcd_8bit_send_string_data(&lcd1 , "SYNTEX ERROR !!");
                    __delay_ms(500);
                    value = '#';
                }
                if( value != '#')
                {
                    ret = lcd_8bit_send_char_data(&lcd1,value);
                    __delay_ms(200);
                }
                if((value!='+')  && (value!='-') && (value!='/') && (value!='*') && (value!= '=') && (value!= '#'))
                {
                    *number_one =  ( (*number_one) * tens) + conv ;
                }
                tens *= 10 ;
            }
            sub_value = value ;
        }
    }
    Get_Func(number_one,&result,&value);
}

void Get_Number_Two(uint32 *number_two )
{
    uint32 value=0 , sub_value=0  , tens = 1   ;
    uint32 conv = 0 ;
    while((value!='+')  && (value!='-') && (value!='/') && (value!='*') && (value!= '=') && (value!= '#'))
    {
        ret = keypad_get_value(&keypad1,&value);
        conv = atoi(&value);
        error = 0 ;
        if( value != sub_value )
        {
            {
                if( ( (value=='+')  || (value=='-') || (value=='/') || (value=='*') || (value== '=') ) && (*number_two==0) )
                {
                    ret = lcd_8bit_send_command(&lcd1,_LCD_CLEAR);
                    ret = lcd_8bit_send_string_data(&lcd1 , "SYNTEX ERROR !!");
                    __delay_ms(500);
                    clear(&num1,number_two);
                    error =1 ;
                    break ;
                }
                if( value != '#')
                {
                    ret = lcd_8bit_send_char_data(&lcd1,value);
                    __delay_ms(200);
                }
                if((value!='+')  && (value!='-') && (value!='/') && (value!='*') && (value!= '=') && (value!= '#') )
                {
                    *number_two =  *number_two * tens + conv ;
                }
                
                tens *= 10 ;
            }
            sub_value = value ;
            
        }
    }
}

 void Get_Func(uint32 *number_one, uint32 *res ,uint32 *op )
{
    uint32 str[4]={0}; 
    uint32 *number_two = &num2 ;
    switch(*op)
    {
        case ADD :
            Get_Number_Two(&num2);
            *res = *number_one + *number_two  ;
            if(error==0)
            {
                Equal(res,str);
            }
            break;
         case SUBB :
            Get_Number_Two(&num2);
            *res = *number_one -  *number_two  ;
            if(error==0)
            {
                Equal(res,str);
            }
            break; 
        case MUL :
            Get_Number_Two(&num2);
            *res = *number_one * *number_two  ;
            if(error==0)
            {
                Equal(res,str);
            }
            break;
        case DIV :
            Get_Number_Two(&num2);
            *res = *number_one / *number_two  ;
            if(error==0)
            {
                Equal(res,str);
            }
            break;
        case EQL :
            Equal(res,str);
            break;
        case CLR :
            clear(number_one,number_two) ;
            break;    
    }
}

 
 void Equal(uint32 *res , uint32 *str)
 {
     ret = convert_byte_to_string(*res ,str);
     ret = lcd_8bit_send_string_data(&lcd1,str);
 }
void clear(uint32 *number_one , uint32 *number_two)
{
    ret = lcd_8bit_send_command(&lcd1,_LCD_CLEAR);
    *number_one = 0 ; 
    *number_two = 0 ; 
}
