#include "uart.h"
#include "stdio.h"

#define INTERNAL_CLK    8000000UL
#define UART_ISR_TXE_FLAG   7U
#define UART_ISR_RXNE_FLAG  5U
#define UART_ISR_ORE_FLAG   3U
#define UART_ISR_PE_FLAG    0

#define UART_CR1_PEIE_IT       8U
#define UART_CR1_TXEIE_IT      7U
#define UART_CR1_TCIE_IT       6U
#define UART_CR1_RXNEIE_IT     5U


#define RESET_UART  0x3UL
#define RESET_WORDLENGTH    0x10001000UL

#define MASK_LENGTH8    0xFFU
#define MASK_LENGTH9    0x1FFU

void uart_configPort( UART_InitTypeDef *uartH )
{
    uart_mspInit(uartH);
    // RESET_BIT(uartH->uart->CR1,0);

    //Configuration of wordlength
    uartH->uart->CR1 &= ~(RESET_WORDLENGTH);
    uartH->uart->CR1 |= uartH->WordLength;

    //Reset bit 15 in CR1, OVER8 equal to oversampling 16
    RESET_BIT(uartH->uart->CR1,15U);

    //Configuration of Stopbits
    uartH->uart->CR2 &= ~(RESET_UART << 12U);
    uartH->uart->CR2 |= ((uartH->StopBits % 3U) << 12U);

    //Configuration of parity bits
    uartH->uart->CR1 &= ~(RESET_UART << 9U);
    uartH->uart->CR1 |= ((uartH->Parity % 4U) << 9U);

    //Configuration of HWControl 
    uartH->uart->CR3 &= ~(RESET_UART << 9U);
    uartH->uart->CR3 |= ((uartH->HwFlowCtl % 4U) << 9U);

    //Configuration of UART MODE
    uartH->uart->CR1 &= ~(RESET_UART << 2U);
    uartH->uart->CR1 |= ((uartH->TxRxMode % 4U) << 2U);

    //Configuration of baudRate
    uartH->uart->BRR = (uint32_t)(INTERNAL_CLK / uartH->BaudRate);

    /*  COnfiguration with OVERSAMPLING 8 
    uint32_t buadRateTemp = (uint32_t)((2*INTERNAL_CLK) / uartH->BaudRate);
    uartH->uart->BRR = (7UL & ((buadRateTemp & 0xFUL) >> 1));
    RESET_BIT(uartH->uart->BRR,3);
    uartH->uart->BRR |= (buadRateTemp & 0xFFFFFFF0UL);
    */

    //Active USARTx
    SET_BIT(uartH->uart->CR1,0);
}

_weak void uart_mspInit( UART_InitTypeDef *uartH )
{
    (void) uartH;
}
    
void uart_sendBuffer( UART_InitTypeDef *uartH, const uint8_t *ptr, uint32_t len )
{
    volatile uint16_t temp = 0;
    volatile uint16_t lentemp = len;
    uint16_t *ptr16bits;
    if (uartH->WordLength == UART_WORDLENGTH_9B)
    {
        ptr16bits = ptr;
    }
    // printf("%s\n",ptr);
    while (lentemp != 0UL)
    {
        if ((uartH->WordLength == UART_WORDLENGTH_9B) && (BITCHECK(uartH->uart->ISR,UART_ISR_TXE_FLAG)) )
        {
            uartH->uart->TDR = (ptr16bits[temp] & MASK_LENGTH9);
            temp++;
            lentemp--;
        }
        else if ((BITCHECK(uartH->uart->ISR,UART_ISR_TXE_FLAG) != 0UL))
        {
            uartH->uart->TDR = (ptr[temp] & MASK_LENGTH8);
            temp++;
            lentemp--;
        }
        else
        {
            /* code */
        }
        
        
    }
}

