#ifndef TYPES__H
    #define TYPES__H

    /*Privates defines*/    
    #define _delay(cuentas)         for(volatile uint32_t i = 0; i < (cuentas) ;i++)
    #define _weak   __attribute__((weak))

    #define SET     1UL
    #define RESET   0UL

    #define BYTE        8UL
    #define HALF_WORD   16UL
    #define WORD        32UL

    #define LEFT_SHIFT(var,bits)    ((var) <<= (bits) )
    #define RIGTH_SHIFT(var,bits)   ((var) >>= (bits) )

    #define SET_BIT(var,BIT)       ((var) |=  (1UL << (BIT) ))

    #define RESET_BIT(var,BIT)     ((var) &= ~(1UL << (BIT) ))

    #define TOOGLE_BIT(var,BIT)    ((var) ^=  (1UL << (BIT) ))

    #define BITCHECK(var,BIT)      ((var) &   (1UL << (BIT) ))

    /*Private typedef definitions---*/
    typedef unsigned long uint32_t;
    typedef unsigned short uint16_t;
    typedef unsigned char uint8_t;
    /*------------------------------*/
    typedef signed long int32_t;
    typedef signed short int16_t;
    typedef signed char int8_t;

#endif