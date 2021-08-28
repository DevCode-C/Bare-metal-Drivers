#include "nvic.h"

#define CLEAN_BYTE_NVIC     0xFFU
#define PRIOR_BITS          0x06U
#define BITS_MASK           0x03U
#define IRQs_MAKS           0x1FU

#define IPR_SEL(IRQ)   ( ( (IRQ) & IRQs_MAKS ) >> 2U )

#define P_SHIFT(IRQ)   ( ( (IRQ) % 4U ) * (1 << 3) )

#define G_PENDING(Register_Member,irq) ( ((Register_Member) & (1 << (irq & IRQs_MAKS))) != 0 ? 1U : 0)

void nvic_SetPriority( IRQ_Types irq, uint32_t priority )
{
    NVIC->IPR[IPR_SEL(irq)] &=  ~( CLEAN_BYTE_NVIC << P_SHIFT(irq) ); 
    NVIC->IPR[IPR_SEL(irq)] |= ( ( (priority & BITS_MASK) << PRIOR_BITS ) << P_SHIFT(irq) );
}
	
uint32_t nvic_GetPriority( IRQ_Types irq )
{
    return  ((( NVIC->IPR[IPR_SEL(irq)] >> P_SHIFT(irq) ) & (CLEAN_BYTE_NVIC)) >> PRIOR_BITS) ;
}

void nvic_EnableIrq( IRQ_Types irq )
{
    NVIC->ISER |= (1 << (irq & IRQs_MAKS));
}

void nvic_DisableIrq( IRQ_Types irq )
{
    NVIC->ICER &= (1 << (irq & IRQs_MAKS));
}

uint32_t nvic_GetPendingIrq( IRQ_Types irq )
{
    return ( (NVIC->ISPR & (1 << (irq & IRQs_MAKS)) ) != 0 ? 1U : 0);
    // return G_PENDING(NVIC->ISPR,irq);
}

void nvic_SetPendingIrq( IRQ_Types irq )
{
    NVIC->ISPR = (1 << (irq & IRQs_MAKS));
}

void nvic_ClearPendingIrq( IRQ_Types irq )
{
    NVIC->ICPR = (1 << (irq & IRQs_MAKS));
}

// 04201 62910