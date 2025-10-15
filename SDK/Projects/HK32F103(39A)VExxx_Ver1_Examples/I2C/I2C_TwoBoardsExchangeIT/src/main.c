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
#include "hk32f103xxxxa.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t BufferTx[BUFFER_SIZE] = {0};
uint8_t BufferRx[BUFFER_SIZE] = {0};
uint8_t TxFlagM = 0;
uint8_t RxFlagM = 0;

__IO uint32_t I2CDirection = I2C_DIRECTION_TX;
__IO uint32_t NumbOfBytes;
__IO uint8_t Address;

/* Private function prototypes -----------------------------------------------*/
static void NVIC_Configuration(void);
static void USART_Config(void);
static void I2C_LowLevel_Init(void);
static void sI2C_LowLevel_DeInit(void);
#if(IIC_MODE == MASTER_MODE)
static void I2C_Master_BufferRead(uint32_t NumByteToRead, uint8_t SlaveAddress);
static void I2C_Master_BufferWrite(uint32_t NumByteToWrite, uint8_t SlaveAddress);
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
  
    /* Init NVIC */
    NVIC_Configuration();
  
    /* Init I2C */
    I2C_LowLevel_Init(); 
  
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

    I2C_Master_BufferWrite(BUFFER_SIZE, SLAVE_ADDRESS);
    while(TxFlagM == 0)
    {
    }
    TxFlagM = 0;
    I2C_Master_BufferRead(BUFFER_SIZE, SLAVE_ADDRESS);
    while(RxFlagM == 0)
    {
    }
    RxFlagM = 0;

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

    sI2C_LowLevel_DeInit();
    
    while (1)
    {
    }
}

/**
  * @brief  Init NVIC.
  * @param  None
  * @retval None
  */
static void NVIC_Configuration(void)
{ 
    NVIC_InitTypeDef NVIC_InitStructure;
  
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_EV_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    NVIC_InitStructure.NVIC_IRQChannel = I2C1_ER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
  
}

/**
  * @brief  DeInitializes peripherals.
  * @param  None
  * @retval None
  */
static void sI2C_LowLevel_DeInit(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

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
}

/**
  * @brief  Init I2C.
  * @param  None
  * @retval None
  */
static void I2C_LowLevel_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef  I2C_InitStructure;

    /* Clock Enable */
    RCC_APB2PeriphClockCmd(s_I2C_SCL_GPIO_CLK | s_I2C_SDA_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(s_I2C_CLK, ENABLE);

    /* SDA and SCL configuration */
    GPIO_InitStructure.GPIO_Pin = s_I2C_SCL_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_Init(s_I2C_SCL_GPIO_PORT, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = s_I2C_SDA_PIN;
    GPIO_Init(s_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);

    /* Enable I2C2 reset state */
    RCC_APB1PeriphResetCmd(s_I2C_CLK, ENABLE);

    /* Release I2C2 from reset state */
    RCC_APB1PeriphResetCmd(s_I2C_CLK, DISABLE);

    /* I2C2 configuration */
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
    I2C_Init(s_I2C, &I2C_InitStructure);
}

#if(IIC_MODE == MASTER_MODE)
/**
  * @brief  Reads buffer of bytes  from the slave.
  * @param  pBuffer: Buffer of bytes to be read from the slave.
  * @param  NumByteToRead: Number of bytes to be read by the Master.
  * @param  SlaveAddress: The address of the slave to be addressed by the Master.
  * @retval None.
  */
static void I2C_Master_BufferRead(uint32_t NumByteToRead, uint8_t SlaveAddress)
{
    I2C_ITConfig(s_I2C, I2C_IT_ERR, ENABLE);
    I2C_ITConfig(s_I2C, I2C_IT_EVT, ENABLE);
    I2C_ITConfig(s_I2C, I2C_IT_BUF, ENABLE);
    I2CDirection = I2C_DIRECTION_RX;
    Address = SlaveAddress;
    NumbOfBytes = NumByteToRead;
  
    /* Generates START condition */
    I2C_GenerateSTART(s_I2C, ENABLE);

    /* Wait until the START condition is generated on the bus: START bit is cleared by hardware */
    while ((s_I2C->CR1 & START_SET) == START_SET)
    {
    }

    /* Wait until the BUSY */
    while (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BUSY) == SET)
    {
    }

    /* Enable Acknowledgement to be ready for another reception */
    I2C_AcknowledgeConfig(s_I2C, ENABLE);
}

/**
  * @brief  Writes buffer of bytes.
  * @param  pBuffer: Buffer of bytes to be sent to the slave.
  * @param  NumByteToWrite: Number of bytes to be sent by the Master.
  * @param  SlaveAddress: The address of the slave to be addressed by the Master.
  * @retval None.
  */
static void I2C_Master_BufferWrite(uint32_t NumByteToWrite, uint8_t SlaveAddress)
{
    I2C_ITConfig(s_I2C, I2C_IT_ERR, ENABLE);
    I2C_ITConfig(s_I2C, I2C_IT_EVT, ENABLE);
    I2C_ITConfig(s_I2C, I2C_IT_BUF, ENABLE);
   
    I2CDirection = I2C_DIRECTION_TX;
    Address = SlaveAddress;
    NumbOfBytes = NumByteToWrite;

    /* Generates START condition */
    I2C_GenerateSTART(s_I2C, ENABLE);

    /* Wait until the START condition is generated on the bus: START bit is cleared by hardware */
    while ((s_I2C->CR1 & START_SET) == START_SET)
    {
    }

    /* Wait until the BUSY */
    while (I2C_GetFlagStatus(s_I2C, I2C_FLAG_BUSY) == SET)
    {
    }
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


