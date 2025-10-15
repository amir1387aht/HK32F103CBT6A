/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval.c
* @brief:     This file provides
*             - set of firmware functions to manage Leds, push-button and COM ports
*             available on HK32F103xxxxA evaluation board from Hangshun Chip.
* @author:    AE Team
* @version:   V1.0.0/2023-10-31
*             1.Initial version
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_eval.h"
#include "hk32f103xxxxa_spi.h"
#include "hk32f103xxxxa_i2c.h"
#include "hk32f103xxxxa_sdio.h"
#include "hk32f103xxxxa_dma.h"

/** @addtogroup HK32F103xxxxA_EVAL
  * @{
  */ 
      
/** @defgroup  HK32F103xxxxA_EVAL_LOW_LEVEL  
  * @brief This file provides firmware functions to manage Leds, push-buttons, 
  *        COM ports, SD card on SDIO, serial flash (sFLASH) and serial EEPROM (HK24C) 
  *         available on HK32F103xxxxA-EVAL evaluation board from Hangshun chip.
  * @{
  */ 

/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Private_TypesDefinitions
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Private_Defines
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Private_Macros
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Private_Variables
  * @{
  */  
GPIO_TypeDef* GPIO_PORT[LEDn] = {LED1_GPIO_PORT, LED2_GPIO_PORT, LED3_GPIO_PORT};
const uint16_t GPIO_PIN[LEDn] = {LED1_PIN, LED2_PIN, LED3_PIN};
const uint32_t GPIO_CLK[LEDn] = {LED1_GPIO_CLK, LED2_GPIO_CLK, LED3_GPIO_CLK};

GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {KEY1_BUTTON_GPIO_PORT, KEY2_BUTTON_GPIO_PORT, 
                                      KEY3_BUTTON_GPIO_PORT }; 

const uint16_t BUTTON_PIN[BUTTONn] = {KEY1_BUTTON_PIN, KEY2_BUTTON_PIN, 
                                      KEY3_BUTTON_PIN}; 

const uint32_t BUTTON_CLK[BUTTONn] = {KEY1_BUTTON_GPIO_CLK, KEY2_BUTTON_GPIO_CLK,
                                      KEY3_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[BUTTONn] = {KEY1_BUTTON_EXTI_LINE,
                                            KEY2_BUTTON_EXTI_LINE, 
                                            KEY3_BUTTON_EXTI_LINE};

const uint16_t BUTTON_PORT_SOURCE[BUTTONn] = {KEY1_BUTTON_EXTI_PORT_SOURCE,
                                              KEY2_BUTTON_EXTI_PORT_SOURCE, 
                                              KEY3_BUTTON_EXTI_PORT_SOURCE};
								 
const uint16_t BUTTON_PIN_SOURCE[BUTTONn] = {KEY1_BUTTON_EXTI_PIN_SOURCE,
                                             KEY2_BUTTON_EXTI_PIN_SOURCE, 
                                             KEY3_BUTTON_EXTI_PIN_SOURCE}; 

const uint16_t BUTTON_IRQn[BUTTONn] = {KEY1_BUTTON_EXTI_IRQn, KEY2_BUTTON_EXTI_IRQn, 
                                       KEY3_BUTTON_EXTI_IRQn};

USART_TypeDef* COM_USART[COMn] = {EVAL_COM1}; 

GPIO_TypeDef* COM_TX_PORT[COMn] = {EVAL_COM1_TX_GPIO_PORT};
 
GPIO_TypeDef* COM_RX_PORT[COMn] = {EVAL_COM1_RX_GPIO_PORT};
 
const uint32_t COM_USART_CLK[COMn] = {EVAL_COM1_CLK};

const uint32_t COM_TX_PORT_CLK[COMn] = {EVAL_COM1_TX_GPIO_CLK};
 
const uint32_t COM_RX_PORT_CLK[COMn] = {EVAL_COM1_RX_GPIO_CLK};

const uint16_t COM_TX_PIN[COMn] = {EVAL_COM1_TX_PIN};

const uint16_t COM_RX_PIN[COMn] = {EVAL_COM1_RX_PIN};

DMA_InitTypeDef   sEEDMA_InitStructure;

/**
  * @}
  */ 


/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Private_FunctionPrototypes
  * @{
  */ 

/**
  * @}
  */ 


/** @defgroup HK32F103xxxxA_EVAL_LOW_LEVEL_Private_Functions
  * @{
  */ 

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured. 
  *         This parameter can be one of following parameters:
  *    @arg LED1
  *    @arg LED2
  *    @arg LED3
  * @retval None
  */
void HK_EVAL_LEDInit(Led_TypeDef Led)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /* Enable the GPIO_LED Clock */
    RCC_APB2PeriphClockCmd(GPIO_CLK[Led], ENABLE);

    /* Configure the GPIO_LED pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN[Led];
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIO_PORT[Led], &GPIO_InitStructure);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on. 
  *         This parameter can be one of following parameters:
  *    @arg LED1
  *    @arg LED2
  *    @arg LED3
  * @retval None
  */
void HK_EVAL_LEDOn(Led_TypeDef Led)
{
    GPIO_PORT[Led]->BRR = GPIO_PIN[Led];     
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off. 
  *         This parameter can be one of following parameters:
  *    @arg LED1
  *    @arg LED2
  *    @arg LED3 
  * @retval None
  */
void HK_EVAL_LEDOff(Led_TypeDef Led)
{
    GPIO_PORT[Led]->BSRR = GPIO_PIN[Led];    
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled. 
  *         This parameter can be one of following parameters:
  *    @arg LED1
  *    @arg LED2
  *    @arg LED3  
  * @retval None
  */
void HK_EVAL_LEDToggle(Led_TypeDef Led)
{
    GPIO_PORT[Led]->ODR ^= GPIO_PIN[Led];
}

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *         This parameter can be one of following parameters:   
  *    @arg BUTTON_KEY1: Key Push Button
  *    @arg BUTTON_KEY2: Key Push Button
  *    @arg BUTTON_KEY3: Key Push Button
  * @param  Button_Mode: Specifies Button mode.
  *         This parameter can be one of following parameters:   
  *    @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *    @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *         generation capability  
  * @retval None
  */
void HK_EVAL_PBInit(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* Enable the BUTTON Clock */
    RCC_APB2PeriphClockCmd(BUTTON_CLK[Button] | RCC_APB2Periph_AFIO, ENABLE);

    /* Configure Button pin as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
    GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

    /* Configure Button EXTI mode */
    if (Button_Mode == BUTTON_MODE_EXTI)
    {
        /* Connect Button EXTI Line to Button GPIO Pin */
        GPIO_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);

        /* Configure Button EXTI line */
        EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;

        /* Configure Button EXTI trigger edge */
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        /* Enable and set Button EXTI Interrupt to the lowest priority */
        NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

        NVIC_Init(&NVIC_InitStructure); 
    }
}

/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *         This parameter can be one of following parameters:      
  *    @arg BUTTON_KEY1: Key1 Push Button
  *    @arg BUTTON_KEY2: Key2 Push Button
  *    @arg BUTTON_KEY3: Key3 Push Button
  * @retval The Button GPIO pin value.
  */
uint32_t HK_EVAL_PBGetState(Button_TypeDef Button)
{
    return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

/**
  * @brief  Configures COM port.
  * @param  COM: Specifies the COM port to be configured.
  *         This parameter can be one of following parameters:    
  *    @arg COM1  
  * @param  USART_InitStruct: pointer to a USART_InitTypeDef structure that
  *         contains the configuration information for the specified USART peripheral.
  * @retval None
  */
void HK_EVAL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable GPIO clock */
    RCC_APB2PeriphClockCmd(COM_TX_PORT_CLK[COM] | COM_RX_PORT_CLK[COM] | RCC_APB2Periph_AFIO, ENABLE);

    /* Enable UART clock */
    RCC_APB2PeriphClockCmd(COM_USART_CLK[COM], ENABLE); 

    /* Configure USART Tx as alternate function push-pull */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = COM_TX_PIN[COM];
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(COM_TX_PORT[COM], &GPIO_InitStructure);

    /* Configure USART Rx as input floating */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = COM_RX_PIN[COM];
    GPIO_Init(COM_RX_PORT[COM], &GPIO_InitStructure);

    /* USART configuration */
    USART_Init(COM_USART[COM], USART_InitStruct);

    /* Enable USART */
    USART_Cmd(COM_USART[COM], ENABLE);
}

/**
  * @brief  DeInitializes the SDIO interface.
  * @param  None
  * @retval None
  */
void SD_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /*!< Disable SDIO Clock */
    SDIO_ClockCmd(DISABLE);

    /*!< Set Power State to OFF */
    SDIO_SetPowerState(SDIO_PowerState_OFF);

    /*!< DeInitializes the SDIO peripheral */
    SDIO_DeInit();

    /*!< Disable the SDIO AHB Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, DISABLE);

    /*!< Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*!< Configure PD.02 CMD line */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the SD Card and put it into StandBy State (Ready for 
  *         data transfer).
  * @param  None
  * @retval None
  */
void SD_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    /*!< GPIOC and GPIOD Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);

    /*!< Configure PC.08, PC.09, PC.10, PC.11, PC.12 pin: D0, D1, D2, D3, CLK pin */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*!< Configure PD.02 CMD line */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*!< Enable the SDIO AHB Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_SDIO, ENABLE);

    /*!< Enable the DMA2 Clock */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
}

/**
  * @brief  Configures the DMA2 Channel4 for SDIO Tx request.
  * @param  BufferSRC: pointer to the source buffer
  * @param  BufferSize: buffer size
  * @retval None
  */
void SD_LowLevel_DMA_TxConfig(uint32_t *BufferSRC, uint32_t BufferSize)
{
    DMA_InitTypeDef DMA_InitStructure;

    DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

    /*!< DMA2 Channel4 disable */
    DMA_Cmd(DMA2_Channel4, DISABLE);

    /*!< DMA2 Channel4 Config */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SDIO_FIFO_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)BufferSRC;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel4, &DMA_InitStructure);

    /*!< DMA2 Channel4 enable */
    DMA_Cmd(DMA2_Channel4, ENABLE);  
}

