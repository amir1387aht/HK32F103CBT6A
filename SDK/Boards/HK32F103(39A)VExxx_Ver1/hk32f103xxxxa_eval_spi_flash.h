/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_eval_spi_flash.h
* @brief:     This file contains all the functions prototypes for the USART 
*             firmware library
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103xxxxA_EVAL_SPI_FLASH_H
#define __HK32F103xxxxA_EVAL_SPI_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"


/** @addtogroup Utilities
  * @{
  */ 


#define             FLASH_SPIx                                  SPI1
#define             FLASH_SPI_APBxClock_FUN                     RCC_APB2PeriphClockCmd
#define             FLASH_SPI_CLK                               RCC_APB2Periph_SPI1
#define             FLASH_SPI_GPIO_APBxClock_FUN                RCC_APB2PeriphClockCmd



#define             FLASH_SPI_SCK_PORT                          GPIOA   
#define             FLASH_SPI_SCK_PIN                           GPIO_Pin_5

#define             FLASH_SPI_MOSI_PORT                         GPIOA 
#define             FLASH_SPI_MOSI_PIN                          GPIO_Pin_7

#define             FLASH_SPI_MISO_PORT                         GPIOA 
#define             FLASH_SPI_MISO_PIN                          GPIO_Pin_6
#define             FLASH_SPI_GPIO_CLK                          RCC_APB2Periph_GPIOA
	
#define             FLASH_SPI_CS_PORT                           GPIOA 
#define             FLASH_SPI_CS_PIN                            GPIO_Pin_4




#define DUMMY 							0x00
#define WRITE_STATUS				    0x01
#define WRITE_DATA				        0x02	
#define READ_DATA					    0x03
#define Write_Disable                   0x04
#define READ_STATUS				        0x05
#define WRITE_ENABLE                    0x06		
#define ERASE_SECTOR			        0x20	
#define READ_JEDEC_ID                   0x9f	

#define SPIT_FLAG_TIMEOUT               ((uint32_t)0x1000)
#define SPIT_LONG_TIMEOUT               ((uint32_t)(10 * SPIT_FLAG_TIMEOUT))
#define FLASH_ERROR(fmt,arg...)         printf("<<-FLASH-ERROR->> "fmt"\n",##arg)


void SPI_FLASH_Init(void);
uint32_t SPI_Read_ID(void);
void SPI_Erase_Sector(uint32_t addr);
void SPI_Read_Data(uint32_t addr,uint8_t *readBuff,uint32_t numByteToRead);
void SPI_Write_Data(uint32_t addr,uint8_t *writeBuff,uint32_t numByteToWrite);
																					
void SPI_WaitForWriteEnd(void);






#ifdef __cplusplus
}
#endif
  
#endif /* __HK32F103xxxxA_EVAL_SPI_FLASH_H */


/**
  * @}
  */

