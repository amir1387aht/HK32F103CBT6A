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
uint8_t BufferTx[BUFFER_SIZE] = {0};
uint8_t BufferRx[BUFFER_SIZE] = {0};

__IO uint32_t  sTimeout = s_LONG_TIMEOUT;
__IO uint16_t* sDataReadPointer;
__IO uint8_t*  sDataWritePointer;
__IO uint8_t sDataNum;
uint8_t RxFlagM = 0;

DMA_InitTypeDef   sDMA_InitStructure;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static ErrorStatus s_TIMEOUT_UserCallback(void);
static void sI2C_LowLevel_Init(void);
static void sI2C_Init(void);
static void sI2C_LowLevel_DeInit(void);

#if(IIC_MODE == MASTER_MODE)
static ErrorStatus I2C_Master_BufferWrite(uint8_t* pBuffer, uint8_t* NumByteToWrite);
static ErrorStatus I2C_Master_BufferRead(uint8_t* pBuffer, uint16_t* NumByteToRead);
#endif

#if(IIC_MODE == SLAVE_MODE)
static void I2C_Slave_BufferReadWrite(void);
#endif

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
    /* Configures USART */
    USART_Config();
  
    /* Initialize the I2C */
    sI2C_Init();
 
#if(IIC_MODE == MASTER_MODE)
    
    HK_EVAL_PBInit(BUTTON_KEY1,BUTTON_MODE_GPIO);
  
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        BufferTx[i] = i;
    }
  
    while(HK_EVAL_PBGetState(BUTTON_KEY1) == SET)
    {
    }
    
    printf("\r\nThe master send data:");
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", BufferTx[i]);
    }   
    
    sDataNum = BUFFER_SIZE;
    I2C_Master_BufferWrite(BufferTx, (uint8_t*)(&sDataNum));
    while (sDataNum > 0)
    {
    }
    
    sDataNum = BUFFER_SIZE;
    I2C_Master_BufferRead(BufferRx, (uint16_t *)(&sDataNum));
    while (sDataNum > 0)
    {
    }
      
    printf("\r\nThe master receives data:");
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", BufferRx[i]);
    }   
    
#else
    I2C_Slave_BufferReadWrite();

    while(RxFlagM == 0)
    {
    }
    RxFlagM = 0;
    
    printf("\r\nThe slave receives data:");
    
    for (uint8_t i = 0; i < BUFFER_SIZE; i++)
    {
        printf("%d ", BufferRx[i]);
    }     
#endif

    /* Free all used resources */
    sI2C_LowLevel_DeInit();

    while (1)
    {
    }
}

/**
  * @brief  Initializes DMA channel.
  * @param  None
  * @retval None
  */
void s_LowLevel_DMAConfig(uint32_t pBuffer, uint32_t BufferSize, uint32_t Direction)
{
    /* Initialize the DMA with the new parameters */
    if (Direction == s_DIRECTION_TX)
    {
        /* Configure the DMA Tx Channel with the buffer address and the buffer size */
        sDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
        sDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
        sDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
        DMA_Init(s_I2C_DMA_CHANNEL_TX, &sDMA_InitStructure);
    }
    else
    {
        /* Configure the DMA Rx Channel with the buffer address and the buffer size */
        sDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)pBuffer;
        sDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        sDMA_InitStructure.DMA_BufferSize = (uint32_t)BufferSize;
        DMA_Init(s_I2C_DMA_CHANNEL_RX, &sDMA_InitStructure);
    }
}

#if(IIC_MODE == MASTER_MODE)
/**
  * @brief  I2C Master BufferWrite.
  * @param  pBuffer : pointer to the buffer containing the data to be written.
  * @param  NumByteToWrite : pointer to the variable holding number of bytes to
  *         be written.
  * @retval ErrorStatus
  */
