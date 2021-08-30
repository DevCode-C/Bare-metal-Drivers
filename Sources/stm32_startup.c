typedef unsigned long uint32_t;
typedef unsigned char uint8_t;

#define SRAM_START  0x20000000UL
#define SRAM_SIZE   (16UL * 1024UL)//16Kb
#define SRAM_END    (SRAM_START + (SRAM_SIZE))

#define STACK_START SRAM_END

extern uint32_t _etext;

extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _la_data;

extern uint32_t _sbss;
extern uint32_t _ebss;
void __libc_init_array(void);
int main(void);

void Reset_handler(void);
void NMI_handler(void)                          __attribute__((weak,alias("Default_handler")));
void HardFault_handler(void)                    __attribute__((weak,alias("Default_handler")));
void SVCall_handler(void)                       __attribute__((weak,alias("Default_handler")));
void PendSV_handler(void)                       __attribute__((weak,alias("Default_handler")));
void SysTick_handler(void)                      __attribute__((weak,alias("Default_handler")));

void WWDG_handler(void)                         __attribute__((weak,alias("Default_handler")));
void RTC_handler(void)                          __attribute__((weak,alias("Default_handler")));
void FLASH_handler(void)                        __attribute__((weak,alias("Default_handler")));
void RCC_handler(void)                          __attribute__((weak,alias("Default_handler")));
void EXTI0_1_handler(void)                      __attribute__((weak,alias("Default_handler")));
void EXTI2_3_handler(void)                      __attribute__((weak,alias("Default_handler")));
void EXTI4_15_handler(void)                     __attribute__((weak,alias("Default_handler")));
void DMA_CH1_handler(void)                      __attribute__((weak,alias("Default_handler")));
void DMA_CH2_3_handler(void)                    __attribute__((weak,alias("Default_handler")));
void DMA_CH4_5_handler(void)                    __attribute__((weak,alias("Default_handler")));
void ADC_handler(void)                          __attribute__((weak,alias("Default_handler")));
void TIM1_BRK_UP_TRG_COM_handler(void)          __attribute__((weak,alias("Default_handler")));
void TIM1_CC_handler(void)                      __attribute__((weak,alias("Default_handler")));
void TIM3_handler(void)                         __attribute__((weak,alias("Default_handler")));
void TIM6_handler(void)                         __attribute__((weak,alias("Default_handler")));
void TIM14_handler(void)                        __attribute__((weak,alias("Default_handler")));
void TIM15_handler(void)                        __attribute__((weak,alias("Default_handler")));
void TIM16_handler(void)                        __attribute__((weak,alias("Default_handler")));
void TIM17_handler(void)                        __attribute__((weak,alias("Default_handler")));
void I2C1_handler(void)                         __attribute__((weak,alias("Default_handler")));
void I2C2_handler(void)                         __attribute__((weak,alias("Default_handler")));
void SPI1_handler(void)                         __attribute__((weak,alias("Default_handler")));
void SPI2_handler(void)                         __attribute__((weak,alias("Default_handler")));
void USART1_handler(void)                       __attribute__((weak,alias("Default_handler")));
void USART2_handler(void)                       __attribute__((weak,alias("Default_handler")));
void USART3_4_5_6_handler(void)                 __attribute__((weak,alias("Default_handler")));
void USB_handler(void)                          __attribute__((weak,alias("Default_handler")));


uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    STACK_START,
    (uint32_t)&Reset_handler,
    (uint32_t)&NMI_handler,
    (uint32_t)&HardFault_handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t)&SVCall_handler,
    0,
    0,
    (uint32_t)&PendSV_handler,
    (uint32_t)&SysTick_handler,
    (uint32_t)&WWDG_handler,
    0,
    (uint32_t)&RTC_handler,
    (uint32_t)&FLASH_handler,
    (uint32_t)&RCC_handler,
    (uint32_t)&EXTI0_1_handler,
    (uint32_t)&EXTI2_3_handler,
    (uint32_t)&EXTI4_15_handler,
    0,
    (uint32_t)&DMA_CH1_handler,
    (uint32_t)&DMA_CH2_3_handler,
    (uint32_t)&DMA_CH4_5_handler,
    (uint32_t)&ADC_handler,
    (uint32_t)&TIM1_BRK_UP_TRG_COM_handler,
    (uint32_t)&TIM1_CC_handler,
    0,
    (uint32_t)&TIM3_handler,
    (uint32_t)&TIM6_handler,
    0,
    (uint32_t)&TIM14_handler,
    (uint32_t)&TIM15_handler,
    (uint32_t)&TIM16_handler,
    (uint32_t)&TIM17_handler,
    (uint32_t)&I2C1_handler,
    (uint32_t)&I2C2_handler,
    (uint32_t)&SPI1_handler,
    (uint32_t)&SPI2_handler,
    (uint32_t)&USART1_handler,
    (uint32_t)&USART2_handler,
    (uint32_t)&USART3_4_5_6_handler,
    0,
    (uint32_t)&USB_handler
};

void Default_handler(void)
{
    while (1)
    {

    }
}

void Reset_handler(void)
{
    /*copy .data section to SRAM
        Operation needed for get the size of data store in flash 
    */
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata; /* cppcheck-suppress misra-c2012-11.4 */
    

    uint8_t *pDst = (uint8_t*)&_sdata;
    uint8_t *pSrc = (uint8_t*)&_la_data;

    for (uint32_t i = 0; i < size; i++)
    {
        *pDst = *pSrc;
        pDst++;
        pSrc++;
    }
    

    /*init the .bss section to xeto in SRAM
        Operation needed for get the size of data store in flash 
    */
    size = (uint32_t)&_ebss - (uint32_t)&_sbss; /* cppcheck-suppress misra-c2012-11.4 */
    pDst = (uint8_t*)&_sbss;

    for (uint32_t i = 0; i < size; i++)
    {
        *pDst = 0;
        pDst++;
    }
    //call init function of std library
    __libc_init_array();
    //call main()
    (void) main();
}
