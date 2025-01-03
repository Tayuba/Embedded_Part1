/*
 * stm32f4xx.h
 *
 *  Created on: Sep 15, 2024
 *      Author: Ayuba Tahiru
 */

#ifndef INC_STM32F4XX_H_
#define INC_STM32F4XX_H_


#include <stdint.h>
#include <stddef.h>
#define __vo 					volatile



/*************************************************************************************************************************************************
											PROCESSOR DETAILS, FOR NVIC ISERx AND ICERx REGISTER ADDRESSES
***************************************************************************************************************************************************/
//NVIC ISERx REGISTER ADDRESSES
#define NVIC_ISERO				((__vo uint32_t *)0xE000E100)
#define NVIC_ISER1				((__vo uint32_t *)0xE000E104)
#define NVIC_ISER2				((__vo uint32_t *)0xE000E108)

//ICERx REGISTER ADDRESSES
#define NVIC_ICERO				((__vo uint32_t *)0XE000E180)
#define NVIC_ICER1				((__vo uint32_t *)0XE000E184)
#define NVIC_ICER2				((__vo uint32_t *)0XE000E188)

//IPR REGISTER ADDRESSES
#define NVIC_IPR_BASE_ADDR		((__vo uint32_t *)0xE000E400)


//NVIC Priority Macros
#define NVIC_IRQ_PRIORITY_0				0
#define NVIC_IRQ_PRIORITY_1				1
#define NVIC_IRQ_PRIORITY_2				2
#define NVIC_IRQ_PRIORITY_3				3
#define NVIC_IRQ_PRIORITY_4				4
#define NVIC_IRQ_PRIORITY_5				5
#define NVIC_IRQ_PRIORITY_6				6
#define NVIC_IRQ_PRIORITY_7				7
#define NVIC_IRQ_PRIORITY_8				8
#define NVIC_IRQ_PRIORITY_9				9
#define NVIC_IRQ_PRIORITY_10			10
#define NVIC_IRQ_PRIORITY_11			11
#define NVIC_IRQ_PRIORITY_12			12
#define NVIC_IRQ_PRIORITY_13			13
#define GNVIC_IRQ_PRIORITY_14			14
#define NVIC_IRQ_PRIORITY_15			15

/*
 * Base Addresses of Flash and SRAM Memories
 */

#define FLASH_BASEADDR					0x08000000UL  						/****	main memory	****/
#define SRAM1_BASEADDR					0x20000000UL 						/****	112KB	****/
#define SRAM2_OFFSET					0x00001C00UL 						/****	112KB x 1024 = 1C00	****/
#define ROM_BASEADDR					0x1FFF0000UL						/****	System memory	****/
#define SRAM2							(SRAM1_BASEADDR + SRAM2_OFFSET)		/****	SRAM2_OFFSET + SRAM1_BASEADDR	****/
#define SRAM							SRAM1_BASEADDR





/*
 * Base Addresses of Bus Interfaces (AHBx and APBx)
 */
#define PERIPH_BASEADDR					0x40000000UL						/****	Check Reference manual register boundary addresses	****/
#define APB1_BASEADDR					PERIPH_BASEADDR						/****	Same as the starting address of the Peripheral bus address	****/
#define APB2_BASEADDR					0x40010000UL						/****	Check Reference manual register boundary addresses	****/
#define AHB1_BASEADDR					0x40020000UL						/****	Check Reference manual register boundary addresses	****/
#define AHB2_BASEADDR					0x50000000UL						/****	Check Reference manual register boundary addresses	****/





/*
 * Base Addresses of Peripheral on AHB1 Bus need for my Driver Development
 */
#define GPIOA_BASEADDR					(AHB1_BASEADDR + 0x0000UL)			/****	AHB1_BASEADDR + OFFSET OF GPIOA = GPIOA_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define GPIOB_BASEADDR					(AHB1_BASEADDR + 0x0400UL)			/****	AHB1_BASEADDR + OFFSET OF GPIOB = GPIOB_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define GPIOC_BASEADDR					(AHB1_BASEADDR + 0x0800UL)			/****	AHB1_BASEADDR + OFFSET OF GPIOC = GPIOC_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define GPIOD_BASEADDR					(AHB1_BASEADDR + 0x0C00UL)			/****	AHB1_BASEADDR + OFFSET OF GPIOD = GPIOD_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define GPIOE_BASEADDR					(AHB1_BASEADDR + 0x1000UL)			/****	AHB1_BASEADDR + OFFSET OF GPIOE = GPIOE_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define RCC_BASEADDR 					(AHB1_BASEADDR + 0x3800UL)			/****	AHB1_BASEADDR + OFFSET OF GRCC = RCC_BASEADDR




																			Check Reference manual register boundary addresses	****/
/*
 * Base Addresses of Peripheral on APB1 Bus need for my Driver Development
 */
#define SPI2_BASEADDR					(APB2_BASEADDR + 0x3800UL)			/****	APB1_BASEADDR + OFFSET OF SPI2 = SPI2_BASEADDR/I2S2_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define SPI3_BASEADDR					(APB1_BASEADDR + 0x3C00UL)			/****	APB1_BASEADDR + OFFSET OF SPI3 = SPI2_BASEADDR/I2S3_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define USART2_BASEADDR					(APB1_BASEADDR + 0x4400UL)			/****	APB1_BASEADDR + OFFSET OF USART2 = USART2_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define USART3_BASEADDR					(APB1_BASEADDR + 0x4800UL)			/****	APB1_BASEADDR + OFFSET OF USART3 = USART3_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define UART4_BASEADDR					(APB1_BASEADDR + 0x4C00UL)			/****	APB1_BASEADDR + OFFSET OF UART4 = UART4_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define UART5_BASEADDR					(APB1_BASEADDR + 0x5000UL)			/****	APB1_BASEADDR + OFFSET OF UART5 = UART5_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define I2C1_BASEADDR					(APB1_BASEADDR + 0x5400UL)			/****	APB1_BASEADDR + OFFSET OF I2C1 = I2C1_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define I2C2_BASEADDR					(APB1_BASEADDR + 0x5800UL)			/****	APB1_BASEADDR + OFFSET OF I2C2 = I2C2_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define I2C3_BASEADDR					(APB1_BASEADDR + 0x5C00UL)			/****	APB1_BASEADDR + OFFSET OF I2C3 = I2C3_BASEADDR
																			Check Reference manual register boundary addresses	****/




/*
 * Base Addresses of Peripheral on APB2 Bus need for my Driver Development
 */
#define SPI1_BASEADDR					(APB2_BASEADDR + 0x3000UL)			/****	APB2_BASEADDR + OFFSET OF SPI1 = SPI1_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define SPI4_BASEADDR					(APB2_BASEADDR + 0x3400UL)			/****	APB2_BASEADDR + OFFSET OF SPI4 = SPI4_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define USART1_BASEADDR					(APB2_BASEADDR + 0x1000UL)			/****	APB2_BASEADDR + OFFSET OF USART1 = USART1_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define USART6_BASEADDR					(APB2_BASEADDR + 0x1400UL)			/****	APB2_BASEADDR + OFFSET OF USART6 = USART6_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define SYSCFG_BASEADDR					(APB2_BASEADDR + 0x3800UL)			/****	APB2_BASEADDR + OFFSET OF SYSCFG = SYSCFG_BASEADDR
																			Check Reference manual register boundary addresses	****/
#define EXTI_BASEADDR					(APB2_BASEADDR + 0x3C00UL)			/****	APB2_BASEADDR + OFFSET OF EXTI = EXTI_BASEADDR
																			Check Reference manual register boundary addresses	****/




/*Register Peripherals of GPIO
 *
 * */
typedef struct{
	__vo uint32_t MODER;													/****	GPIO port mode register	****/
	__vo uint32_t OTYPER;													/****	GPIO port output type register	****/
	__vo uint32_t OSPEEDR;													/****	GPIO port output speed register	****/
	__vo uint32_t PUPDR;													/****	GPIO port pull-up/pull-down register	****/
	__vo uint32_t IDR;														/****	GPIO port input data register	****/
	__vo uint32_t ODR;														/****	GPIO port output data register		****/
	__vo uint32_t BSRR;														/****	GPIO port bit set/reset register	****/
	__vo uint32_t LCKR;														/****	GPIO port configuration lock register	****/
	__vo uint32_t AFR[2];													/****	GPIO alternate function register,
																			AFR[0]:LOW and AFR[1]:HIGH	****/
}GPIO_Reg_t;