/**
  * @brief  Configures the DMA2 Channel4 for SDIO Rx request.
  * @param  BufferDST: pointer to the destination buffer
  * @param  BufferSize: buffer size
  * @retval None
  */
void SD_LowLevel_DMA_RxConfig(uint32_t *BufferDST, uint32_t BufferSize)
{
    DMA_InitTypeDef DMA_InitStructure;

    DMA_ClearFlag(DMA2_FLAG_TC4 | DMA2_FLAG_TE4 | DMA2_FLAG_HT4 | DMA2_FLAG_GL4);

    /*!< DMA2 Channel4 disable */
    DMA_Cmd(DMA2_Channel4, DISABLE);

    /*!< DMA2 Channel4 Config */
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)SDIO_FIFO_ADDRESS;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)BufferDST;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BufferSize / 4;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA2_Channel4, &DMA_InitStructure);

    /*!< DMA2 Channel4 enable */
    DMA_Cmd(DMA2_Channel4, ENABLE); 
}

/**
  * @brief  Returns the DMA End Of Transfer Status.
  * @param  None
  * @retval DMA SDIO Channel Status.
  */
uint32_t SD_DMAEndOfTransferStatus(void)
{
    return (uint32_t)DMA_GetFlagStatus(DMA2_FLAG_TC4);
}

