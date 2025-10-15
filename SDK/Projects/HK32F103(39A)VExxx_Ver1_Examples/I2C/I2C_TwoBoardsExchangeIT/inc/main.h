/*******************************************************************************
* @copyright: Shenzhen Hangshun Chip Technology R&D Co., Ltd
* @filename:  main.h
* @brief:     Header for main.c file.
* @author:    AE Team
*******************************************************************************/


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "hk32f103xxxxa_conf.h"
#include "hk32f103xxxxa_eval.h"

/* Exported types ------------------------------------------------------------*/
#define MASTER_MODE                      (0)
#define SLAVE_MODE                       (1)
           
#define BUFFER_SIZE                      (20)
           
#define CLOCK_SPEED                      (400000)
           
#define I2C_DIRECTION_TX                 (0)
#define I2C_DIRECTION_RX                 (1)
           
#define MASTER_ADDRESS                   (0x30)
#define SLAVE_ADDRESS                    (0x28)
           
#define START_SET                        ((uint16_t)0x0100)

#define s_I2C                            I2C1
#define s_I2C_CLK                        RCC_APB1Periph_I2C1
#define s_I2C_SCL_PIN                    GPIO_Pin_6                 
#define s_I2C_SCL_GPIO_PORT              GPIOB                      
#define s_I2C_SCL_GPIO_CLK               RCC_APB2Periph_GPIOB
#define s_I2C_SDA_PIN                    GPIO_Pin_7                
#define s_I2C_SDA_GPIO_PORT              GPIOB                      
#define s_I2C_SDA_GPIO_CLK               RCC_APB2Periph_GPIOB

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /*__MAIN_H */

