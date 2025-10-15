/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  hk32f103xxxxa_spi.h 
* @brief:     RCC initialization and configuration 
* @author:    AE Team
* @version:   V1.0.0/2023-10-23
* @log:
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HK32F103XXXXA_SPI_H
#define __HK32F103XXXXA_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"



	 
/** @addtogroup SPI SPI
  * @{
  */	 
	 
/** @defgroup SPI_Exported_Types SPI_Exported_Types
  * @{
  */	 
	 
/** 
  * @brief  SPI Init structure definition  
  */

typedef struct
{
	uint16_t SPI_Direction;           /*!< Specifies the SPI unidirectional or bidirectional data mode.
                                         This parameter can be a value of SPI_data_direction */

	uint16_t SPI_Mode;                /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of SPI_mode */
  
	uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of SPI_data_size */

	uint16_t SPI_CPOL;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of SPI_Clock_Polarity */

	uint16_t SPI_CPHA;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of SPI_Clock_Phase */

	uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of SPI_Slave_Select_management */
 
	uint16_t SPI_BaudRatePrescaler;   /*!< Specifies the Baud Rate prescaler value which will be
                                         used to configure the transmit and receive SCK clock.
                                         This parameter can be a value of SPI_BaudRate_Prescaler
                                         @note The communication clock is derived from the master
                                               clock. The slave clock does not need to be set. */

	uint16_t SPI_FirstBit;            /*!< Specifies whether data transfers start from MSB or LSB bit.
                                         This parameter can be a value of SPI_MSB_LSB_transmission */

	uint16_t SPI_CRCPolynomial;       /*!< Specifies the polynomial used for the CRC calculation. */
}SPI_InitTypeDef;


/** 
  * @brief  I2S Init structure definition  
  */

typedef struct
{
	uint16_t I2S_Mode;         /*!< Specifies the I2S operating mode.
                                  This parameter can be a value of SPI_I2S_Mode */

	uint16_t I2S_Standard;     /*!< Specifies the standard used for the I2S communication.
                                  This parameter can be a value of SPI_I2S_Standard */

	uint16_t I2S_DataFormat;   /*!< Specifies the data format for the I2S communication.
                                  This parameter can be a value of SPI_I2S_Data_Format */

	uint16_t I2S_MCLKOutput;   /*!< Specifies whether the I2S MCLK output is enabled or not.
                                  This parameter can be a value of SPI_I2S_MCLK_Output */

	uint32_t I2S_AudioFreq;    /*!< Specifies the frequency selected for the I2S communication.
                                  This parameter can be a value of SPI_I2S_Audio_Frequency */

	uint16_t I2S_CPOL;         /*!< Specifies the idle state of the I2S clock.
                                  This parameter can be a value of SPI_I2S_Clock_Polarity */
}I2S_InitTypeDef;

/**
  * @}
  */

/** @defgroup SPI_Exported_Constants SPI_Exported_Constants
  * @{
  */

/** @defgroup SPIx_Selection SPIx_Selection
  * @{
  */
#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPI1) || \
                                   ((PERIPH) == SPI2) || \
                                   ((PERIPH) == SPI3))
/**
  * @}
  */ 

/** @defgroup SPI_data_direction SPI_data_direction
  * @{
  */
  
#define SPI_Direction_2Lines_FullDuplex ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly     ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx          ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx          ((uint16_t)0xC000)
#define IS_SPI_DIRECTION_MODE(MODE) (((MODE) == SPI_Direction_2Lines_FullDuplex) || \
                                     ((MODE) == SPI_Direction_2Lines_RxOnly) || \
                                     ((MODE) == SPI_Direction_1Line_Rx) || \
                                     ((MODE) == SPI_Direction_1Line_Tx))
/**
  * @}
  */ 


/** @defgroup SPI_Mode SPI_Mode
  * @{
  */

#define SPI_Mode_Master                 ((uint16_t)0x0104)
#define SPI_Mode_Slave                  ((uint16_t)0x0000)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */ 


/** @defgroup Data_Size Data_Size
  * @{
  */

#define SPI_DataSize_16b                ((uint16_t)0x0800)
#define SPI_DataSize_8b                 ((uint16_t)0x0000)
#define IS_SPI_DATASIZE(DATASIZE) (((DATASIZE) == SPI_DataSize_16b) || \
                                   ((DATASIZE) == SPI_DataSize_8b))
