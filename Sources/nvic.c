#include "nvic.h"

#define CLEAN_BYTE_NVIC     0xFFUL
#define PRIOR_BITS          0x06UL
#define BITS_MASK           0x03UL
#define IRQs_MAKS           0x1FUL

#define IPR_SEL(IRQ)   ( ( (IRQ) & IRQs_MAKS ) >> 2UL )

#define P_SHIFT(IRQ)   ( ( (IRQ) % 4UL ) * (1UL << 3UL) )

#define G_PENDING(Register_Member,irq) ( ((Register_Member) & (1UL << ((irq) & IRQs_MAKS))) != 0UL ? 1UL : 0UL)

void nvic_SetPriority( IRQ_Types irq, uint32_t priority )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    NVIC->IPR[IPR_SEL(((uint32_t)irq))] &=  ~( CLEAN_BYTE_NVIC << P_SHIFT(((uint32_t)irq)) ); 

    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    NVIC->IPR[IPR_SEL(((uint32_t)irq))] |= ( ( (priority & BITS_MASK) << PRIOR_BITS ) << P_SHIFT(((uint32_t)irq)) );
}
	
uint32_t nvic_GetPriority( IRQ_Types irq )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    return  ((( NVIC->IPR[IPR_SEL(((uint32_t)irq))] >> P_SHIFT(((uint32_t)irq)) ) & (CLEAN_BYTE_NVIC)) >> PRIOR_BITS) ;
}

void nvic_EnableIrq( IRQ_Types irq )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    NVIC->ISER |= (1UL << (((uint32_t)irq) & IRQs_MAKS));
}

void nvic_DisableIrq( IRQ_Types irq )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    NVIC->ICER &= (1UL << (((uint32_t)irq) & IRQs_MAKS));
}

uint32_t nvic_GetPendingIrq( IRQ_Types irq )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    return ( ( (NVIC->ISPR & (1UL << (((uint32_t)irq) & IRQs_MAKS)) ) != 0UL ) ? 1UL : 0UL);
}

void nvic_SetPendingIrq( IRQ_Types irq )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    NVIC->ISPR = (1UL << (((uint32_t)irq) & IRQs_MAKS));
}

void nvic_ClearPendingIrq( IRQ_Types irq )
{
    //The suppresion is needed because the driver will assignet the value directly in the register
    /* cppcheck-suppress misra-c2012-11.4 */
    NVIC->ICPR = (1UL << (((uint32_t)irq) & IRQs_MAKS));
}