static ErrorStatus I2C_Master_BufferWrite(uint8_t* pBuffer, uint8_t* NumByteToWrite)
{
    
    sDataWritePointer = NumByteToWrite;
    /*!< While the bus is busy */
    sTimeout = s_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BUSY))
    {
        if ((sTimeout--) == 0)
        {
            return s_TIMEOUT_UserCallback();
        }          
    }

    /*!< Send START condition */
    I2C_GenerateSTART(s_I2C, ENABLE);
    /*!< Test on EV5 and clear it */
    sTimeout = s_FLAG_TIMEOUT;

    while (!I2C_CheckEvent(s_I2C, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((sTimeout--) == 0)
        {
            return s_TIMEOUT_UserCallback();
        }          
    }

    sTimeout = s_FLAG_TIMEOUT;
    I2C_Send7bitAddress(s_I2C, SLAVE_ADDRESS, I2C_Direction_Transmitter);
    /*!< Test on EV6 and clear it */
    sTimeout = s_FLAG_TIMEOUT;

    while (!I2C_CheckEvent(s_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
        if ((sTimeout--) == 0)
        {
            return s_TIMEOUT_UserCallback();
        }          
    }

    /* Configure the DMA Tx Channel with the buffer address and the buffer size */
    s_LowLevel_DMAConfig((uint32_t)pBuffer, (uint8_t)(*NumByteToWrite), s_DIRECTION_TX);
    /* Enable the DMA Tx Channel */
    DMA_Cmd(s_I2C_DMA_CHANNEL_TX, ENABLE);
   
    return SUCCESS;
}

/**
  * @brief  I2C Master BufferRead.
  * @param  pBuffer : pointer to the buffer that receives the data read.
  * @param  NumByteToRead : pointer to the variable holding number of bytes to
  *         be read.
  * @retval ErrorStatus.
  */
static ErrorStatus I2C_Master_BufferRead(uint8_t* pBuffer, uint16_t* NumByteToRead)
{
    sDataReadPointer = NumByteToRead;
    /*!< While the bus is busy */
    sTimeout = s_LONG_TIMEOUT;

    while (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BUSY))
    {
        if ((sTimeout--) == 0)
        {
            return s_TIMEOUT_UserCallback();
        }          
    }

    /*!< Send STRAT condition a second time */
    I2C_GenerateSTART(s_I2C, ENABLE);
    /*!< Test on EV5 and clear it (cleared by reading SR1 then writing to DR) */
    sTimeout = s_FLAG_TIMEOUT;

    while (!I2C_CheckEvent(s_I2C, I2C_EVENT_MASTER_MODE_SELECT))
    {
        if ((sTimeout--) == 0) 
        {
            return s_TIMEOUT_UserCallback();
        }
    }

    /*!< Send address */
    I2C_Send7bitAddress(s_I2C, SLAVE_ADDRESS, I2C_Direction_Receiver);
    
    /*!< Test on EV6 and clear it */
    sTimeout = s_FLAG_TIMEOUT;

    while (!I2C_CheckEvent(s_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
    {
        if ((sTimeout--) == 0)
        {
            return s_TIMEOUT_UserCallback();
        }          
    }

    /* Configure the DMA Rx Channel with the buffer address and the buffer size */
    s_LowLevel_DMAConfig((uint32_t)pBuffer, (uint16_t)(*NumByteToRead), s_DIRECTION_RX);
    /* Inform the DMA that the next End Of Transfer Signal will be the last one */
    I2C_DMALastTransferCmd(s_I2C, ENABLE);
    /* Enable the DMA Rx Channel */
    DMA_Cmd(s_I2C_DMA_CHANNEL_RX, ENABLE);
     
    return SUCCESS;
}
#endif

#if(IIC_MODE == SLAVE_MODE)
/**
  * @brief  Prepares the I2C slave for transmission.
  * @param  None.
  * @retval None.
  */
static void I2C_Slave_BufferReadWrite(void)
{
    I2C_ITConfig(s_I2C, I2C_IT_ERR, ENABLE);
    I2C_ITConfig(s_I2C, I2C_IT_EVT, ENABLE);
    I2C_ITConfig(s_I2C, I2C_IT_BUF, ENABLE);
}
#endif

/**
  * @brief  Example of timeout situation management.
  * @param  None.
  * @retval None.
  */
static ErrorStatus s_TIMEOUT_UserCallback(void)
{
    /* Block communication and all processes */
    while (1)
    {
    }
}

/**
  * @brief  Configure Usart
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
    USART_InitTypeDef USART_InitStructure;

    /* USARTx configured as follow:
    - BaudRate = 115200 baud
    - Word Length = 8 Bits
    - Stop Bit = 1 Stop Bit
    - Parity = No Parity
    - Hardware flow control disabled (RTS and CTS signals)
    - Receive enabled
    */
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    HK_EVAL_COMInit(COM1, &USART_InitStructure);
}

/**
  * @brief  Initializes peripherals.
  * @param  None
  * @retval None
  */
static void sI2C_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    /*!< s_I2C_SCL_GPIO_CLK and s_I2C_SDA_GPIO_CLK Periph clock enable */
    RCC_APB2PeriphClockCmd(s_I2C_SCL_GPIO_CLK | s_I2C_SDA_GPIO_CLK, ENABLE);
    /*!< s_I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(s_I2C_CLK, ENABLE);
    /*!< GPIO configuration */
    /*!< Configure s_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = s_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(s_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    /*!< Configure s_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = s_I2C_SDA_PIN;
    GPIO_Init(s_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Configure and enable I2C DMA TX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = s_I2C_DMA_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = s_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = s_I2C_DMA_SUBPRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure and enable I2C DMA RX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = s_I2C_DMA_RX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = s_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = s_I2C_DMA_SUBPRIO;
    NVIC_Init(&NVIC_InitStructure);
    
#if(IIC_MODE == SLAVE_MODE)
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#endif
   
    /*!< I2C DMA TX and RX channels configuration */

    /* Enable the DMA clock */
    RCC_AHBPeriphClockCmd(s_I2C_DMA_CLK, ENABLE);

    /* I2C TX DMA Channel configuration */
    DMA_DeInit(s_I2C_DMA_CHANNEL_TX);
    sDMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)s_I2C_DR_Address;
    sDMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)0;   /* This parameter will be configured durig communication */
    sDMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;    /* This parameter will be configured durig communication */
    sDMA_InitStructure.DMA_BufferSize = 0xFFFF;            /* This parameter will be configured durig communication */
    sDMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    sDMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    sDMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte;
    sDMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    sDMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    sDMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    sDMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(s_I2C_DMA_CHANNEL_TX, &sDMA_InitStructure);

    /* I2C RX DMA Channel configuration */
    DMA_DeInit(s_I2C_DMA_CHANNEL_RX);
    DMA_Init(s_I2C_DMA_CHANNEL_RX, &sDMA_InitStructure);

    /* Enable the DMA Channels Interrupts */
    DMA_ITConfig(s_I2C_DMA_CHANNEL_TX, DMA_IT_TC, ENABLE);
    DMA_ITConfig(s_I2C_DMA_CHANNEL_RX, DMA_IT_TC, ENABLE);
}

