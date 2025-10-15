/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
EXTI_InitTypeDef   EXTI_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static void EXTI0_Config(void);
static void EXTI1_Config(void);

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{     
    /* Initialize LED2 */       
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDOff(LED1);

    /* Configure PA.00 in interrupt mode */
    EXTI0_Config();

    /* Configure PB.09 or PG.08 in interrupt mode */
    EXTI1_Config();
  
    /* Generate software interrupt: simulate a Rising edge applied on EXTI0 line */
    EXTI_GenerateSWInterrupt(EXTI_Line0);
            
    while (1)
    {
    }
}

/**
  * @brief  Configure PA.00 in interrupt mode
  * @param  None
  * @retval None
  */
static void EXTI0_Config(void)
{
  /* Enable GPIOA clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
  /* Configure GPIO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* Connect EXTI0 Line to PA.00 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

  /* Configure EXTI0 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Configure PA.01 in interrupt mode
  * @param  None
  * @retval None
  */
void EXTI1_Config(void)
{
  /* Enable GPIOB clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

  /* Configure GPIO */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Enable AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

  /* Connect EXTI1 Line to PA.01 pin */
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);

  /* Configure EXTI9 line */
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable and set EXTI9_5 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
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