/*GPIO Peripheral definitions
 *
 * */
#define GPIOA 		((GPIO_Reg_t *)GPIOA_BASEADDR)
#define GPIOB 		((GPIO_Reg_t *)GPIOB_BASEADDR)
#define GPIOC 		((GPIO_Reg_t *)GPIOC_BASEADDR)
#define GPIOD 		((GPIO_Reg_t *)GPIOD_BASEADDR)
#define GPIOE 		((GPIO_Reg_t *)GPIOE_BASEADDR)





/*Register Peripherals of RCC
 *
 * */
typedef struct{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	__vo uint32_t Reserved0;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t Reserved1[2];
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	__vo uint32_t Reserved2;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t Reserved3[2];
	__vo uint32_t AHB1LPENR;
	__vo uint32_t AHB2LPENR;
	__vo uint32_t AHB3LPENR;
	__vo uint32_t Reserved4;
	__vo uint32_t APB1LPENR;
	__vo uint32_t APB2LPENR;
	__vo uint32_t Reserved5[2];
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t Reserved6[2];
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SCFGR;

}RCC_Reg_t;

//RCC Peripheral definitions
#define RCC 		((RCC_Reg_t *)RCC_BASEADDR)


//EXTI Peripheral definitions
#define EXTI 		((EXTI_Reg_t *)EXTI_BASEADDR)


/*Register Peripherals of EXTI*/
typedef struct{
	__vo uint32_t IMR; 													// Interrupt mask register
	__vo uint32_t EMR;													// Event mask register
	__vo uint32_t RTSR;													// Rising trigger selection register
	__vo uint32_t FTSR;													// Falling trigger selection register
	__vo uint32_t SWIER;												// Software interrupt event register
	__vo uint32_t PR;													// Pending register
}EXTI_Reg_t;

//SYSCFG Peripheral definitions
#define SYSCFG 		((SYSCFG_Reg_t *)SYSCFG_BASEADDR)

/*Register Peripherals of SYSCFG*/
typedef struct{
	__vo uint32_t MEMRMP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
     uint32_t RESERVED[2];
	__vo uint32_t CMPCR;

}SYSCFG_Reg_t;


// GPIO base to Port Code Macro
#define GPIO_BASE_TO_PORTCODE(x)		((x == GPIOA)?  0:\
										(x ==  GPIOB) ? 1:\
										(x ==  GPIOC) ? 2:\
										(x ==  GPIOD) ? 3:\
										(x ==  GPIOE) ? 4:0)


// Interrupt Request (IRQ) Number For GPIO
#define IRQ_EXTI0						6
#define IRQ_EXTI1						7
#define IRQ_EXTI2						8
#define IRQ_EXTI3						9
#define IRQ_EXTI4						10
#define IRQ_EXTI9_5						23
#define IRQ_EXTI15_10					40

// Interrupt Request (IRQ) Number For SPI
#define IRQ_SPI1						32
#define IRQ_SPI2						36
#define IRQ_SPI3						51

// Priority amount to be shifted in STM32F407
#define STM32F407_PR_BIT_IMPLEMENTED	4


/*
 * ENABLE CLOCK FOR VARIOUS PERIPHERALS
 * */
//MACRO GPIOx PERIPHERALS ENABLE
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()	(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()	(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()	(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()	(RCC->AHB1ENR |= (1 << 4))

//MACRO I2Cx PERIPHERALS ENABLE
#define I2C1_PCLK_EN()	(RCC->APB1ENR |= (1 << 21))
#define I2C2_PCLK_EN()	(RCC->APB1ENR |= (1 << 22))
#define I2C3_PCLK_EN()	(RCC->APB1ENR |= (1 << 23))

//MACRO SPIx PERIPHERALS ENABLE
#define SPI1_PCLK_EN()	(RCC->APB2ENR |= (1 << 12))
#define SPI2_PCLK_EN()	(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()	(RCC->APB1ENR |= (1 << 15))

//MACRO USARTx PERIPHERALS ENABLE
#define USART1_PCLK_EN()	(RCC->APB2ENR |= (1 << 4))
#define USART2_PCLK_EN()	(RCC->APB1ENR |= (1 << 17))
#define USART3_PCLK_EN()	(RCC->APB1ENR |= (1 << 18))
#define UART4_PCLK_EN()		(RCC->APB1ENR |= (1 << 19))
#define UART5_PCLK_EN()		(RCC->APB1ENR |= (1 << 20))
#define USART6_PCLK_EN()	(RCC->APB2ENR |= (1 << 5))

//MACRO SYSCFG PERIPHERALS ENABLE
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1 << 14))



/*
 * DISABLE CLOCK FOR VARIOUS PERIPHERALS
 * */
//MACRO GPIOx PERIPHERALS DISABLE
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 4))

//MACRO I2Cx PERIPHERALS DISABLE
#define I2C1_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 21))
#define I2C2_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 22))
#define I2C3_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 23))

//MACRO SPIx PERIPHERALS DISABLE
#define SPI1_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 12))
#define SPI2_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 15))

//MACRO USARTx PERIPHERALS DISABLE
#define USART1_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 4))
#define USART2_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 17))
#define USART3_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 18))
#define UART4_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 19))
#define UART5_PCLK_DI()		(RCC->APB1ENR &= ~(1 << 20))
#define USART6_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 5))

//MACRO SYSCFG PERIPHERALS DISABLE
#define SYSCFG_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 14))



/* GPIO RESET
 *
 * */
#define GPIOA_REG_RESET()			do{	(RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0));} while(0)
#define GPIOB_REG_RESET()			do{	(RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1));} while(0)
#define GPIOC_REG_RESET()			do{	(RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2));} while(0)
#define GPIOD_REG_RESET()			do{	(RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3));} while(0)
#define GPIOE_REG_RESET()			do{	(RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4));} while(0)

// SPI RESET
#define SPI1_REG_RESET()			do{	(RCC->APB2RSTR |= (1 << 12));  (RCC->APB2RSTR &= ~(1 << 12));} while(0)
#define SPI2_REG_RESET()			do{	(RCC->APB1RSTR |= (1 << 14));  (RCC->APB1RSTR &= ~(1 << 14));} while(0)
#define SPI3_REG_RESET()			do{	(RCC->APB1RSTR |= (1 << 15));  (RCC->APB1RSTR &= ~(1 << 15));} while(0)





/*Register Peripherals of SPI
 *
 * */
typedef struct{
	__vo uint32_t CR1;												 		/****	SPI control register 1	****/
	__vo uint32_t CR2;												 		/****	SPI control register 2	****/
	__vo uint32_t SR;												 		/****	SPI status register	****/
	__vo uint32_t DR;												 		/****	SPI data register	****/
	__vo uint32_t CRCPR;											 		/****	SPI CRC polynomial register	****/
	__vo uint32_t RXCRCR;											 		/****	SPI RX CRC register	****/
	__vo uint32_t TXCRCR;											 		/****	SPI TX CRC register	****/
	__vo uint32_t I2SCFGR;											 		/****	SPI_I2S configuration register	****/
	__vo uint32_t I2SPR;											 		/****	SPI_I2S prescaler register	****/
}SPI_Reg_t;

/*SIP Peripheral definitions
 *
 * */
#define SPI1 		((SPI_Reg_t *)SPI1_BASEADDR)
#define SPI2 		((SPI_Reg_t *)SPI2_BASEADDR)
#define SPI3 		((SPI_Reg_t *)SPI3_BASEADDR)





#define ENABLE 					1
#define DISABLE				 	0
#define SET						ENABLE
#define RESET					DISABLE
#define GPIO_PIN_SET			SET
#define GPIO_PIN_RESET			RESET
#define FLAG_RESET				RESET
#define FLAG_SET				SET

#define MASK_PIN				0x00000001

#include "F407_GPIO_Driver.h"
#endif /* INC_STM32F4XX_H_ */
