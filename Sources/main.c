#include "stdio.h"
#include "types.h"
#include "gpio.h"
#include "rcc.h"
#include "nvic.h"
#include "uart.h"

volatile uint8_t flag = 0;
GPIO_InitTypeDef portConfig;    
UART_InitTypeDef uartConfig;

uint8_t RxBuffer[20];
uint8_t RxByte;
volatile uint8_t status = RESET;

const uint8_t msgInt[]   = {"Interrupcion UART TX\n"};
const uint8_t msgBlock[] = {"Mensaje UART Tx\n"};

extern void initialise_monitor_handles(void);

uint32_t charToDigit(uint8_t* charDigit);
int main(void)
{
    initialise_monitor_handles();
    printf("\n");
    uint32_t blinkTime = 1000000;
    /* Enable clock for GPIO port A, RCC_AHBENR bit  */
    RCC_GPIOx_CLK_EN(RCC_GPIOA);
    /* Configure GPIOA pin 5 as output */
    portConfig.Mode = GPIO_MODE_OUTPUT;
    portConfig.Pin = GPIO_PIN_5;
    portConfig.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOA,&portConfig);

    RCC_GPIOx_CLK_EN(RCC_GPIOC);
    portConfig.Mode = GPIO_MODE_IT_FALLING;
    portConfig.Pin = GPIO_PIN_13;
    portConfig.Pull = GPIO_NOPULL;
    gpio_configPort(GPIOC,&portConfig);
    nvic_SetPriority(EXTI4_15_IRQn,NVIC_HIGH_PRIORITY);
    nvic_EnableIrq(EXTI4_15_IRQn);

    RCC_USARTx_CLK_EN(RCC_USART2);
    uartConfig.uart = USART2;
    uartConfig.BaudRate = 9600U;
    uartConfig.HwFlowCtl = UART_HWCONTROL_NONE;
    uartConfig.WordLength = UART_WORDLENGTH_8B;
    uartConfig.StopBits = UART_STOPBITS_1;
    uartConfig.Parity = UART_PARITY_NONE;
    uartConfig.TxRxMode = UART_MODE_TX_RX;
    uart_configPort(&uartConfig);

    for(;;)
    {
        uart_sendBuffer(&uartConfig,(uint8_t*)msgBlock,(sizeof(msgBlock)));
        // if (status == SET)
        // {
        //     status = RESET;
        //     blinkTime = charToDigit(RxBuffer);
            
            // printf("%ld\n",blinkTime);
            
        // }
        gpio_togglePins(GPIOA,GPIO_PIN_5);
        _delay(blinkTime);
    }

    return 0;
}

void uart_mspInit( UART_InitTypeDef *uartH ) /* cppcheck-suppress misra-c2012-2.7 */
{
    RCC_GPIOx_CLK_EN(RCC_GPIOA);
    GPIO_InitTypeDef GPIO_UART_Config; 
    GPIO_UART_Config.Mode = GPIO_MODE_ALT;
    GPIO_UART_Config.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_UART_Config.Pull = GPIO_NOPULL;
    GPIO_UART_Config.Alternate = AF1;
    gpio_configPort(GPIOA,&GPIO_UART_Config);

    nvic_SetPriority(USART2_IRQn,NVIC_HIGHEST_PRIORITY);
    nvic_EnableIrq(USART2_IRQn);
    uart_receiveBufferInt(&uartConfig,&RxByte,1);
}

void uart_isrRxCallback( UART_InitTypeDef *uartH )
{
    static uint32_t i = 0;
    RxBuffer[i] = RxByte;
    i++;
    if(RxBuffer[i-1] == '\r')
    {
        RxBuffer[i-1] = '\0';
        status = SET;
        i=0;
    }
    uart_receiveBufferInt(&uartConfig,&RxByte,1);
}

void USART2_handler(void)
{
    uart_isrHandler(&uartConfig);
}

void EXTI4_15_handler(void)
{
    gpio_isrHandler(GPIO_PIN_13);
}

void gpio_isrCallback(uint32_t pin)
{
    uart_sendBufferInt(&uartConfig,(uint8_t*)msgInt,sizeof(msgInt));   
}

uint32_t charToDigit(uint8_t* charDigit)
{
    uint32_t temp = 0;
    uint8_t i = 0;

    if (charDigit[0] == '-')
    {
        i++;
    }
    while (charDigit[i] != '\0')
    {
        temp = temp * 10 +(charDigit[i++] - '0');
    }
    if (charDigit[0] == '-')
    {
        temp = temp * (-1U);
    }
    return temp;
    
    
}
