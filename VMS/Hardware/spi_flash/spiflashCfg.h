/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPI_FLASH_CFG_H
#define __SPI_FLASH_CFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
  
/* M25P FLASH SPI Interface pins  */  
#define sFLASH_SPI                           SPI2
#define sFLASH_SPI_CLK                       RCC_APB1Periph_SPI2
#define sFLASH_SPI_CLK_INIT                  RCC_APB1PeriphClockCmd
#define sFLASH_SPI_AF                        GPIO_AF_SPI2
#define sFLASH_SPI_BaudRate                  SPI_BaudRatePrescaler_8

#define sFLASH_SPI_SCK_PIN                   GPIO_PB13
#define sFLASH_SPI_MISO_PIN                  GPIO_PB14
#define sFLASH_SPI_MOSI_PIN                  GPIO_PB15
#define sFLASH_SPI_CS_PIN                    GPIO_PB12
   
#ifdef __cplusplus
}
#endif

#endif /* __SPI_FLASH_H */


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
