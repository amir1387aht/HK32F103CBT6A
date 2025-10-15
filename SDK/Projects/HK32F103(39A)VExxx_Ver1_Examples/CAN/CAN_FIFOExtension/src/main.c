/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hk32f103xxxxa_eval.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup _template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
CanTxMsg TxMessage = {0};
CanRxMsg RxMessage = {0};
extern __IO uint8_t MsgReceived;
uint8_t KeyNumber = 0x0;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Config(void);
void CAN_Config(void);
void Delay(void);
void GPIO_Config(void);
static void Printf_TransmittedMsg(uint8_t PushNumber);
void Printf_ReceivedMsg(void);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* KEY pin configuration */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_GPIO);

    /* USART configuration */
    USART_InitTypeDef USART_InitStruct;
		
    USART_StructInit(&USART_InitStruct);
    USART_InitStruct.USART_BaudRate = 115200;
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    HK_EVAL_COMInit(COM1, &USART_InitStruct);

    /* NVIC configuration */
    NVIC_Config();

    /* CANs configuration */
    CAN_Config();
    
    while(1)
    {
        while(HK_EVAL_PBGetState(BUTTON_KEY1) == RESET)
        {
            if(KeyNumber == 41) 
            {    
                KeyNumber = 0;
            }
            
            Printf_TransmittedMsg(KeyNumber);
            KeyNumber++;
            Delay();

            while(HK_EVAL_PBGetState(BUTTON_KEY1) != SET)
            {
            }
        }

        if (MsgReceived != 0)
        {
            Printf_ReceivedMsg();
            MsgReceived = 0;
        }
    }
}

/**
  * @brief  Configures CAN1 and CAN2.
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;

    /* Configure CAN **********************************************/

    /* GPIOB, GPIOD and AFIO clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA, ENABLE);

    /* Configure CAN RX pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure CAN TX pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure CAN **************************************************/

    /* CAN Periph clocks enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    /* Struct init*/
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = ENABLE;
    CAN_InitStructure.CAN_TXFP = ENABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

    /* Baudrate = 500 Kbps */
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStructure.CAN_Prescaler = 8;
    /*Initializes the CAN*/
    CAN_Init(CAN, &CAN_InitStructure);

    /* CAN1 filter init */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure, CAN);

    /* Transmit */
    TxMessage.StdId = 0x321;
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 1;

    /* IT Configuration for CAN */
    CAN_ITConfig(CAN, CAN_IT_FF0, ENABLE);

    /* IT Configuration for CAN */
    CAN_ITConfig(CAN, CAN_IT_FF1, ENABLE);
}

/**
  * @brief  Printf transmitted msg
  * @param  None.
  * @retval None
  */
static void Printf_TransmittedMsg(uint8_t PushNumber)
{
    uint8_t dataindex = 0;
    uint8_t TxMessages[6] = { 0, 1, 2, 3, 4, 5 };

    for (dataindex = 0 ; dataindex < 6 ; dataindex++)
    {
        TxMessage.Data[0] = (uint8_t)(TxMessages[dataindex] + (6 * PushNumber));
        CAN_Transmit(CAN, &TxMessage);
        printf("Send Message Num%d = %d     \r\n", dataindex + 1, TxMessage.Data[0] );
    }
}

/**
  * @brief  Printf received msg
  * @param  None.
  * @retval None
  */
void Printf_ReceivedMsg(void)
{
    uint8_t dataindex = 0;

    for (dataindex = 0 ; dataindex < 6 ; dataindex++)
    {
        if (dataindex < 3)
        {
            /* read data from CAN FIFO 0 */
            CAN_Receive(CAN, CAN_FIFO0, &RxMessage);
        }
        else
        {
            /* read data from CAN FIFO 1 */
            CAN_Receive(CAN, CAN_FIFO1, &RxMessage);
        }

        printf("\r\n Message received Number %d : \r\n", dataindex + 1);
        printf("\r\n ID-0x%x: H%02x   \r\n", RxMessage.StdId, RxMessage.Data[0]);
    }
}

/**
  * @brief  Configures the NVIC for CAN.
  * @param  None
  * @retval None
  */
void NVIC_Config(void)
{
    NVIC_InitTypeDef  NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = CAN_RX1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Delay
  * @param  None
  * @retval None
  */
void Delay(void)
{
    uint16_t nTime = 0x0000;

    for (nTime = 0; nTime < 0xFFF; nTime++)
    {
    }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /*  Printf   */
    USART_SendData(USART1, (unsigned char) ch);

    while(USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
    {
    }
    return (ch);
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */
