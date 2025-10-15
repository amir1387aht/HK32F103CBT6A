/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.c
* @brief:     Main program body
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "hw_config.h" 
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_pwr.h"
#include "dfu_mal.h"

/** @addtogroup HK32F103xxxxA_StdPeriph_Examples
  * @{
  */

/** @addtogroup Device_Firmware_Upgrade
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
typedef  void (*pFunction)(void);

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t DeviceState;
uint8_t DeviceStatus[6];
pFunction Jump_To_Application;
uint32_t JumpAddress;

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void KEY1_Config(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
    /* BUTTON_KEY1 Config */
    KEY1_Config();

    /* Check if the Key push-button on EVAL Board is pressed */
    if (HK_EVAL_PBGetState(BUTTON_KEY1) != 0x01)
    {   
        if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)    /* Test if user code is programmed starting from address 0x8005000 */
        { 
            /* Jump to user application */
            JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
            Jump_To_Application = (pFunction) JumpAddress;
            
            /* Initialize user application's Stack Pointer */
            __set_MSP(*(__IO uint32_t*) ApplicationAddress);
            Jump_To_Application();
        }
    } /* Otherwise enters DFU mode to allow user to program his application */

    /* Enter DFU mode */
    DeviceState = STATE_dfuERROR;
    DeviceStatus[0] = STATUS_ERRFIRMWARE;
    DeviceStatus[4] = DeviceState;

    Set_System();
    Set_USBClock();
    USB_Init();  
    
    /* Main loop */
    while (1)
    {
    }
}

/**
  * @brief  Button 1 Configure as pull-up input .
  * @param  NONE.
  * @retval NONE.
  */
void KEY1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    /* Enable the BUTTON Clock */
    RCC_APB2PeriphClockCmd(KEY1_BUTTON_GPIO_CLK | RCC_APB2Periph_AFIO, ENABLE);

    /* Configure Button pin as pull-up input */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = KEY1_BUTTON_PIN;
    GPIO_Init(KEY1_BUTTON_GPIO_PORT, &GPIO_InitStructure);

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

    /* Infinite loop */
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