/**
  * @brief  DeInitializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< Disable the sFLASH_SPI  */
    SPI_Cmd(sFLASH_SPI, DISABLE);

    /*!< DeInitializes the sFLASH_SPI */
    SPI_I2SDeInit(sFLASH_SPI);

    /*!< sFLASH_SPI Periph clock disable */
    RCC_APB2PeriphClockCmd(sFLASH_SPI_CLK, DISABLE);

    /*!< Configure sFLASH_SPI pins: SCK */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MISO */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
    GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MOSI */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
    GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
    GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
    GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  Initializes the peripherals used by the SPI FLASH driver.
  * @param  None
  * @retval None
  */
void sFLASH_LowLevel_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*!< sFLASH_SPI_CS_GPIO, sFLASH_SPI_MOSI_GPIO, sFLASH_SPI_MISO_GPIO 
       and sFLASH_SPI_SCK_GPIO Periph clock enable */
    RCC_APB2PeriphClockCmd(sFLASH_CS_GPIO_CLK | sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK |
                         sFLASH_SPI_SCK_GPIO_CLK, ENABLE);

    /*!< sFLASH_SPI Periph clock enable */
    RCC_APB2PeriphClockCmd(sFLASH_SPI_CLK, ENABLE);

    /*!< Configure sFLASH_SPI pins: SCK */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MOSI */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MOSI_PIN;
    GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_SPI pins: MISO */
    GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_MISO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
    GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

    /*!< Configure sFLASH_CS_PIN pin: sFLASH Card CS pin */
    GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @brief  DeInitializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void sEE_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /* sEE_I2C Peripheral Disable */
    I2C_Cmd(sEE_I2C, DISABLE);
    /* sEE_I2C DeInit */
    I2C_DeInit(sEE_I2C);
    /*!< sEE_I2C Periph clock disable */
    RCC_APB1PeriphClockCmd(sEE_I2C_CLK, DISABLE);
    /*!< GPIO configuration */
    /*!< Configure sEE_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(sEE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    /*!< Configure sEE_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
    GPIO_Init(sEE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
    /* Configure and enable I2C DMA TX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Configure and enable I2C DMA RX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_RX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
    NVIC_Init(&NVIC_InitStructure);
    /* Disable and Deinitialize the DMA channels */
    DMA_Cmd(sEE_I2C_DMA_CHANNEL_TX, DISABLE);
    DMA_Cmd(sEE_I2C_DMA_CHANNEL_RX, DISABLE);
    DMA_DeInit(sEE_I2C_DMA_CHANNEL_TX);
    DMA_DeInit(sEE_I2C_DMA_CHANNEL_RX);
}

