#include "registers.h"

#ifndef RCC__H
#define RCC__H

#define RCC_GPIOA   17UL
#define RCC_GPIOB   18UL
#define RCC_GPIOC   19UL
#define RCC_GPIOD   20UL
#define RCC_GPIOF   22UL

#define RCC_USART1  14UL
#define RCC_USART2  17UL
#define RCC_USART3  18UL
#define RCC_USART4  19UL
#define RCC_USART5  20UL
#define RCC_USART6  5UL

#define RCC_GPIOx_CLK_EN(RCC_GPIOx)      ( RCC->AHBENR |= ( 1UL << (RCC_GPIOx) ))  //Enable GPIOx RCC clock bus
#define RCC_GPIOx_CLK_DIS(RCC_GPIOx)     ( RCC->AHBENR &= ( 0UL << (RCC_GPIOx) ))  //Disable GPIOx RCC clock bus

#define RCC_USARTx_CLK_EN(RCC_USARTx)   ( (((RCC_USARTx) == RCC_USART1 ) || ((RCC_USARTx) == RCC_USART6 )) \
                                        ? SET_BIT(RCC->APB2ENR,(RCC_USARTx)) : SET_BIT(RCC->APB1ENR,(RCC_USARTx)))

#define RCC_USARTx_CLK_DIS(RCC_USARTx)  ( (((RCC_USARTx) == RCC_USART1 ) || ((RCC_USARTx) == RCC_USART6 )) \
                                        ? RESET_BIT(RCC->APB2ENR,(RCC_USARTx)) : RESET_BIT(RCC->APB1ENR,(RCC_USARTx)))

#endif