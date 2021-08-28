#include "types.h"
#include "registers.h"

#ifndef __NVIC__H
#define __NVIC__H

#define NVIC_HIGHEST_PRIORITY   0U
#define NVIC_HIGH_PRIORITY      1U
#define NVIC_LOW_PRIORITY       2U
#define NVIC_LOWEST_PRIORITY    3U
 
/**
 * @brief Establece la prioridad que tendrá la interrupción. 
 * 
 * @param IRQ_Types irq
 * 
 * @param uint32_t priority
 * 
 * @return NONE (void)
*/
void nvic_SetPriority( IRQ_Types irq, uint32_t priority );
	
/**
 * @brief Regresa el valor que tiene la prioridad. 
 * 
 * @param IRQ_Types irq 
 * 
 * @return NONE (void)
*/
uint32_t nvic_GetPriority( IRQ_Types irq );

/**
 * @brief Habilita la interrupción deseada, esto quiere decir que una interrupción podrá ser activada por una señal 
 * 
 * @param IRQ_Types irq 
 * 
 * @return NONE (void)
*/
void nvic_EnableIrq( IRQ_Types irq );

/**
 * @brief Deshabilita la interrupción deseada 
 * 
 * @param IRQ_Types irq 
 * 
 * @return NONE (void)
*/
void nvic_DisableIrq( IRQ_Types irq );

/**
 * @brief Regresa la interrupción que esta activa (esto no implica que el procesador la este atendiendo aun)
 * 
 * @param IRQ_Types irq 
 * 
 * @return uint32_t
*/
uint32_t nvic_GetPendingIrq( IRQ_Types irq );

/**
 * @brief Activa la interrupción para que el procesador la atienda.
 * 
 * @param IRQ_Types irq 
 * 
 * @return NONE (void)
*/
void nvic_SetPendingIrq( IRQ_Types irq );

/**
 * @brief Indica al procesador que ya no debe atender la interrupción
 * 
 * @param IRQ_Types irq 
 * 
 * @return NONE (void)
*/
void nvic_ClearPendingIrq( IRQ_Types irq );


#endif