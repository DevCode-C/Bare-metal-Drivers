#include "types.h"
#include "registers.h"
#ifndef __UART__H
    #define __UART__H

    typedef struct __uart_transferData
    {
        volatile uint8_t* pTxBuffer;
        volatile uint16_t sizeTxBuffer;
        volatile uint16_t TxCounter;
        volatile uint8_t* pRxBuffer;
        volatile uint16_t sizeRxBuffer;
        volatile uint16_t RxCounter;
    }UART_TX_RX_Data;
    

    typedef struct __uart_config
    {
        USART_TypeDef*          uart;
        volatile uint32_t       BaudRate;
        volatile uint32_t       WordLength;
        volatile uint32_t       StopBits;
        volatile uint32_t       Parity;
        volatile uint32_t       HwFlowCtl;
        volatile uint32_t       TxRxMode;
        UART_TX_RX_Data         TxRxData;
    }UART_InitTypeDef;

    #define UART_WORDLENGTH_7B   (0x10000000UL)
    #define UART_WORDLENGTH_8B   (0x0)
    #define UART_WORDLENGTH_9B   (0x00001000UL)

    #define UART_STOPBITS_0_5   (0x0U)
    #define UART_STOPBITS_1   	(0x0U)
    #define UART_STOPBITS_1_5   (0x2U)
    #define UART_STOPBITS_2     (0x2U)

    #define UART_PARITY_NONE  	(0x0U)
    #define UART_PARITY_EVEN   	(0x2U)
    #define UART_PARITY_ODD     (0x3U)

    #define UART_HWCONTROL_NONE     (0x0U)
    #define UART_HWCONTROL_RTS   	(0x1U)
    #define UART_HWCONTROL_CTS      (0x2U)
    #define UART_HWCONTROL_RTS_CTS  (0x3U)

    #define UART_MODE_TX        (0x2U)
    #define UART_MODE_RX  	    (0x1U)
    #define UART_MODE_TX_RX     (0x3U)

    #define UART_OVERSAMPLING_8     (0x1U)
    #define UART_OVERSAMPLING_16    (0x0)


    //Configura el puerto uart seleccionado con la configuración descrita en la estructura uartH, 
    //esta tendrá los parámetros para setear la velocidad, bits de parada, paridad, 
    //tama;o de palabra y control de flujo
    void uart_configPort( UART_InitTypeDef *uartH );

    //Función callback que se manda llamar dentro de la función uart_configPort y que permite 
    //agregar código extra a la rutina de inicialización (activación de reloj configuración de puertos, etc ...)
    void uart_mspInit( UART_InitTypeDef *uartH );
        
    //manda la cantidad de caracteres especificados por len y referenciados en ptr a través 
    //del uart especificado, sin usar interrupciones. La función regresará solo cuando todos 
    //los caracteres se hayan mandado.
    void uart_sendBuffer( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len );

    //manda a través de interrupciones la cantidad de caracteres especificados por len y referenciados 
    //en ptr a través del uart especificado. La función solo inicia la transferencia, la interrupción 
    //se encargará de enviar los caracteres.
    void uart_sendBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len );

    //recibe mediante interrupciones la cantidad de caracteres especificados por len y referenciados 
    //en ptr a través del uart especificado. La función solo inicia la transferencia, la interrupción 
    //se encargará de recibir los caracteres cuando estos lleguen por el puerto.
    void uart_receiveBufferInt( UART_InitTypeDef *uartH, uint8_t *ptr, uint32_t len );

    //Procesa (manda o recibe) la información establecida por las funciones 
    //uart_sendBufferInt y  uart_receiveBufferInt ademas de limpiar la(s) bandera(s) de la interrupción 
    //que va a atender y llamar la función(es) callback(s) en donde el usuario escribirá su aplicación. 
    //Esta función solo debe ser llamada dentro de uno de los  vectores de interrupción UART
    void uart_isrHandler( UART_InitTypeDef *uartH );

    //esta función deberá ser escrita por el usuario en la aplicación, es llamada dentro de la función 
    //uart_isrHandler solo cuando todos los caracteres hayan sido enviados y debe estar declarada como 
    //weak dentro del driver uart
    void uart_isrTxCallback( UART_InitTypeDef *uartH );

    //esta función deberá ser escrita por el usuario en la aplicación, es llamada dentro de la función 
    //uart_isrHandler solo cuando todos los caracteres hayan sido recibidos y debe estar declarada 
    //como weak dentro del driver uart
    void uart_isrRxCallback( UART_InitTypeDef *uartH );

    void uart_isrErrorCallback( UART_InitTypeDef *uartH );


#endif