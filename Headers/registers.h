#include "types.h"
#ifndef REGISTERS__H
    #define REGISTERS__H

    typedef enum
    {
    WWDG_IRQn                   = 0,      
    RTC_IRQn                    = 2,            
    FLASH_IRQn                  = 3,            
    RCC_IRQn                    = 4,            
    EXTI0_1_IRQn                = 5,            
    EXTI2_3_IRQn                = 6,            
    EXTI4_15_IRQn               = 7,            
    DMA1_Channel1_IRQn          = 9,            
    DMA1_Channel2_3_IRQn        = 10,           
    DMA1_Channel4_5_IRQn        = 11,           
    ADC1_IRQn                   = 12,           
    TIM1_BRK_UP_TRG_COM_IRQn    = 13,           
    TIM1_CC_IRQn                = 14,           
    TIM3_IRQn                   = 16,           
    TIM6_IRQn                   = 17,           
    TIM7_IRQn                   = 18,           
    TIM14_IRQn                  = 19,           
    TIM15_IRQn                  = 20,           
    TIM16_IRQn                  = 21,           
    TIM17_IRQn                  = 22,           
    I2C1_IRQn                   = 23,           
    I2C2_IRQn                   = 24,           
    SPI1_IRQn                   = 25,           
    SPI2_IRQn                   = 26,           
    USART1_IRQn                 = 27,           
    USART2_IRQn                 = 28,           
    USART3_4_IRQn               = 29,           
    USB_IRQn                    = 31            
    }IRQ_Types;


    typedef struct __gpio_registers
    {
        volatile uint32_t MODER;
        volatile uint32_t OTYPER;
        volatile uint32_t OSPEEDR;
        volatile uint32_t PUPDR;
        volatile uint32_t IDR;
        volatile uint32_t ODR;
        volatile uint32_t BSRR;
        volatile uint32_t LCKR;
        volatile uint32_t AFRL;
        volatile uint32_t AFRH;
        volatile uint32_t BRR;
    }GPIO_TypeDef;

    typedef struct __rcc_registers
    {
        volatile uint32_t CR;
        volatile uint32_t CFGR;
        volatile uint32_t CIR;
        volatile uint32_t APB2RSTR;
        volatile uint32_t APB1RSTR;
        volatile uint32_t AHBENR;
        volatile uint32_t APB2ENR;
        volatile uint32_t APB1ENR;
        volatile uint32_t BDCR;
        volatile uint32_t CSR;
        volatile uint32_t AHBRSTR;
        volatile uint32_t CFGR2;
        volatile uint32_t CFGR3;
        volatile uint32_t CR2;
    }RCC_TypeDef;

    typedef struct{
        volatile uint32_t ISER;
        volatile uint32_t Reserved_0[31];
        volatile uint32_t ICER;
        volatile uint32_t Reserved_1[31];
        volatile uint32_t ISPR;
        volatile uint32_t Reserved_2[31];
        volatile uint32_t ICPR;
        volatile uint32_t Reserved_3[95];
        volatile uint32_t IPR[8];
    }NVIC_TypeDef;

    typedef struct __syscfg_registers
    {
        volatile uint32_t CFGR1;
        volatile uint32_t Reserved0;
        volatile uint32_t EXTICR[4];
        volatile uint32_t CFGR2;
    }SYSCFG_TypeDef;

    typedef struct __exti_registers
    {
        volatile uint32_t IMR;
        volatile uint32_t EMR;
        volatile uint32_t RTSR;
        volatile uint32_t FTSR;
        volatile uint32_t SWIER; 
        volatile uint32_t PR;
    }EXTI_TypeDef;


    typedef struct __uart_registers
    {
        volatile uint32_t CR1;
        volatile uint32_t CR2;
        volatile uint32_t CR3;
        volatile uint32_t BRR;
        volatile uint32_t Reserved;
        volatile uint32_t RTOR;
        volatile uint32_t RQR;
        volatile uint32_t ISR;
        volatile uint32_t ICR;
        volatile uint32_t RDR;
        volatile uint32_t TDR;
    }USART_TypeDef;
    


    #define PERIPHERALS_BASE    (0x40000000UL)
    #define PPB                 (0xE000E000UL)


    #define APB_BASE    (PERIPHERALS_BASE)
    #define AHB1_BASE   (PERIPHERALS_BASE | 0x00020000UL)
    #define AHB2_BASE   (PERIPHERALS_BASE | 0x08000000UL)


    #define GPIOA_BASE  (AHB2_BASE + 0x0UL)
    #define GPIOB_BASE  (AHB2_BASE + 0x0400U)
    #define GPIOC_BASE  (AHB2_BASE + 0x0800U)
    #define GPIOD_BASE  (AHB2_BASE + 0x0C00U)
    #define GPIOF_BASE  (AHB2_BASE + 0x1400U)

    #define RCC_BASE    (AHB1_BASE + 0x1000U)
    #define NVIC_BASE   (PPB + 0x100UL)
    #define SYSCFG_BASE (APB_BASE + 0x10000U)
    #define EXTI_BASE   (APB_BASE + 0x10400U)

    #define USART1_BASE (APB_BASE + 0x13800U)
    #define USART2_BASE (APB_BASE + 0x04400U)
    #define USART3_BASE (APB_BASE + 0x04800U)
    #define USART4_BASE (APB_BASE + 0x04C00U)
    #define USART5_BASE (APB_BASE + 0x05000U)
    #define USART6_BASE (APB_BASE + 0x11400U)


    #define GPIOA       ((GPIO_TypeDef *) GPIOA_BASE)
    #define GPIOB       ((GPIO_TypeDef *) GPIOB_BASE)
    #define GPIOC       ((GPIO_TypeDef *) GPIOC_BASE)
    #define GPIOD       ((GPIO_TypeDef *) GPIOD_BASE)
    #define GPIOF       ((GPIO_TypeDef *) GPIOF_BASE)

    #define RCC         ((RCC_TypeDef *)    RCC_BASE)
    #define NVIC        ((NVIC_TypeDef *)   NVIC_BASE)
    #define EXTI        ((EXTI_TypeDef *)   EXTI_BASE)
    #define SYSCFG      ((SYSCFG_TypeDef *) SYSCFG_BASE)

    #define USART1      ((USART_TypeDef*) USART1_BASE)
    #define USART2      ((USART_TypeDef*) USART2_BASE)
    #define USART3      ((USART_TypeDef*) USART3_BASE)
    #define USART4      ((USART_TypeDef*) USART4_BASE)
    #define USART5      ((USART_TypeDef*) USART5_BASE)
    #define USART6      ((USART_TypeDef*) USART6_BASE)


#endif