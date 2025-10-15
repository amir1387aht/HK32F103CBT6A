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
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t nTemp = 0;
CanTxMsg TxMessage = {0}, TxMessage1 = {0};
uint8_t KeyNumber = 0x0;
/* Private function prototypes -----------------------------------------------*/
void NVIC_Config(void);
void CAN_Config(void);
void LED_Display(uint8_t Ledstatus);
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* KEYs pin configuration */
    HK_EVAL_PBInit(BUTTON_KEY1, BUTTON_MODE_EXTI);
    HK_EVAL_PBInit(BUTTON_KEY2, BUTTON_MODE_EXTI);

    /* LEDs configuration */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    HK_EVAL_LEDInit(LED3);

    /* NVIC configuration */
    NVIC_Config();

    /* CANs configuration */
    CAN_Config();

    /* turn off all leds*/
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);
    HK_EVAL_LEDOff(LED3);

    while (1)
    {

    }
}

/**
  * @brief  Configures CAN.
  * @param  None
  * @retval None
  */
void CAN_Config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    CAN_InitTypeDef        CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

    /* Configure CAN IOs **********************************************/

    /* GPIOB, GPIOD and AFIO clocks enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA , ENABLE);

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

    /* CAN1 Periph clocks enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    /* Struct init*/
    CAN_StructInit(&CAN_InitStructure);

    /* CAN cell init */
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = DISABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;

    /* Baudrate = 500 Kbps */
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_5tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;
    CAN_InitStructure.CAN_Prescaler = 8;
    /*Initializes the CAN*/
    CAN_Init(CAN, &CAN_InitStructure);

    /* CAN filter init "FIFO0" */
    CAN_FilterInitStructure.CAN_FilterNumber = 0;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x6420;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure, CAN);

    /* CAN filter init "FIFO1" */
    CAN_FilterInitStructure.CAN_FilterNumber = 1;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdList;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x2460;
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO1;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure, CAN);

    /* Transmit Structure preparation */
    TxMessage.StdId = 0x321;
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = 1;

    /* Transmit Structure preparation 2*/
    TxMessage1.StdId = 0x123;
    TxMessage1.ExtId = 0x01;
    TxMessage1.RTR = CAN_RTR_DATA;
    TxMessage1.IDE = CAN_ID_STD;
    TxMessage1.DLC = 1;

    /* Enable FIFO 0 message pending Interrupt */
    CAN_ITConfig(CAN, CAN_IT_FMP0, ENABLE);

    /* Enable FIFO 1 message pending Interrupt */
    CAN_ITConfig(CAN, CAN_IT_FMP1, ENABLE);
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
    NVIC_InitStructure.NVIC_IRQChannel = CAN_RX1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQn;
    NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Turn ON/OFF the dedicated led
  * @param  Ledstatus: Led number from 1 to 3.
  * @retval None
  */
void LED_Display(uint8_t Ledstatus)
{
  /* Turn off all leds */
  HK_EVAL_LEDOff(LED1);
  HK_EVAL_LEDOff(LED2);
  HK_EVAL_LEDOff(LED3);
  
  switch(Ledstatus)
  {
    case(1): 
      HK_EVAL_LEDOn(LED1);
      break;
   
    case(2): 
      HK_EVAL_LEDOn(LED2);
      break;
 
    case(3): 
      HK_EVAL_LEDOn(LED3);
      break;

    case(4): 
      HK_EVAL_LEDOn(LED1);
    HK_EVAL_LEDOn(LED2);
    HK_EVAL_LEDOn(LED3);
      break;
    default:
      break;
  }
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
