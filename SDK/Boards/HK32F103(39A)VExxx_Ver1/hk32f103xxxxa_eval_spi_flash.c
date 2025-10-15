/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_spi_flash.c
* @brief:     API
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
* @log:
*******************************************************************************/


/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_eval_spi_flash.h"

static __IO uint32_t  SPITimeout = SPIT_LONG_TIMEOUT;     

/* Private variables ---------------------------------------------------------*/
static uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode);
extern void delay(uint32_t i);
/** @addtogroup hk32f103xxxxa_StdPeriph_Driver
  * @{
  */
/**
  * @brief  
  * @param  
  * @retval 
  */
uint8_t SPI_FLASH_Send_Byte(uint8_t data)
{
	SPITimeout = SPIT_FLAG_TIMEOUT;

	while(SPI_I2SGetFlagStatus(SPI1,SPI_I2S_FLAG_TXE) == RESET)
	{
		if((SPITimeout--) == 0) return SPI_TIMEOUT_UserCallback(0);
	}
	

	SPI_I2SSendData (SPI1,data);
	
	
	SPITimeout = SPIT_FLAG_TIMEOUT;

	while(SPI_I2SGetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE) == RESET)
	{
		if((SPITimeout--) == 0)
		{			
			return SPI_TIMEOUT_UserCallback(0);
		}
	}

	return SPI_I2SReceiveData(SPI1); 

}

/**
  * @brief  
  * @param  
  * @retval 
  */
void SPI_Read_Data(uint32_t addr,uint8_t *readBuff,uint32_t numByteToRead)
{

	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	SPI_FLASH_Send_Byte(READ_DATA);
	
	SPI_FLASH_Send_Byte((addr>>16)&0xff);
	
	SPI_FLASH_Send_Byte((addr>>8)&0xff); 
	
    SPI_FLASH_Send_Byte(addr&0xff); 
	
	while(numByteToRead--)
	{	
		*readBuff = SPI_FLASH_Send_Byte(DUMMY);
		readBuff++;
	}
	
	
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
}
/**
  * @brief  
  * @param  
  * @retval 
  */
uint32_t SPI_Read_ID(void)
{
    uint32_t flash_id;
	

	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	SPI_FLASH_Send_Byte(READ_JEDEC_ID);
	
	flash_id = SPI_FLASH_Send_Byte(DUMMY);

	flash_id <<= 8;
	
	flash_id |= SPI_FLASH_Send_Byte(DUMMY); 
	
	flash_id <<= 8;
	
	flash_id |= SPI_FLASH_Send_Byte(DUMMY); 
	
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
	
    return flash_id;
}



/**
  * @brief  
  * @param  
  * @retval 
  */
void SPI_Write_Enable(void)
{

	 GPIO_ResetBits(GPIOA,GPIO_Pin_4);
     SPI_FLASH_Send_Byte(WRITE_ENABLE);	 
     GPIO_SetBits(GPIOA,GPIO_Pin_4);
}
/**
  * @brief  
  * @param  
  * @retval 
  */
void SPI_Write_Data(uint32_t addr,uint8_t *writeBuff,uint32_t numByteToWrite)
{
	SPI_Write_Enable();

    GPIO_ResetBits(GPIOA,GPIO_Pin_4);

	SPI_FLASH_Send_Byte(WRITE_DATA);
	
	SPI_FLASH_Send_Byte((addr>>16)&0xff);
	
	SPI_FLASH_Send_Byte((addr>>8)&0xff); 
	
    SPI_FLASH_Send_Byte(addr&0xff); 
    

	
	while(numByteToWrite--)
	{
        
		SPI_FLASH_Send_Byte(*writeBuff);
		writeBuff++;
	}
	
	
    GPIO_SetBits(GPIOA,GPIO_Pin_4);
	SPI_WaitForWriteEnd();
}

/**
  * @brief  
  * @param  
  * @retval 
  */
void SPI_WaitForWriteEnd(void)
{
	uint8_t status_reg = 0;
	

    GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	
    SPI_FLASH_Send_Byte(READ_STATUS);
	
	do
	{	
        status_reg = SPI_FLASH_Send_Byte(DUMMY);
	}
	while((status_reg & 0x01) == 1);
	
    GPIO_SetBits(GPIOA,GPIO_Pin_4);


}

/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：Error code, which can be used to locate the link that went wrong.
  * @retval 0:SPI read error
  */
void SPI_Erase_Sector(uint32_t addr)
{	
	SPI_Write_Enable();
    //片选使能
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	SPI_FLASH_Send_Byte(ERASE_SECTOR);
	
	SPI_FLASH_Send_Byte((addr>>16)&0xff);
	
	SPI_FLASH_Send_Byte((addr>>8)&0xff); 
	
    SPI_FLASH_Send_Byte(addr&0xff); 
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);	
	
	SPI_WaitForWriteEnd();
	
}
/**
  * @brief  Basic management of the timeout situation.
  * @param  errorCode：Error code, which can be used to locate the link that went wrong.
  * @retval 0:SPI read error
  */
static  uint32_t SPI_TIMEOUT_UserCallback(uint8_t errorCode)
{
  /* Block communication and all processes */
  FLASH_ERROR("SPI 等待超时!errorCode = %d",errorCode);
  
  return 0;
}

   

/**
  * @}
  */ 

