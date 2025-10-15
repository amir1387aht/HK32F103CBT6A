/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  usb_usartapp.c
* @brief:     Virtual Com Port Configuration
* @author:    AE Team
* @version:   V1.0.0/2023-11-10
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "hw_config.h"
#include "usb_prop.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define USART_RX_DATA_SIZE   512

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
USART_InitTypeDef USART_InitStructure;

uint8_t  USART_Rx_Buffer[USART_RX_DATA_SIZE];
extern uint32_t USART_Rx_ptr_in ;
extern uint32_t USART_Rx_ptr_out ;
extern uint32_t USART_Rx_length ;
extern uint8_t  USB_Tx_State ;
uint16_t USB_Tx_length;
uint16_t USB_Tx_ptr;

/* Extern variables ----------------------------------------------------------*/
extern LINE_CODING linecoding;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  EPxIN USB transfer complete ISR. Send pending data if any.
  * @retval none.
  */
void VCP_Data_InISR(void)
{
    VCP_SendRxBufPacketToUsb();
}

/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *         This parameter can be one of following parameters:
  *            @arg COM1
  *            @arg COM2
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *         contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void HK_EVAL_USARTInit(USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(VCP_USARTx_TX_GPIO_CLK | VCP_USARTx_RX_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(VCP_USARTx_CLK, ENABLE);

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = VCP_USARTx_TX_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(VCP_USARTx_TX_GPIO_PORT, &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = VCP_USARTx_RX_PIN;
    GPIO_Init(VCP_USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(VCP_USARTx, USART_InitStruct);

    /* Enable the USART Receive interrupt */
    USART_ITConfig(VCP_USARTx, USART_IT_RXNE, ENABLE);

    /* Enable USART */
    USART_Cmd(VCP_USARTx, ENABLE);
}


/**
  * @brief  configure the EVAL_COM1 with default values.
  * @retval None.
  */
void USART_Config_Default(void)
{
    /* EVAL_COM1 default configuration */

    /* EVAL_COM1 configured as follow:
          - BaudRate = 9600 baud
          - Word Length = 8 Bits
          - One Stop Bit
          - Parity Odd
          - Hardware flow control disabled
          - Receive and transmit enabled
    */
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_Odd;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure and enable the USART */
    HK_EVAL_USARTInit(&USART_InitStructure);

    /* Enable the USART Receive interrupt */
    USART_ITConfig(VCP_USARTx, USART_IT_RXNE, ENABLE);
}

/**
  * @brief  Configure the EVAL_COM1 according to the line coding structure.
  * @retval Configuration status
  *         - TRUE : configuration done with success
  *         - FALSE : configuration aborted.
  */
bool USART_Config(void)
{
    /* set the Stop bit*/
    switch (linecoding.format)
    {
        case 0:
            USART_InitStructure.USART_StopBits = USART_StopBits_1;
            break;

        case 1:
            USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
            break;

        case 2:
            USART_InitStructure.USART_StopBits = USART_StopBits_2;
            break;

        default :
        {
            USART_Config_Default();
            return (FALSE);
        }
    }

    /* set the parity bit*/
    switch (linecoding.paritytype)
    {
        case 0:
            USART_InitStructure.USART_Parity = USART_Parity_No;
            break;

        case 1:
            USART_InitStructure.USART_Parity = USART_Parity_Even;
            break;

        case 2:
            USART_InitStructure.USART_Parity = USART_Parity_Odd;
            break;

        default :
        {
            USART_Config_Default();
            return (FALSE);
        }
    }

    /*set the data type : only 8bits and 9bits is supported */
    switch (linecoding.datatype)
    {
        case 0x07:

            /* With this configuration a parity (Even or Odd) should be set */
            USART_InitStructure.USART_WordLength = USART_WordLength_8b;
            break;

        case 0x08:
            if (USART_InitStructure.USART_Parity == USART_Parity_No)
            {
                USART_InitStructure.USART_WordLength = USART_WordLength_8b;
            }
            else
            {
                USART_InitStructure.USART_WordLength = USART_WordLength_9b;
            }

            break;

        default :
        {
            USART_Config_Default();
            return (FALSE);
        }
    }

    USART_InitStructure.USART_BaudRate = linecoding.bitrate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    /* Configure and enable the USART */
    HK_EVAL_USARTInit(&USART_InitStructure);
    return (TRUE);
}

/**
  * @brief  send the received data from USB to the UART 0.
  * @param  data_buffer: data address.
  * @param  Nb_bytes: number of bytes to send.
  * @retval none.
  */
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes)
{
    uint32_t i;

    for (i = 0; i < Nb_bytes; i++)
    {
        USART_SendData(VCP_USARTx, *(data_buffer + i));

        while (USART_GetFlagStatus(VCP_USARTx, USART_FLAG_TXE) == RESET)
        {
        }
    }
}

/**
  * @brief  send data from USART_Rx_Buffer to the USB. Manage the segmentation
  *         into USB FIFO buffer. Commit one packet to the USB at each call.
  * @param  globals:
  *         - USB_Tx_State: transmit state variable
  *         - USART_Rx_Buffer: buffer of data to be sent
  *         - USART_Rx_length: amount of data (in bytes) ready to be sent
  *         - USART_Rx_ptr_out: index in USART_Rx_Buffer of the first data to send
  * @retval none.
  */
void VCP_SendRxBufPacketToUsb(void)
{
    uint16_t USB_Tx_ptr;
    uint16_t USB_Tx_length;

    if (USB_Tx_State == 1)
    {
        if (USART_Rx_length == 0)
        {
            USB_Tx_State = 0;
        }
        else
        {
            if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE)
            {
                USB_Tx_ptr = USART_Rx_ptr_out;
                USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
                USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;
                USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;
            }
            else
            {
                USB_Tx_ptr = USART_Rx_ptr_out;
                USB_Tx_length = USART_Rx_length;
                USART_Rx_ptr_out += USART_Rx_length;
                USART_Rx_length = 0;
            }

            UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
            SetEPTxCount(ENDP1, USB_Tx_length);
            SetEPTxValid(ENDP1);
        }
    }
}

/**
  * @brief  send data to USB.
  * @retval none.
  */
void Handle_USBAsynchXfer(void)
{
    if (USB_Tx_State != 1)
    {
        if (USART_Rx_ptr_out == USART_RX_DATA_SIZE)
        {
            USART_Rx_ptr_out = 0;
        }

        if (USART_Rx_ptr_out == USART_Rx_ptr_in)
        {
            USB_Tx_State = 0;
            return;
        }

        if (USART_Rx_ptr_out > USART_Rx_ptr_in) /* rollback */
        {
            USART_Rx_length = USART_RX_DATA_SIZE - USART_Rx_ptr_out;
        }
        else
        {
            USART_Rx_length = USART_Rx_ptr_in - USART_Rx_ptr_out;
        }

        if (USART_Rx_length > VIRTUAL_COM_PORT_DATA_SIZE)
        {
            USB_Tx_ptr = USART_Rx_ptr_out;
            USB_Tx_length = VIRTUAL_COM_PORT_DATA_SIZE;
            USART_Rx_ptr_out += VIRTUAL_COM_PORT_DATA_SIZE;
            USART_Rx_length -= VIRTUAL_COM_PORT_DATA_SIZE;
        }
        else
        {
            USB_Tx_ptr = USART_Rx_ptr_out;
            USB_Tx_length = USART_Rx_length;
            USART_Rx_ptr_out += USART_Rx_length;
            USART_Rx_length = 0;
        }

        USB_Tx_State = 1;
        UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
        SetEPTxCount(ENDP1, USB_Tx_length);
        SetEPTxValid(ENDP1);
    }
}

/**
  * @brief  send the received data from UART 0 to USB
  * @retval none.
  */
void USART_To_USB_Send_Data(void)
{
    if (linecoding.datatype == 7)
    {
        USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(VCP_USARTx) & 0x7F;
    }
    else if (linecoding.datatype == 8)
    {
        USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(VCP_USARTx);
    }

    USART_Rx_ptr_in++;

    /* To avoid buffer overflow */
    if (USART_Rx_ptr_in == USART_RX_DATA_SIZE)
    {
        USART_Rx_ptr_in = 0;
    }
}


/************************ (C) COPYRIGHT HK Microelectronics *****END OF FILE****/