/**
  * @}
  */ 

/** @defgroup SPI_Clock_Polarity SPI_Clock_Polarity
  * @{
  */

#define SPI_CPOL_Low                    ((uint16_t)0x0000)
#define SPI_CPOL_High                   ((uint16_t)0x0002)
#define IS_SPI_CPOL(CPOL) (((CPOL) == SPI_CPOL_Low) || \
                           ((CPOL) == SPI_CPOL_High))
/**
  * @}
  */ 
  

/** @defgroup SPI_Clock_Phase SPI_Clock_Phase
  * @{
  */
#define SPI_CPHA_1Edge                  ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                  ((uint16_t)0x0001)
#define IS_SPI_CPHA(CPHA) (((CPHA) == SPI_CPHA_1Edge) || \
                           ((CPHA) == SPI_CPHA_2Edge))
/**
  * @}
  */ 

/** @defgroup SPI_Slave_Select_management SPI_Slave_Select_management
  * @{
  */
#define SPI_NSS_Soft                    ((uint16_t)0x0200)
#define SPI_NSS_Hard                    ((uint16_t)0x0000)
#define IS_SPI_NSS(NSS) (((NSS) == SPI_NSS_Soft) || \
                         ((NSS) == SPI_NSS_Hard))
/**
  * @}
  */ 

/** @defgroup SPI_BaudRate_Prescaler SPI_BaudRate_Prescaler
  * @{
  */

#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038)
#define IS_SPI_BAUDRATE_PRESCALER(PRESCALER) (((PRESCALER) == SPI_BaudRatePrescaler_2) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_4) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_8) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_16) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_32) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_64) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_128) || \
                                              ((PRESCALER) == SPI_BaudRatePrescaler_256))
/**
  * @}
  */ 

/** @defgroup SPI_MSB_LSB_transmission SPI_MSB_LSB_transmission
  * @{
  */

#define SPI_FirstBit_MSB                ((uint16_t)0x0000)
#define SPI_FirstBit_LSB                ((uint16_t)0x0080)
#define IS_SPI_FIRST_BIT(BIT) (((BIT) == SPI_FirstBit_MSB) || \
                               ((BIT) == SPI_FirstBit_LSB))
/**
  * @}
  */  
 

/** @defgroup SPI_I2S_Mode SPI_I2S_Mode
  * @{
  */
#define I2S_Mode_SlaveTx                ((uint16_t)0x0000)
#define I2S_Mode_SlaveRx                ((uint16_t)0x0100)
#define I2S_Mode_MasterTx               ((uint16_t)0x0200)
#define I2S_Mode_MasterRx               ((uint16_t)0x0300)
#define IS_I2S_MODE(MODE) (((MODE) == I2S_Mode_SlaveTx) || \
                           ((MODE) == I2S_Mode_SlaveRx) || \
                           ((MODE) == I2S_Mode_MasterTx)|| \
                           ((MODE) == I2S_Mode_MasterRx))
/**
  * @}
  */  
 


/** @defgroup SPI_I2S_Standard SPI_I2S_Standard
  * @{
  */

#define I2S_Standard_Phillips           ((uint16_t)0x0000)
#define I2S_Standard_MSB                ((uint16_t)0x0010)
#define I2S_Standard_LSB                ((uint16_t)0x0020)
#define I2S_Standard_PCMShort           ((uint16_t)0x0030)
#define I2S_Standard_PCMLong            ((uint16_t)0x00B0)
#define IS_I2S_STANDARD(STANDARD) (((STANDARD) == I2S_Standard_Phillips) || \
                                   ((STANDARD) == I2S_Standard_MSB) || \
                                   ((STANDARD) == I2S_Standard_LSB) || \
                                   ((STANDARD) == I2S_Standard_PCMShort) || \
                                   ((STANDARD) == I2S_Standard_PCMLong))
/**
  * @}
  */                                    
                                   

/** @defgroup SPI_I2S_Data_Format SPI_I2S_Data_Format
  * @{
  */
#define I2S_DataFormat_16b              ((uint16_t)0x0000)
#define I2S_DataFormat_16bextended      ((uint16_t)0x0001)
#define I2S_DataFormat_24b              ((uint16_t)0x0003)
#define I2S_DataFormat_32b              ((uint16_t)0x0005)
#define IS_I2S_DATA_FORMAT(FORMAT) (((FORMAT) == I2S_DataFormat_16b) || \
                                    ((FORMAT) == I2S_DataFormat_16bextended) || \
                                    ((FORMAT) == I2S_DataFormat_24b) || \
                                    ((FORMAT) == I2S_DataFormat_32b))
/**
  * @}
  */    
  


/** @defgroup SPI_I2S_MCLK_Output SPI_I2S_MCLK_Output
  * @{
  */
#define I2S_MCLKOutput_Enable           ((uint16_t)0x0200)
#define I2S_MCLKOutput_Disable          ((uint16_t)0x0000)
#define IS_I2S_MCLK_OUTPUT(OUTPUT) (((OUTPUT) == I2S_MCLKOutput_Enable) || \
                                    ((OUTPUT) == I2S_MCLKOutput_Disable))

/**
  * @}
  */  


/** @defgroup SPI_I2S_Audio_Frequency SPI_I2S_Audio_Frequency
  * @{
  */
#define I2S_AudioFreq_192k               ((uint32_t)192000)
#define I2S_AudioFreq_96k                ((uint32_t)96000)
#define I2S_AudioFreq_48k                ((uint32_t)48000)
#define I2S_AudioFreq_44k                ((uint32_t)44100)
#define I2S_AudioFreq_32k                ((uint32_t)32000)
#define I2S_AudioFreq_22k                ((uint32_t)22050)
#define I2S_AudioFreq_16k                ((uint32_t)16000)
#define I2S_AudioFreq_11k                ((uint32_t)11025)
#define I2S_AudioFreq_8k                 ((uint32_t)8000)
#define I2S_AudioFreq_Default            ((uint32_t)2)

#define IS_I2S_AUDIO_FREQ(FREQ) ((((FREQ) >= I2S_AudioFreq_8k) && \
                                 ((FREQ) <= I2S_AudioFreq_192k)) || \
                                 ((FREQ) == I2S_AudioFreq_Default))
/**
  * @}
  */ 


/** @defgroup SPI_I2S_Clock_Polarity SPI_I2S_Clock_Polarity
  * @{
  */
#define I2S_CPOL_Low                    ((uint16_t)0x0000)
#define I2S_CPOL_High                   ((uint16_t)0x0008)
#define IS_I2S_CPOL(CPOL) (((CPOL) == I2S_CPOL_Low) || \
                           ((CPOL) == I2S_CPOL_High))
/**
  * @}
  */ 


/** @defgroup SPI_I2S_DMA_transfer_requests SPI_I2S_DMA_transfer_requests
  * @{
  */
#define SPI_I2S_DMAReq_Tx               ((uint16_t)0x0002)
#define SPI_I2S_DMAReq_Rx               ((uint16_t)0x0001)
#define IS_SPI_I2S_DMAREQ(DMAREQ) ((((DMAREQ) & (uint16_t)0xFFFC) == 0x00) && ((DMAREQ) != 0x00))
/**
  * @}
  */ 

/** @defgroup SPI_NSS_internal_software_management SPI_NSS_internal_software_management
  * @{
  */
#define SPI_NSSInternalSoft_Set         ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset       ((uint16_t)0xFEFF)
#define IS_SPI_NSS_INTERNAL(INTERNAL) (((INTERNAL) == SPI_NSSInternalSoft_Set) || \
                                       ((INTERNAL) == SPI_NSSInternalSoft_Reset))

/**
  * @}
  */ 


/** @defgroup SPI_CRC_Transmit_Receive SPI_CRC_Transmit_Receive
  * @{
  */
#define SPI_CRC_Tx                      ((uint8_t)0x00)
#define SPI_CRC_Rx                      ((uint8_t)0x01)
#define IS_SPI_CRC(CRC) (((CRC) == SPI_CRC_Tx) || ((CRC) == SPI_CRC_Rx))

/**
  * @}
  */ 


/** @defgroup SPI_Direction_Transmit_Receive SPI_Direction_Transmit_Receive
  * @{
  */
