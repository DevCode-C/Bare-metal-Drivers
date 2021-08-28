#include "registers.h"

#ifndef __RCC__H
#define __RCC__H

#define RCC_GPIOA   17U
#define RCC_GPIOB   18U
#define RCC_GPIOC   19U
#define RCC_GPIOD   20U
#define RCC_GPIOF   22U

#define RCC_USART1  14U  
#define RCC_USART2  17U
#define RCC_USART3  18U
#define RCC_USART4  19U
#define RCC_USART5  20U
#define RCC_USART6  5U

#define RCC_GPIOx_CLK_EN(RCC_GPIOx)      ( RCC->AHBENR |= ( 1 << (RCC_GPIOx) ))  //Enable GPIOx RCC clock bus
#define RCC_GPIOx_CLK_DIS(RCC_GPIOx)     ( RCC->AHBENR &= ( 0 << (RCC_GPIOx) ))  //Disable GPIOx RCC clock bus

#define RCC_USARTx_CLK_EN(RCC_USARTx)   ( (((RCC_USARTx) == RCC_USART1 ) || ((RCC_USARTx) == RCC_USART6 )) \
                                        ? SET_BIT(RCC->APB2ENR,(RCC_USARTx)) : SET_BIT(RCC->APB1ENR,(RCC_USARTx)))

#define RCC_USARTx_CLK_DIS(RCC_USARTx)  ( (((RCC_USARTx) == RCC_USART1 ) || ((RCC_USARTx) == RCC_USART6 )) \
                                        ? RESET_BIT(RCC->APB2ENR,(RCC_USARTx)) : RESET_BIT(RCC->APB1ENR,(RCC_USARTx)))

#endif