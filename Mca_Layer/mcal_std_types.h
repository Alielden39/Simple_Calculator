/* 
 * File:   mcal_std_types.h
 * Author: Alielden
 *
 * Created on September 9, 2023, 6:51 PM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H


/* Section :  Includes */

#include "std_libriries.h"
#include "compiler.h"


/* Section : Macros  */ 
#define _XTAL_FREQ 4000000
/* Section : Macros Functions */


/* Section : Data type Declaration */

typedef unsigned char   uint8 ;
typedef unsigned short  uint16 ;
typedef unsigned int    uint32 ;

typedef signed char   sint8 ;
typedef signed short  sint16 ;
typedef signed int    sint32 ;

typedef uint8  Std_ReturnType ;


/* Section : Macros */

#define STD_LOW      0x00
#define STD_HIGH     0x01

#define STD_OFF      0x00
#define STD_ON       0x01

#define STD_IDLE     0x00
#define STD_ACTIVE   0x01

#define STD_NOT_OK   (Std_ReturnType)0x00
#define STD_OK       (Std_ReturnType)0x01


/* Section : Functions Declaration */


#endif	/* MCAL_STD_TYPES_H */

