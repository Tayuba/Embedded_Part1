/*
 * F407_GPIO_Driver.h
 *
 *  Created on: Oct 26, 2024
 *      Author: Ayuba Tahiru
 */

#ifndef INC_F407_GPIO_DRIVER_H_
#define INC_F407_GPIO_DRIVER_H_

#include "stm32f4xx.h"





/*
 * GPIO pin configurable
 * */
typedef struct{
	uint8_t GPIO_PinNumber;								/*** Possible values from @GPIO_PIN_NUMBERS	***/
	uint8_t GPIO_PinMode;								/*** Possible values from @GPIO_PIN_MODES	***/
	uint8_t GPIO_PinSpeed;								/*** Possible values from @GPIO_PIN_SPEED	***/
	uint8_t GPIO_PinPuPdControl;						/*** Possible values from @GPIO_PIN_PULL_UP_PULL_DOWN	***/
	uint8_t GPIO_PinOPType;								/*** Possible values from @GPIO_PIN_OUTPUT_TYPE	***/
	uint8_t GPIO_PinAlteFuncMode;
}GPIO_PinConfig;

/*
 * GPIOx Handle Structure*
 */
typedef struct {
	GPIO_Reg_t 		*pGPIOx;   							/*** Holds base address of GPIO port to which the pin belongs	***/
	GPIO_PinConfig	GPIO_PinConfig;						/*** Holds GPIO pin configuration settings	***/
}GPIO_Handle_t;





/*
 *@GPIO_PIN_MODES
 * */
//GPIO Pin Mode Macros
#define GPIO_MODE_INPUT					0
#define GPIO_MODE_OUTPUT				1
#define GPIO_MODE_ALTFUNC				2
#define GPIO_MODE_ANALOG				3
#define GPIO_MODE_INP_FE_T				4
#define GPIO_MODE_INP_RE_T				5
#define GPIO_MODE_INP_FERE_T			6

/*
 *@GPIO_PIN_OUTPUT_TYPE
 * */
//GPIO Output Types Macros
#define GPIO_OTY_PUSPUL					0
#define GPIO_OTY_OPEN_DRAIN				1

/*
 *@GPIO_PIN_SPEED
 * */
//GPIO Output Speed Macros
#define GPIO_OSPEED_L					0
#define GPIO_OSPEED_M					1
#define GPIO_OSPEED_H					2
#define GPIO_OSPEED_VH					3

/*
 *@GPIO_PIN_PULL_UP_PULL_DOWN
 * */
//GPIO Pull Up, Pull Down Macros
#define GPIO_PUPD_NO					0
#define GPIO_PUPD_PULUP					1
#define GPIO_PUPD_PULDOWN				2

/*
 *@GPIO_PIN_NUMBERS
 * */
//GPIO Pins Macros
#define GPIO_PIN_NO_0					0
#define GPIO_PIN_NO_1					1
#define GPIO_PIN_NO_2					2
#define GPIO_PIN_NO_3					3
#define GPIO_PIN_NO_4					4
#define GPIO_PIN_NO_5					5
#define GPIO_PIN_NO_6					6
#define GPIO_PIN_NO_7					7
#define GPIO_PIN_NO_8					8
#define GPIO_PIN_NO_9					9
#define GPIO_PIN_NO_10					10
#define GPIO_PIN_NO_11					11
#define GPIO_PIN_NO_12					12
#define GPIO_PIN_NO_13					13
#define GPIO_PIN_NO_14					14
#define GPIO_PIN_NO_15					15





// Peripheral Clock setup
void GPIO_PeriphControl(GPIO_Reg_t *pGPIOx, uint8_t EnorDis);

// Initialize and De-Initialize
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);
void GPIO_DeInit(GPIO_Reg_t *pGPIOx);

// Read and Write Data
uint8_t GPIO_ReadInputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum);
uint16_t GPIO_ReadInputPort(GPIO_Reg_t *pGPIOx);
void GPIO_WriteOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum, uint8_t Val);
void GPIO_WriteOutputPort(GPIO_Reg_t *pGPIOx, uint16_t Val);
void GPIO_ToggleOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum);

// Interrupt Configuration and Interrupt Service Routine Handling
void GPIO_InterruptConfig(uint8_t IRQNum, uint8_t EnorDis);
void GPIO_IRQHandler(uint8_t PinNum);
void GPIO_InterruptPriorityConfig(uint8_t IRQNum ,uint32_t IRQ_Priority);
#endif /* INC_F407_GPIO_DRIVER_H_ */