#define SPI_Direction_Rx                ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                ((uint16_t)0x4000)
#define IS_SPI_DIRECTION(DIRECTION) (((DIRECTION) == SPI_Direction_Rx) || \
                                     ((DIRECTION) == SPI_Direction_Tx))
/**
  * @}
  */ 


/** @defgroup SPI_I2S_interrupts_definition SPI_I2S_interrupts_definition
  * @{
  */
#define SPI_I2S_IT_TXE                  ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                 ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                  ((uint8_t)0x50)

#define IS_SPI_I2S_CONFIG_IT(IT) (((IT) == SPI_I2S_IT_TXE) || \
                                  ((IT) == SPI_I2S_IT_RXNE) || \
                                  ((IT) == SPI_I2S_IT_ERR))
#define SPI_I2S_IT_OVR                  ((uint8_t)0x56)
#define SPI_IT_MODF                     ((uint8_t)0x55)
#define SPI_IT_CRCERR                   ((uint8_t)0x54)
#define I2S_IT_UDR                      ((uint8_t)0x53)
#define IS_SPI_I2S_CLEAR_IT(IT) (((IT) == SPI_IT_CRCERR))
#define IS_SPI_I2S_GET_IT(IT) (((IT) == SPI_I2S_IT_RXNE) || ((IT) == SPI_I2S_IT_TXE) || \
                               ((IT) == I2S_IT_UDR) || ((IT) == SPI_IT_CRCERR) || \
                               ((IT) == SPI_IT_MODF) || ((IT) == SPI_I2S_IT_OVR))
/**
  * @}
  */ 



/** @defgroup SPI_I2S_flags_definition SPI_I2S_flags_definition
  * @{
  */
#define SPI_I2S_FLAG_RXNE               ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE                 ((uint16_t)0x0004)
#define I2S_FLAG_UDR                    ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR                 ((uint16_t)0x0010)
#define SPI_FLAG_MODF                   ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY                ((uint16_t)0x0080)
#define IS_SPI_I2S_CLEAR_FLAG(FLAG) (((FLAG) == SPI_FLAG_CRCERR))
#define IS_SPI_I2S_GET_FLAG(FLAG) (((FLAG) == SPI_I2S_FLAG_BSY) || ((FLAG) == SPI_I2S_FLAG_OVR) || \
                                   ((FLAG) == SPI_FLAG_MODF) || ((FLAG) == SPI_FLAG_CRCERR) || \
                                   ((FLAG) == I2S_FLAG_UDR) || ((FLAG) == I2S_FLAG_CHSIDE) || \
                                   ((FLAG) == SPI_I2S_FLAG_TXE) || ((FLAG) == SPI_I2S_FLAG_RXNE))
/**
  * @}
  */ 


/** @defgroup SPI_CRC_polynomial SPI_CRC_polynomial
  * @{
  */
#define IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL) ((POLYNOMIAL) >= 0x1)

/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPI_I2SDeInit(SPI_TypeDef* SPIx);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
void I2S_Init(SPI_TypeDef* SPIx, I2S_InitTypeDef* I2S_InitStruct);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void I2S_StructInit(I2S_InitTypeDef* I2S_InitStruct);
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void I2S_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_I2SITConfig(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);
void SPI_I2SDMACmd(SPI_TypeDef* SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);
void SPI_I2SSendData(SPI_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_I2SReceiveData(SPI_TypeDef* SPIx);
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef* SPIx, uint16_t SPI_NSSInternalSoft);
void SPI_SSOutputCmd(SPI_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SPI_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_TransmitCRC(SPI_TypeDef* SPIx);
void SPI_CalculateCRC(SPI_TypeDef* SPIx, FunctionalState NewState);
uint16_t SPI_GetCRC(SPI_TypeDef* SPIx, uint8_t SPI_CRC);
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef* SPIx);
void SPI_BiDirectionalLineConfig(SPI_TypeDef* SPIx, uint16_t SPI_Direction);
FlagStatus SPI_I2SGetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
void SPI_I2SClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
ITStatus SPI_I2SGetITStatus(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);
void SPI_I2SClearITPendingBit(SPI_TypeDef* SPIx, uint8_t SPI_I2S_IT);

#ifdef __cplusplus
}
#endif

#endif /*__HK32F103XXXXA_SPI_H */