/**
  * @brief  Initializes peripherals.
  * @param  None
  * @retval None
  */
static void sI2C_Init(void)
{
    I2C_InitTypeDef  I2C_InitStructure;
    sI2C_LowLevel_Init();
    /*!< I2C configuration */

    /* s_I2C configuration */
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
#if(IIC_MODE == MASTER_MODE)
    I2C_InitStructure.I2C_OwnAddress1 = MASTER_ADDRESS;
#else
    I2C_InitStructure.I2C_OwnAddress1 = SLAVE_ADDRESS;
#endif  
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_InitStructure.I2C_ClockSpeed = CLOCK_SPEED;

    /* s_I2C Peripheral Enable */
    I2C_Cmd(s_I2C, ENABLE);

    /* Apply s_I2C configuration after enabling it */
    I2C_Init(s_I2C, &I2C_InitStructure);

    /* Enable the s_I2C peripheral DMA requests */
    I2C_DMACmd(s_I2C, ENABLE);
}

/**
  * @brief  DeInitializes peripherals.
  * @param  None
  * @retval None
  */
static void sI2C_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* s_I2C Peripheral Disable */
    I2C_Cmd(s_I2C, DISABLE);

    /* s_I2C DeInit */
    I2C_DeInit(s_I2C);
    /*!< s_I2C Periph clock disable */
    RCC_APB1PeriphClockCmd(s_I2C_CLK, DISABLE);
    /*!< GPIO configuration */
    /*!< Configure s_I2C pins: SCL */
    GPIO_InitStructure.GPIO_Pin = s_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(s_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    /*!< Configure s_I2C pins: SDA */
    GPIO_InitStructure.GPIO_Pin = s_I2C_SDA_PIN;
    GPIO_Init(s_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Configure and enable I2C DMA TX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = s_I2C_DMA_TX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = s_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = s_I2C_DMA_SUBPRIO;
    NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Configure and enable I2C DMA RX Channel interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = s_I2C_DMA_RX_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = s_I2C_DMA_PREPRIO;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = s_I2C_DMA_SUBPRIO;
    NVIC_Init(&NVIC_InitStructure);

    /* Disable and Deinitialize the DMA channels */
    DMA_Cmd(s_I2C_DMA_CHANNEL_TX, DISABLE);
    DMA_Cmd(s_I2C_DMA_CHANNEL_RX, DISABLE);
    DMA_DeInit(s_I2C_DMA_CHANNEL_TX);
    DMA_DeInit(s_I2C_DMA_CHANNEL_RX);
}

/**
  * @brief  This function handles the DMA Tx Channel interrupt Handler.
  * @param  None
  * @retval None
  */
void s_I2C_DMA_TX_IRQHandler(void)
{
    /* Check if the DMA transfer is complete */
    if (DMA_GetFlagStatus(s_I2C_DMA_FLAG_TX_TC) != RESET)
    {
        /* Disable the DMA Tx Channel and Clear all its Flags */
        DMA_Cmd(s_I2C_DMA_CHANNEL_TX, DISABLE);
        DMA_ClearFlag(s_I2C_DMA_FLAG_TX_GL);
        /*!< Wait till all data have been physically transferred on the bus */
        sTimeout = s_LONG_TIMEOUT;

        while (!I2C_GetFlagStatus(s_I2C, I2C_FLAG_BTF))
        {
            if ((sTimeout--) == 0) 
            {
                s_TIMEOUT_UserCallback();
            }
        }

        /*!< Send STOP condition */
        I2C_GenerateSTOP(s_I2C, ENABLE);
        /* Perform a read on SR1 and SR2 register to clear eventualaly pending flags */
        (void)s_I2C->SR1;
        (void)s_I2C->SR2;
        /* Reset the variable holding the number of data to be written */
        *sDataWritePointer = 0;
    }
}

/**
  * @brief  This function handles the DMA Rx Channel interrupt Handler.
  * @param  None
  * @retval None
  */
void s_I2C_DMA_RX_IRQHandler(void)
{
    /* Check if the DMA transfer is complete */
    if (DMA_GetFlagStatus(s_I2C_DMA_FLAG_RX_TC) != RESET)
    {
        /*!< Send STOP Condition */
        I2C_GenerateSTOP(s_I2C, ENABLE);

        /* Disable the DMA Rx Channel and Clear all its Flags */
        DMA_Cmd(s_I2C_DMA_CHANNEL_RX, DISABLE);
        DMA_ClearFlag(s_I2C_DMA_FLAG_RX_GL);

        /* Reset the variable holding the number of data to be read */
        *sDataReadPointer = 0;
        RxFlagM = 1;
    }
}

/**
  * @brief  printf function
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
    /*  Printf   */
    USART_SendData(USART1, (unsigned char) ch);

    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET)
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



