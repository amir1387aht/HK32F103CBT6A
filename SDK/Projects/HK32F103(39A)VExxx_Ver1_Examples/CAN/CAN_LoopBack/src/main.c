/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*              1.Initial version
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
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t ret = 0; /* for return of the interrupt handling */
volatile TestStatus TestRx;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Configuration(void);
TestStatus CAN_Polling(void);
TestStatus CAN_Interrupt(void);
void GPIO_Config(void);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* system clock configuration */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

    /* LEDs configuration */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);

    /* GPIOs configuration */
    GPIO_Config();

    /* NVIC configuration */
    NVIC_Configuration();

    /* turn off led1 and led2*/
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    /* CAN Clock configuration */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    /* CAN transmit at 125Kb/s and receive by polling in loopback mode */
    TestRx = CAN_Polling();

    if (TestRx == FAILED)
    {
        HK_EVAL_LEDOff(LED1);
    }
    else
    {
        HK_EVAL_LEDOn(LED1);        
    }
    /* CAN transmit at 500Kb/s and receive by interrupt in loopback mode */
    TestRx = CAN_Interrupt();

    if (TestRx == FAILED)
    {
        HK_EVAL_LEDOff(LED2);
    }
    else
    {
        HK_EVAL_LEDOn(LED2);      
    }

    while (1)
    {
    }
}

/**
  * @brief  Configures the CAN, transmit and receive by polling
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */
TestStatus CAN_Polling(void)
{
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    CanTxMsg TxMessage;
    CanRxMsg RxMessage;
    uint32_t i = 0;
    uint8_t TransmitMailbox = 0;

    /* CAN register init */
    CAN_DeInit(CAN);
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;

    /* Baudrate = 125kbps*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStructure.CAN_Prescaler = 4;
    CAN_Init(CAN, &CAN_InitStructure);

    /* CAN filter init */
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

    /* transmit */
    TxMessage.StdId = 0x11;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 2;
    TxMessage.Data[0] = 0xCA;
    TxMessage.Data[1] = 0xFE;
    TransmitMailbox = CAN_Transmit(CAN, &TxMessage);
    i = 0;

    while ((CAN_TransmitStatus(CAN, TransmitMailbox) != CANTXOK) && (i != 0xFFFF))
    {
        i++;
    }

    i = 0;

    while ((CAN_MessagePending(CAN, CAN_FIFO0) < 1) && (i != 0xFFFF))
    {
        i++;
    }

    /* receive */
    RxMessage.StdId = 0x00;
    RxMessage.IDE = CAN_ID_STD;
    RxMessage.DLC = 0;
    RxMessage.Data[0] = 0x00;
    RxMessage.Data[1] = 0x00;
    CAN_Receive(CAN, CAN_FIFO0, &RxMessage);

    if (RxMessage.StdId != 0x11)
    {
        return FAILED;
    }

    if (RxMessage.IDE != CAN_ID_STD)
    {
        return FAILED;
    }

    if (RxMessage.DLC != 2)
    {
        return FAILED;
    }

    if ((RxMessage.Data[0] << 8 | RxMessage.Data[1]) != 0xCAFE)
    {
        return FAILED;
    }

    return PASSED; /* Test Passed */
}

/**
  * @brief  Configures the CAN, transmit and receive using interrupt.
  * @param  None
  * @retval PASSED if the reception is well done, FAILED in other case
  */
TestStatus CAN_Interrupt(void)
{
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;
    CanTxMsg TxMessage;
    uint32_t i = 0;

    /* CAN register init */
    CAN_DeInit(CAN);
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_LoopBack;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

    /* Baudrate = 500 Kbps */
    CAN_InitStructure.CAN_BS1 = CAN_BS1_4tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStructure.CAN_Prescaler = 1;
    CAN_Init(CAN, &CAN_InitStructure);

    /* CAN filter init */
    CAN_FilterInitStructure.CAN_FilterNumber = 1;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure, CAN);

    /* CAN FIFO0 message pending interrupt enable */
    CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE);

    /* transmit 1 message */
    TxMessage.StdId = 0;
    TxMessage.ExtId = 0x1234;
    TxMessage.IDE = CAN_ID_EXT;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.DLC = 2;
    TxMessage.Data[0] = 0xDE;
    TxMessage.Data[1] = 0xCA;
    CAN_Transmit(CAN, &TxMessage);

    /* initialize the value that will be returned */
    ret = 0xFF;

    /* receive message with interrupt handling */
    i = 0;

    while ((ret == 0xFF) && (i < 0xFFF))
    {
        i++;
    }

    if (i == 0xFFF)
    {
        ret = 0;
    }

    /* disable interrupt handling */
    CAN_ITConfig(CAN, CAN_IT_FMP0, DISABLE);
    return (TestStatus)ret;
}

/**
  * @brief  Configures GPIO.
  * @param  None
  * @retval None
  */
void GPIO_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* GPIOA clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_AFIO, ENABLE);

    /* Configure CAN RX pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Configure CAN TX pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
  * @brief  Configures the NVIC and Vector Table base address.
  * @param  None
  * @retval None
  */
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable CAN RX0 interrupt IRQ channel */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
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
