/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hw_config.c
* @brief:     Hardware Configuration & Setup.
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
extern __IO uint8_t PrevXferComplete;
EXTI_InitTypeDef EXTI_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static void IntToUnicode (uint32_t value, uint8_t *pbuf, uint8_t len);
static void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures Main system clocks & power.
  * @retval None.
  */
void Set_System(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /*Configure USB DM/DP pins*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*Enable all GPIOs Clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ALLGPIO, ENABLE);

#if 0
    
    /* USB_DISCONNECT used as USB pull-up */
    GPIO_InitStructure.GPIO_Pin = USB_DISCONNECT_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_Init(USB_DISCONNECT, &GPIO_InitStructure);

    /* Enable the USB disconnect GPIO clock */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);
#endif

#ifdef USB_LOW_PWR_MGMT_SUPPORT

    /*Configure the EXTI line 18 connected internally to the USB IP*/
    EXTI_ClearITPendingBit(EXTI_Line18);
    EXTI_InitStructure.EXTI_Line = EXTI_Line18;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
#endif  /* USB_LOW_PWR_MGMT_SUPPORT */
}

/**
  * @brief  Configures USB Clock input (48MHz).
  * @retval None.
  */
void Set_USBClock(void)
{
    /* Select USBCLK source */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
    
    /* Enable the USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/**
  * @brief  Restores system clocks and power while exiting suspend mode.
  * @retval None.
  */
void Leave_LowPowerMode(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->Current_Configuration != 0)
    {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
    else
    {
        bDeviceState = ATTACHED;
    }

    /* Reset SLEEPDEEP bit of Cortex System Control Register */
    SCB->SCR &= (uint32_t)~((uint32_t)(SCB_SCR_SLEEPDEEP_Msk | SCB_SCR_SLEEPONEXIT_Msk));

    /*Enable SystemCoreClock*/
    SystemInit();
    Set_USBClock();
}

/**
  * @brief  Configures the USB interrupts.
  * @retval None.
  */
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

#ifdef USB_LOW_PWR_MGMT_SUPPORT
    
    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_WAKEUP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif /* USB_LOW_PWR_MGMT_SUPPORT */
}

/**
  * @brief  Software Connection/Disconnection of USB Cable.
  * @param  NewState: new state.
  * @retval None
  */
void USB_Cable_Config(FunctionalState NewState)
{
#if 0

    if (NewState != DISABLE)
    {
        GPIO_ResetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }
    else
    {
        GPIO_SetBits(USB_DISCONNECT, USB_DISCONNECT_PIN);
    }

#endif
}

/**
  * @brief  Gets Pointer Data
  * @retval None.
  */
void Joy_Emul(void)
{
    uint8_t Mouse_Buffer[4] = {0, 0, 0, 0};
    uint8_t X = 0, Y = 0;
    static uint8_t Sens = 0;
    static uint8_t Step = 0;

    Delay(0x0FFFF);

    if (Step == 35)
    {
        Step = 0;
        Sens++;
    }

    if (Sens == 0)
    {
        X = Step++;
        Y = 0;
    }

    if (Sens == 1)
    {
        Y = Step++;
        X = 0;
    }

    if (Sens == 2)
    {
        X = 256 - Step++;
        Y = 0;
    }

    if (Sens == 3)
    {
        Y = 256 - Step++;
        X = 0;
    }

    if (Sens == 4)
    {
        Sens = 0;
        X = 0;
        Y = 0;
    }

    Mouse_Buffer[0] = 0;
    Mouse_Buffer[1] = X;
    Mouse_Buffer[2] = Y;
    Mouse_Buffer[3] = 0;

    /* Reset the control token to inform upper layer that a transfer is ongoing */
    PrevXferComplete = 0;
    
    /* Copy mouse position info in ENDP1 Tx Packet Memory Area*/
    USB_SIL_Write(EP1_IN, Mouse_Buffer, 4);
    
    /* Enable endpoint for transmission */
    SetEPTxValid(ENDP1);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
static void Delay(__IO uint32_t nTime)
{
    for (; nTime != 0; nTime--)
    {
    }
}

/**
  * @brief  Create the serial number string descriptor.
  * @retval None.
  */
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(uint32_t*)ID1;
    Device_Serial1 = *(uint32_t*)ID2;
    Device_Serial2 = *(uint32_t*)ID3;

    Device_Serial0 += Device_Serial2;

    if (Device_Serial0 != 0)
    {
        IntToUnicode (Device_Serial0, &Joystick_StringSerial[2], 8);
        IntToUnicode (Device_Serial1, &Joystick_StringSerial[18], 4);
    }
}

/**
  * @brief  Convert Hex 32Bits value into char.
  * @retval None.
  */
static void IntToUnicode(uint32_t value, uint8_t *pbuf, uint8_t len)
{
    uint8_t idx = 0;

    for ( idx = 0 ; idx < len ; idx ++)
    {
        if ( ((value >> 28)) < 0xA )
        {
            pbuf[ 2 * idx] = (value >> 28) + '0';
        }
        else
        {
            pbuf[2 * idx] = (value >> 28) + 'A' - 10;
        }

        value = value << 4;

        pbuf[ 2 * idx + 1] = 0;
    }
}
/************************ (C) COPYRIGHT HK Microchip *****END OF FILE****/

