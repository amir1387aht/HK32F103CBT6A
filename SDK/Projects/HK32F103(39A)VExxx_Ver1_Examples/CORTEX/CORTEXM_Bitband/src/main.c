/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-11-12
*                     1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"


/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup Cortex_BitBand
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
#define RAM_BASE       0x20000000
#define RAM_BB_BASE    0x22000000
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define  Var_ResetBit_BB(VarAddr, BitNumber)    \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 0)

#define Var_SetBit_BB(VarAddr, BitNumber)       \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)) = 1)

#define Var_GetBit_BB(VarAddr, BitNumber)       \
          (*(__IO uint32_t *) (RAM_BB_BASE | ((VarAddr - RAM_BASE) << 5) | ((BitNumber) << 2)))

/* Private variables ---------------------------------------------------------*/

__IO uint32_t Var, VarAddr = 0, VarBitValue = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    Var = 0x00005AA5;

    /* A mapping formula shows how to reference each word in the alias region to a
       corresponding bit in the bit-band region.
       The mapping formula is:
        bit_word_addr = bit_band_base + (byte_offset x 32) + (bit_number + 4)

    where:
       - bit_word_addr: is the address of the word in the alias memory region that
                        maps to the targeted bit.
       - bit_band_base is the starting address of the alias region
       - byte_offset is the number of the byte in the bit-band region that contains
         the targeted bit
       - bit_number is the bit position (0-7) of the targeted bit */

    /* Get the variable address --------------------------------------------------*/
    VarAddr = (uint32_t)&Var;

    /* Modify variable bit using bit-band access ---------------------------------*/

    /* Modify Var variable bit 0 -----------------------------------------------*/
    Var_ResetBit_BB(VarAddr, 0);  /* Var = 0x00005AA4 */
    Var_SetBit_BB(VarAddr, 0);    /* Var = 0x00005AA5 */

    /* Modify Var variable bit 11 ----------------------------------------------*/
    Var_ResetBit_BB(VarAddr, 11);             /* Var = 0x000052A5 */

    /* Get Var variable bit 11 value */
    VarBitValue = Var_GetBit_BB(VarAddr, 11); /* VarBitValue = 0x00000000 */
    Var_SetBit_BB(VarAddr, 11);               /* Var = 0x00005AA5 */

    /* Get Var variable bit 11 value */
    VarBitValue = Var_GetBit_BB(VarAddr, 11);    /* VarBitValue = 0x00000001 */

    /* Modify Var variable bit 31 ----------------------------------------------*/
    Var_SetBit_BB(VarAddr, 31);               /* Var = 0x80005AA5 */

    /* Get Var variable bit 31 value */
    VarBitValue = Var_GetBit_BB(VarAddr, 31); /* VarBitValue = 0x00000001 */
    Var_ResetBit_BB(VarAddr, 31);             /* Var = 0x00005AA5 */

    /* Get Var variable bit 31 value */
    VarBitValue = Var_GetBit_BB(VarAddr, 31); /* VarBitValue = 0x00000000 */

    while (1)
    {
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
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    while (1)
    {
    }
}

#endif

/**
  * @}
  */

/**
  * @}
  */

