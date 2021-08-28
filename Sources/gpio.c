#include "gpio.h"

#define NO_PIN      0x00U
#define GPIO_RESET  0x03UL
#define ALTER_RL    0x08U

#define CONFIG_MASK  ((config->Mode == GPIO_MODE_OUTPUT) || (config->Mode == GPIO_MODE_INPUT) ||\
                      (config->Mode == GPIO_MODE_ANALOG) || (config->Mode == GPIO_MODE_ALT))

#define CONFIG_IT_MAKS  ((config->Mode == GPIO_MODE_IT_FALLING) || (config->Mode == GPIO_MODE_IT_RISING) || \
                        (config->Mode == GPIO_MODE_IT_BOTH) )



void gpio_configPort(GPIO_TypeDef* port, GPIO_InitTypeDef* config)
{
    __IO uint8_t pos = 0x0U;
    while ((config->Pin >> pos) != NO_PIN)
    {
        if (BITCHECK(config->Pin,pos) != NO_PIN)
        {   
            if (CONFIG_MASK)
            {
                //Configure the register moder (Type of GPIOx mode)
                port->MODER &= ~(GPIO_RESET << (pos*2));
                port->MODER |= ((config->Mode % 4U) <<(pos*2));

                if (config->Mode == GPIO_MODE_ALT)
                {
                    if (pos < ALTER_RL)
                    {
                        port->AFRL &= (~(0xFU<<((pos & 0x07U)*4U)));
                        port->AFRL |= ((config->Alternate) << ((pos & 0x07U)*4U));
                    }
                    else
                    {
                        port->AFRH &= (~(0xFU<<((pos & 0x07U)*4U)));
                        port->AFRH |= ((config->Alternate) << ((pos & 0x07U)*4U));
                    }
                }
            }
            port->PUPDR &= ~(GPIO_RESET << (pos*2));
            port->PUPDR |= ((config->Pull % 3U) << (pos*2));

            port->OSPEEDR &= ~(GPIO_RESET << (pos*2));
            SET_BIT(port->OSPEEDR,(pos*2));


            if (CONFIG_IT_MAKS)
            {
                RESET_BIT(RCC->APB2ENR,0);
                SET_BIT(RCC->APB2ENR,0);

                EXTI->IMR &= ~(config->Pin);
                EXTI->IMR |=  (config->Pin);

                if (config->Mode == GPIO_MODE_IT_FALLING)
                {
                    EXTI->FTSR &= ~(config->Pin);
                    EXTI->FTSR |= (config->Pin);

                }
                else if(config->Mode == GPIO_MODE_IT_RISING)
                {
                    EXTI->RTSR &= ~(config->Pin);
                    EXTI->RTSR |= (config->Pin);
                }
                else
                {
                    EXTI->FTSR &= ~(config->Pin);
                    EXTI->FTSR |= (config->Pin);  

                    EXTI->RTSR &= ~(config->Pin);
                    EXTI->RTSR |= (config->Pin);
                }
                
                volatile uint8_t temp_Syscfg_Port_x = 0;
                switch (((uint32_t)port))
                {
                case GPIOA_BASE:
                    temp_Syscfg_Port_x = 0x0;
                    break;
                case GPIOB_BASE:
                    temp_Syscfg_Port_x = 0x1U;
                    break;
                case GPIOC_BASE:
                    temp_Syscfg_Port_x = 0x2U;
                    break;
                case GPIOD_BASE:
                    temp_Syscfg_Port_x = 0x3U;
                    break;
                case GPIOF_BASE:
                    temp_Syscfg_Port_x = 0x5U;
                    break;
                default:
                    break;
                }

                SYSCFG->EXTICR[(pos >> 2U)] &= ~((0x0FU) << (4 * (pos % 4)));

                SYSCFG->EXTICR[(pos >> 2U)] |= ((temp_Syscfg_Port_x) << (4 * (pos % 4)));
            }
        }
        pos++;
    }
}

void gpio_writePort(GPIO_TypeDef* port, uint32_t value)
{
    port->ODR = (0xFFFFU & value);
}

uint32_t gpio_readPort(GPIO_TypeDef* port)
{
    return port->IDR;
}

void gpio_setPins(GPIO_TypeDef* port, uint32_t pins)
{
    port->BSRR = (0xFFFFU & pins);
}

void gpio_resetPins(GPIO_TypeDef* port, uint32_t pins)
{
    port->BSRR = (0xFFFF0000U & (pins<<HALF_WORD));
}

void gpio_togglePins(GPIO_TypeDef* port, uint32_t pins)
{
    port->ODR ^= (0xFFFFU & pins);
}

void gpio_writePins(GPIO_TypeDef* port, uint32_t pins, uint32_t value)
{
    if (value != RESET)
    {
        gpio_setPins(port,pins);
    }
    else
    {
        gpio_resetPins(port,pins);
    }
}

uint32_t gpio_readPin(GPIO_TypeDef* port, uint32_t pin)
{
    uint8_t temp = 0;
    if ((port->IDR & pin) != (uint32_t)RESET)
    {
        temp = 1U;
    }
    else
    {
        temp = 0U;
    }
    return temp;
}

void gpio_isrHandler(uint32_t pin)
{
    EXTI->PR |= pin;
    gpio_isrCallback(pin);
}

 _weak void gpio_isrCallback(uint32_t pin)
{
    (void)pin; 
}