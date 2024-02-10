/* 
 * File:   ecu_lcd.h
 * Author: Alielden
 *
 * Created on September 28, 2023, 6:25 PM
 */

#ifndef ECU_LCD_H
/* Section :  Includes */

#include "../../Mca_Layer/GPIO/hal_gpio.h"

/* Section : Macros */

/*******************COMMANDS*********************/
#define _LCD_CLEAR                           0x01
#define _LCD_CURSOR_HOME                     0x02
#define _LCD_ENTRY_MODE_INCREMENT            0x06
#define _LCD_ENTRY_MODE_DECREMENT            0x04
#define _LCD_CURSOR_MOVE_LEFT                0x10 
#define _LCD_CURSOR_MOVE_RIGHT               0x14 
#define _LCD_DISPLAY_SHIFT_LEFT              0x18 
#define _LCD_DISPLAY_SHIFT_RIGHT             0x1C
#define _LCD_DISPLAY_OFF                     0x08
#define _LCD_DISPLAY_ON_CURSOR_ON_BLINK_ON   0x0F
#define _LCD_DISPLAY_ON_CURSOR_ON_BLINK_OFF  0x0E
#define _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_ON  0x0D
#define _LCD_DISPLAY_ON_CURSOR_OFF_BLINK_OFF 0x0C
#define _LCD_8BIT_SET                        0x38
#define _LCD_4BIT_SET                        0x28
#define _LCD_CGRAM_START_ADDRESS             0x40
#define _LCD_DDRAM_START_ADDRESS             0x80

/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef struct
{
    pin_config_t lcd_rs ;
    pin_config_t lcd_en ;
    pin_config_t lcd_data[4] ;
}lcd_4bit_t;

typedef struct
{
    pin_config_t lcd_rs ;
    pin_config_t lcd_en ;
    pin_config_t lcd_data[8] ;
}lcd_8bit_t;


/* Section : Functions Declaration */
Std_ReturnType lcd_4bit_intialize(lcd_4bit_t *lcd);
Std_ReturnType lcd_4bit_send_command(lcd_4bit_t *lcd , uint8 command);
Std_ReturnType lcd_4bit_send_char_data(lcd_4bit_t *lcd , uint8 data);
Std_ReturnType lcd_4bit_send_char_data_pos(lcd_4bit_t *lcd ,uint8 row , uint8 column , uint8 data);
Std_ReturnType lcd_4bit_send_string_data(lcd_4bit_t *lcd , uint8 *str);
Std_ReturnType lcd_4bit_send_string_data_pos(lcd_4bit_t *lcd ,uint8 row , uint8 column , uint8 *str);
Std_ReturnType lcd_4bit_send_custom_char_data_pos(lcd_4bit_t *lcd ,uint8 row , uint8 column , uint8 chr[] , uint8 mem_pos);


Std_ReturnType lcd_8bit_intialize(lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_command(lcd_8bit_t *lcd , uint8 command);
Std_ReturnType lcd_8bit_send_char_data(lcd_8bit_t *lcd , uint8 data);
Std_ReturnType lcd_8bit_send_char_data_pos(lcd_8bit_t *lcd ,uint8 row , uint8 column , uint8 data);
Std_ReturnType lcd_8bit_send_string_data(lcd_8bit_t *lcd , uint8 *str);
Std_ReturnType lcd_8bit_send_string_data_pos(lcd_8bit_t *lcd ,uint8 row , uint8 column , uint8 *str);
Std_ReturnType lcd_8bit_send_custom_char_data_pos(lcd_8bit_t *lcd ,uint8 row , uint8 column , uint8 chr[] , uint8 mem_pos);

Std_ReturnType convert_byte_to_string( uint8 value , uint8 *str );
Std_ReturnType convert_short_to_string( uint16 value , uint8 *str );
Std_ReturnType convert_int_to_string( uint32 value , uint8 *str );

#endif	/* ECU_LCD_H */

