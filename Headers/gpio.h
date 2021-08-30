#include "types.h"
#include "registers.h"

#ifndef GPIO__H
#define GPIO__H

typedef enum
{
    GPIO_MODE_INPUT     = (0U),
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALT,
    GPIO_MODE_ANALOG,
    GPIO_MODE_IT_FALLING,
    GPIO_MODE_IT_RISING,
    GPIO_MODE_IT_BOTH
}GPIOx_MODE;

typedef enum
{
    GPIO_NOPULL     = (0U),
    GPIO_PULLUP,
    GPIO_PULLDOWN
}GPIOx_PULL;

typedef enum 
{
    AF0 = (0U),
    AF1,
    AF2,
    AF3,
    AF4,
    AF5,
    AF6,
    AF7,
}GPIOx_ALT;

typedef struct gpio
{
    volatile uint32_t   Pin;
    GPIOx_MODE      Mode;
    GPIOx_PULL      Pull;
    GPIOx_ALT       Alternate;
}GPIO_InitTypeDef;

#define GPIO_PIN_0      (0x0001UL)     
#define GPIO_PIN_1      (0x0002UL)
#define GPIO_PIN_2      (0x0004UL)
#define GPIO_PIN_3      (0x0008UL)
#define GPIO_PIN_4      (0x0010UL)
#define GPIO_PIN_5      (0x0020UL)
#define GPIO_PIN_6      (0x0040UL)
#define GPIO_PIN_7      (0x0080UL)
#define GPIO_PIN_8      (0x0100UL)
#define GPIO_PIN_9      (0x0200UL)
#define GPIO_PIN_10     (0x0400UL)
#define GPIO_PIN_11     (0x0800UL)
#define GPIO_PIN_12     (0x1000UL)
#define GPIO_PIN_13     (0x2000UL)
#define GPIO_PIN_14     (0x4000UL)
#define GPIO_PIN_15     (0x8000UL)
#define GPIO_PIN_ALL    (0xFFFFUL)


/**
 * @brief Configura los registros del puerto
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param GPIO_InitTypeDef* config , 
 * 
 * @return NONE (void)
*/
void gpio_configPort(GPIO_TypeDef* port, GPIO_InitTypeDef* config);

/**
 * @brief escribe un valor completo en el puerto indicado.
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param uint32_t value
 * 
 * @return NONE (void)
*/
void gpio_writePort(GPIO_TypeDef* port, uint32_t value);

/**
 * @brief regresa el valor del puerto indicado.
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @return uint32_t
*/
uint32_t gpio_readPort(GPIO_TypeDef* port);

/**
 * @brief pone en uno aquellos pines indicados en la variable pins, donde cada bit representa un pin 
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param uint32_t pins
 * 
 * @return NONE (void)
*/
void gpio_setPins(GPIO_TypeDef* port, uint32_t pins);

/**
 * @brief pone en cero aquellos pines indicados en la variable pins, donde cada bit representa un pin 
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param uint32_t pins
 * 
 * @return NONE (void)
*/
void gpio_resetPins(GPIO_TypeDef* port, uint32_t pins);

/**
 * @brief invierte el estado de aquellos pines indicados en la variable pins, donde cada bit representa un pin
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param uint32_t pins
 * 
 * @return NONE (void)
*/
void gpio_togglePins(GPIO_TypeDef* port, uint32_t pins);

/**
 * @brief escribe el valor indicado por value (0 o 1) en el pin indicado por el parámetro pin.
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param uint32_t pins
 * 
 * @param uint32_t value
 * 
 * @return NONE (void)
*/
void gpio_writePins(GPIO_TypeDef* port, uint32_t pins, uint32_t value);

/**
 * @brief regresa el valor del pin indicado del puerto indicado por el parámetro pin.
 * 
 * @param GPIO_TypeDef* port , 
 * 
 * @param uint32_t pin
 * 
 * @return uint32_t 
*/
uint32_t gpio_readPin(GPIO_TypeDef* port, uint32_t pin);

/**
 * @brief 
 *  
 * @param uint32_t pin
 * 
 * @return NONE (void) 
*/
void gpio_isrHandler(uint32_t pin);

/**
 * @brief 
 *  
 * @param uint32_t pin
 * 
 * @return NONE (void) 
*/
void gpio_isrCallback(uint32_t pin);

#endif