/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void sEE_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /*!< sEE_I2C_SCL_GPIO_CLK and sEE_I2C_SDA_GPIO_CLK Periph clock enable */
    RCC_APB2PeriphClockCmd(sEE_I2C_SCL_GPIO_CLK | sEE_I2C_SDA_GPIO_CLK, ENABLE);
    /*!< sEE_I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(sEE_I2C_CLK, ENABLE);
    /*!< GPIO configuration */
    /*!< Configure sEE_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = sEE_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(sEE_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    /*!< Configure sEE_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = sEE_I2C_SDA_PIN;
    GPIO_Init(sEE_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
    /* Configure and enable I2C DMA TX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    /* Configure and enable I2C DMA RX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = sEE_I2C_DMA_RX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = sEE_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = sEE_I2C_DMA_SUBPRIO;
    NVIC_Init(&NVIC_InitStructure);
    /*!< I2C DMA TX and RX channels configuration */
    /* Enable the DMA clock */
    RCC_AHBPeriphClockCmd(sEE_I2C_DMA_CLK, ENABLE);
    /* I2C TX DMA Channel configuration */
    DMA_DeInit(sEE_I2C_DMA_CHANNEL_TX);
    sEEDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)sEE_I2C_DR_Address;
    sEEDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;   /* This parameter will be configured durig communication */
    sEEDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;    /* This parameter will be configured durig communication */
    sEEDMA_InitStructure.DMA_BufferSize = 0xFFFF;            /* This parameter will be configured durig communication */
    sEEDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    sEEDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    sEEDMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
    sEEDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    sEEDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    sEEDMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    sEEDMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(sEE_I2C_DMA_CHANNEL_TX, &sEEDMA_InitStructure);
    /* I2C RX DMA Channel configuration */
    DMA_DeInit(sEE_I2C_DMA_CHANNEL_RX);
    DMA_Init(sEE_I2C_DMA_CHANNEL_RX, &sEEDMA_InitStructure);
    /* Enable the DMA Channels Interrupts */
    DMA_ITConfig(sEE_I2C_DMA_CHANNEL_TX, DMA_IT_TC, ENABLE);
    DMA_ITConfig(sEE_I2C_DMA_CHANNEL_RX, DMA_IT_TC, ENABLE);
}

/**
  * @brief  Initializes DMA channel used by the I2C EEPROM driver.
  * @param  None
  * @retval None
  */
void sEE_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction)
{
    /* Initialize the DMA with the new parameters */
    if (Direction == sEE_DIRECTION_TX)
    {
        /* Configure the DMA Tx Channel with the buffer address and the buffer size */
        sEEDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
        sEEDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
        sEEDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
        DMA_Init(sEE_I2C_DMA_CHANNEL_TX, &sEEDMA_InitStructure);
    }
    else
    {
        /* Configure the DMA Rx Channel with the buffer address and the buffer size */
        sEEDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
        sEEDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        sEEDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
        DMA_Init(sEE_I2C_DMA_CHANNEL_RX, &sEEDMA_InitStructure);
    }
}

/**
  * @brief  Initializes the LM75_I2C..
  * @param  None
  * @retval None
  */
void LM75_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    /*!< LM75_I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(LM75_I2C_CLK, ENABLE);
    /*!< LM75_I2C_SCL_GPIO_CLK, LM75_I2C_SDA_GPIO_CLK
         and LM75_I2C_SMBUSALERT_GPIO_CLK Periph clock enable */
    RCC_APB2PeriphClockCmd(LM75_I2C_SCL_GPIO_CLK | LM75_I2C_SDA_GPIO_CLK |
                           LM75_I2C_SMBUSALERT_GPIO_CLK, ENABLE);
    /*!< Configure LM75_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(LM75_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    /*!< Configure LM75_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SDA_PIN;
    GPIO_Init(LM75_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
    /*!< Configure LM75_I2C pin: SMBUS ALERT */
    GPIO_InitStructure.GPIO_Pin = LM75_I2C_SMBUSALERT_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(LM75_I2C_SMBUSALERT_GPIO_PORT, &GPIO_InitStructure);
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */

