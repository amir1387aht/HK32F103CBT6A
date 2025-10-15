/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*                     1.Initial version
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
#define countof(a)             (uint8_t)(sizeof(a) / sizeof(*(a)))
#define BUFFER_SIZE            (countof(CRCBuffer))
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
const uint32_t CRCBuffer[] =
{
    0x00001021, 0x20423063, 0x408450a5, 0x60c670e7, 0x9129a14a, 0xb16bc18c,
    0xd1ade1ce, 0xf1ef1231, 0x32732252, 0x52b54294, 0x72f762d6, 0x93398318,
    0xa35ad3bd, 0xc39cf3ff, 0xe3de2462, 0x34430420, 0x64e674c7, 0x44a45485,
    0xa56ab54b, 0x85289509, 0xf5cfc5ac, 0xd58d3653, 0x26721611, 0x063076d7,
    0x569546b4, 0xb75ba77a, 0x97198738, 0xf7dfe7fe, 0xc7bc48c4, 0x58e56886,
    0x78a70840, 0x18612802, 0xc9ccd9ed, 0xe98ef9af, 0x89489969, 0xa90ab92b,
    0x4ad47ab7, 0x6a961a71, 0x0a503a33, 0x2a12dbfd, 0xfbbfeb9e, 0x9b798b58,
    0xbb3bab1a, 0x6ca67c87, 0x5cc52c22, 0x3c030c60, 0x1c41edae, 0xfd8fcdec,
    0xad2abd0b, 0x8d689d49, 0x7e976eb6, 0x5ed54ef4, 0x2e321e51, 0x0e70ff9f,
    0xefbedfdd, 0xcffcbf1b, 0x9f598f78, 0x918881a9, 0xb1caa1eb, 0xd10cc12d,
    0xe16f1080, 0x00a130c2, 0x20e35004, 0x40257046, 0x83b99398, 0xa3fbb3da,
    0xc33dd31c, 0xe37ff35e, 0x129022f3, 0x32d24235, 0x52146277, 0x7256b5ea,
    0x95a88589, 0xf56ee54f, 0xd52cc50d, 0x34e224c3, 0x04817466, 0x64475424,
    0x4405a7db, 0xb7fa8799, 0xe75ff77e, 0xc71dd73c, 0x26d336f2, 0x069116b0,
    0x76764615, 0x5634d94c, 0xc96df90e, 0xe92f99c8, 0xb98aa9ab, 0x58444865,
    0x78066827, 0x18c008e1, 0x28a3cb7d, 0xdb5ceb3f, 0xfb1e8bf9, 0x9bd8abbb,
    0x4a755a54, 0x6a377a16, 0x0af11ad0, 0x2ab33a92, 0xed0fdd6c, 0xcd4dbdaa,
    0xad8b9de8, 0x8dc97c26, 0x5c644c45, 0x3ca22c83, 0x1ce00cc1, 0xef1fff3e,
    0xdf7caf9b, 0xbfba8fd9, 0x9ff86e17, 0x7e364e55, 0x2e933eb2, 0x0ed11ef0
};

__IO uint32_t ComputedCRC = 0;
uint32_t ExpectedCRC = 0xEBF5058C; /* The expected CRC value of CRCBuffer using the
                               polynomial X32 + X26 + X23 + X22 + X16 + X12 + X11 +
                                              X10 +X8 + X7 + X5 + X4 + X2+ X + 1 */

/* Private function prototypes -----------------------------------------------*/
static void CRC_Config(void);

/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Initialize Leds mounted on HK32F103xxxxA app base board */
    HK_EVAL_LEDInit(LED1);
    HK_EVAL_LEDInit(LED2);
    CRC_Config();

    /* Compute the CRC value of the 8-bit buffer: CRCBuffer */
    ComputedCRC = CRC_CalcBlockCRC((uint32_t *)CRCBuffer, BUFFER_SIZE);

    /* turn off led1 and led2 */
    HK_EVAL_LEDOff(LED1);
    HK_EVAL_LEDOff(LED2);

    /* Check if the computed CRC matches the expected one */
    if (ComputedCRC != ExpectedCRC)
    {
        /* Turn on LED1 */
        HK_EVAL_LEDOn(LED1);
    }
    else
    {
        /* Turn on LED2 */
        HK_EVAL_LEDOn(LED2);
    }

    /* Infinite loop */
    while (1)
    {
    }
}

/**
  * @brief  CRC Configure
  * @param  None
  * @retval None
  */
static void CRC_Config(void)
{
    /* Enable CRC AHB clock interface */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

    /* DeInit CRC peripheral */
    CRC_DeInit();

    /* Set the initial value of the CRC_DR register to 0*/
    CRC_CalcCRC(0xFFFFFFFF);
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