void uart_sendBufferInt( UART_InitTypeDef *uartH, const uint8_t *ptr, uint32_t len )
{
    if ((len > 0UL) && (ptr != NULL))
    {
        uartH->TxRxData.pTxBuffer = ptr;
        uartH->TxRxData.sizeTxBuffer = len;
        uartH->TxRxData.TxCounter = 0;
        
        //Active interrupt TXEIE 
        RESET_BIT(uartH->uart->CR1,UART_CR1_TXEIE_IT);
        SET_BIT(uartH->uart->CR1,UART_CR1_TXEIE_IT);
    }
    else
    {
       
    }
}

void uart_receiveBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len )
{
    if (len > 0UL)
    {
        uartH->TxRxData.pRxBuffer = ptr;
        uartH->TxRxData.sizeRxBuffer = len;
        uartH->TxRxData.RxCounter = 0;

        //Active interrupt 
        RESET_BIT(uartH->uart->CR1,UART_CR1_RXNEIE_IT);
        SET_BIT(uartH->uart->CR1,UART_CR1_RXNEIE_IT);   
        if (uartH->Parity != UART_PARITY_NONE)
        {
            RESET_BIT(uartH->uart->ICR,UART_CR1_PEIE_IT);
            SET_BIT(uartH->uart->ICR,UART_CR1_PEIE_IT);
        }
        
    }
    else
    {
        
    }
}

static void TX_IT_UART(UART_InitTypeDef *uartH)
{
    uartH->uart->TDR = uartH->TxRxData.pTxBuffer[uartH->TxRxData.TxCounter];
    uartH->TxRxData.TxCounter++;
    uartH->TxRxData.sizeTxBuffer--;
}

static void RX_IT_UART(UART_InitTypeDef *uartH)
{
    uartH->TxRxData.pRxBuffer[uartH->TxRxData.RxCounter] = (uint8_t)uartH->uart->RDR;
    uartH->TxRxData.RxCounter++;
    uartH->TxRxData.sizeRxBuffer--;
}

void uart_isrHandler( UART_InitTypeDef *uartH )
{
    if (BITCHECK(uartH->uart->ISR,UART_ISR_TXE_FLAG) != 0UL)
    {
        
        if (uartH->TxRxData.sizeTxBuffer == 0UL)
        {
            //Disable interrupt until Tx complete
            RESET_BIT(uartH->uart->CR1,UART_CR1_TXEIE_IT);
            //Call TxCallback
            uart_isrTxCallback(uartH);
        }
        else
        {
            TX_IT_UART(uartH);
        }
        
    }
    
    if (BITCHECK(uartH->uart->ISR,UART_ISR_RXNE_FLAG) != 0UL)
    {
        
        if (uartH->TxRxData.sizeRxBuffer == 0UL)
        {
            //Disable intenrrupt until Rx complete
            RESET_BIT(uartH->uart->CR1,UART_CR1_RXNEIE_IT);
            //Disable interrupt parity 
            RESET_BIT(uartH->uart->ICR,UART_CR1_PEIE_IT);

            //Call RxCallback
            uart_isrRxCallback(uartH);
        }
        else
        {
            RX_IT_UART(uartH);
        }
        
    }

    if ((BITCHECK(uartH->uart->ISR,UART_ISR_ORE_FLAG)) || (BITCHECK(uartH->uart->ISR,UART_ISR_PE_FLAG)) )
    {
        //Clear Overrun error flag
        SET_BIT(uartH->uart->ICR,3);
        //Clear Parity error flag 
        SET_BIT(uartH->uart->ICR,0);
        //Call ErrorCalback
        uart_isrErrorCallback(uartH);
    }
}



_weak void uart_isrTxCallback( UART_InitTypeDef *uartH )
{
    (void) uartH;
}

_weak void uart_isrRxCallback( UART_InitTypeDef *uartH )
{
    (void) uartH;
}

_weak void uart_isrErrorCallback( UART_InitTypeDef *uartH )
{
    (void) uartH;
}

