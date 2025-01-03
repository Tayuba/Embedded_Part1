/*
 * F407_GPIO_Driver.c
 *
 *  Created on: Oct 26, 2024
 *      Author: Ayuba Tahiru
 */

#include "F407_GPIO_Driver.h"





// Peripheral Clock setup
/************************************************************************************************
 *@func name							- GPIO_PeriphControl
 *
 *@brief								- Function to enable or disable peripheral clock for a given GPIO port
 *
 *@param1								- Base Address of GPIO peripheral
 *@param2								- Enable or Disable Macros
 *
 *@return								- none
 *
 *@Note									- none
 */
void GPIO_PeriphControl(GPIO_Reg_t *pGPIOx, uint8_t EnorDis){
	if(EnorDis == ENABLE){
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_EN();
		}
		else if(pGPIOx == GPIOB){
			GPIOB_PCLK_EN();
		}
		else if(pGPIOx == GPIOC){
			GPIOC_PCLK_EN();
		}
		else if(pGPIOx == GPIOD){
			GPIOD_PCLK_EN();
		}
		else if(pGPIOx == GPIOE){
			GPIOE_PCLK_EN();
		}

	}else{
		if(pGPIOx == GPIOA){
			GPIOA_PCLK_DI();
		}
		else if(pGPIOx == GPIOB){
			GPIOB_PCLK_DI();
		}
		else if(pGPIOx == GPIOC){
			GPIOC_PCLK_DI();
		}
		else if(pGPIOx == GPIOD){
			GPIOD_PCLK_DI();
		}
		else if(pGPIOx == GPIOE){
			GPIOE_PCLK_DI();
		}
	}
}





// Initialize
/************************************************************************************************
 *@func name							- GPIO_Init
 *
 *@brief								- Function to initialize GPIO
 *
 *@param1								- Base Address of GPIO Handle
 *
 *@return								- none
 *
 *@Note									- none
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle){
	// Enable Peripheral clock
	GPIO_PeriphControl(pGPIOHandle->pGPIOx, ENABLE);

	//1. Configure MODE of GPIO
	uint32_t temp = 0; //hold register mode temporary
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG){
		//Mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 	    				//clearing
		pGPIOHandle->pGPIOx->MODER |= temp; 																		// setting

	}else{
		// Configure GPIO port to selection  in SYSCG
		/* Interrupt mode, at peripheral side */
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_INP_FE_T){
			pGPIOHandle->pGPIOx->MODER &= ~(0x3 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//1. Falling Edge trigger configured
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 					    				// set falling edge
			EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 					   					// reset rising edge

		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_INP_RE_T){
			//2. Rising Edge trigger configured
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 					     				// set rising edge
			EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 					     				// reset falling edge

		}else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_INP_FERE_T){
			//3.  Both Falling and Rising Edge trigger configured
			EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 						 				// set falling edge
			EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 						 				// set rising edge
		}

		SYSCFG_PCLK_EN();
		uint8_t temp1, temp2;
		uint8_t portCode = GPIO_BASE_TO_PORTCODE(pGPIOHandle->pGPIOx);								   				// REturn the port code(PA...PI for the EXTI register
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 4;                                	   				// Select which EXTI(0...3) register to Configure
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;									   				// Select which EXTI?(0...15) bit to store values
																					   	   	   	   	   	   	   	   	// Enable SYSCFG clock
		SYSCFG->EXTICR[temp1] = (portCode << (4 * temp2));											   				// Select EXTIx register and the respective bits

		// Interrupt request from line x is not masked or disabled
		EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}
	temp = 0;

	//2. Configure Speed of GPIO
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 			  			// clearing
	pGPIOHandle->pGPIOx->OSPEEDR |= temp; 																  			// setting
	temp = 0;

	//3. Configure Pull up Pull down of GPIO
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 							// clearing
	pGPIOHandle->pGPIOx->PUPDR |= temp; 																			//setting
	temp = 0;

	//4. Configure Output Type of GPIO
	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 <<  pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 						// clearing
	pGPIOHandle->pGPIOx->OTYPER |= temp; 																		//setting
	temp = 0;



	//5. Alternative Function
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFUNC){
		uint8_t temp1, temp2;
		temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandle->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2 )); 	// clearing
		pGPIOHandle->pGPIOx->AFR[temp1] |= (pGPIOHandle->GPIO_PinConfig.GPIO_PinAlteFuncMode << (4 * temp2 ));	 	// setting
	}

}


// De-Initialize
/************************************************************************************************
 *@func name							- GPIO_DeInit
 *
 *@brief								- Function to reset or disable GPIO
 *
 *@param1								- Base Address of GPIO peripheral
 *
 *@return								-	none
 *
 *@Note									-	none
 */
void GPIO_DeInit(GPIO_Reg_t *pGPIOx){
	if(pGPIOx == GPIOA){
		GPIOA_REG_RESET();
	}
	else if(pGPIOx == GPIOB){
		GPIOB_REG_RESET();
	}
	else if(pGPIOx == GPIOC){
		GPIOC_REG_RESET();
	}
	else if(pGPIOx == GPIOD){
		GPIOD_REG_RESET();
	}
	else if(pGPIOx == GPIOE){
		GPIOE_REG_RESET();
	}
}





// Read Data Pin
/**********************************************************************************************
*@func name								- GPIO_ReadInputPin
*
*@brief									- Function reads the values in a given GPIO pin
*
*@param1								- Base Address of GPIO peripheral
*@param2								- GPIO Pin number
*
*@return								- Return the pin value 0 or 1
*
*@Note									- none
*/
uint8_t GPIO_ReadInputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum){
	uint8_t IDR_value;
//	IDR_value = (uint8_t)(pGPIOx->IDR >> PinNum & 0x00000001);
	IDR_value = (uint8_t)(pGPIOx->IDR >> PinNum & MASK_PIN);
	return IDR_value;
}

// Read Data Port
/**********************************************************************************************
*@func name								- GPIO_ReadInputPort
*
*@brief									- Function reads the values in GPIO ports
*
*@param1								- Base Address of GPIO peripheral
*@param2								- GPIO Port number
*
*@return								- Return the port values
*
*@Note									- none
*/
uint16_t GPIO_ReadInputPort(GPIO_Reg_t *pGPIOx){
	uint16_t PORT_value;
	PORT_value = (uint16_t)(pGPIOx->IDR);
	return PORT_value;
}





// Write Data for Pin
/**********************************************************************************************
*@func name								- GPIO_WriteOutputPin
*
*@brief									- Function writes values in GPIO pin
*
*@param1								- Base Address of GPIO peripheral
*@param2								- GPIO Pin number
*@param3								- Value to be written
*
*@return								- none
*
*@Note									- none
*/
void GPIO_WriteOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum, uint8_t Val){
	if(Val == GPIO_PIN_SET){
		pGPIOx->ODR |= (1 << PinNum);
	}else{
		pGPIOx->ODR &= ~(1 << PinNum);
	}
}

// Write Data for Port
/**********************************************************************************************
*@func name								- GPIO_WriteOutputPort
*
*@brief									- Function writes values in GPIO port
*
*@param1								- Base Address of GPIO peripheral
*@param2								- Value to be written
*
*@return								- none
*
*@Note									- none
*/
void GPIO_WriteOutputPort(GPIO_Reg_t *pGPIOx, uint16_t Val){
	pGPIOx->ODR = Val;
}




// Toggle Output Pin
/**********************************************************************************************
*@func name								- GPIO_ToggleOutputPin
*
*@brief									- Function toggles value in GPIO pin from high to low or vice versa
*
*@param1								- Base Address of GPIO peripheral
*@param2								- GPIO Pin number
*
*@return								- none
*
*@Note									- none
*/
void GPIO_ToggleOutputPin(GPIO_Reg_t *pGPIOx, uint8_t PinNum){
	pGPIOx->ODR ^= (1 << PinNum);
}


/* Interrupt Configuration and Interrupt Service Routine Handling at processor side.
 * This configuration is done using Cortex M4 Generic User Guide */
/************************************************************************************************
 *@func name							- GPIO_InterruptConfig
 *
 *@brief								- Function configures interrupt at the processor side of the peripheral.
 *
 *
 *@param1								- IRQ number of the interrupt been used in the MCU Cortex M4 peripheral
 *@param2								- Enable variable of the interrupt been used in the MCU Cortex M4 peripheral
 *
 *@return								- none
 *
 *@Note									- Even though Cortex M4 has 8 Nested Vector Interrupt Controllers available (NVIC),
 *										  STM32F407 does not use more than three of this NVIC
 */
void GPIO_InterruptConfig(uint8_t IRQNum, uint8_t EnorDis){
	if(EnorDis == ENABLE){
		if(IRQNum <= 31){
			// ISRE0 Register to be programmed
			*(NVIC_ISERO) |= (1 << IRQNum);

		} else if(IRQNum >= 31 && IRQNum <64){
			// ISRE1 Register to be programmed
			*(NVIC_ISER1) |= (1 << (IRQNum % 32));

		} else if(IRQNum >= 64 && IRQNum <96){
			// ISRE2 Register to be programmed
			*(NVIC_ISER2) |= (1 << (IRQNum % 64));
		}
	}else{
		if(IRQNum <= 31){
			// ICRE0 Register to be programmed
			*(NVIC_ICERO) |= (1 << (IRQNum % 32));

		} else if(IRQNum >= 31 && IRQNum <64){
			// ICRE1 Register to be programmed
			*(NVIC_ICER1) |= (1 << (IRQNum % 32));

		} else if(IRQNum >= 64 && IRQNum <96){
			// ICRE2 Register to be programmed
			*(NVIC_ICER2) |= (1 << (IRQNum % 64));
		}
	}
}


// Configuration of interrupt priority
/************************************************************************************************
 *@func name							- GPIO_InterruptPriorityConfig
 *
 *@brief								- Function configures priority for interrupt at the processor side of the peripheral.
 *
 *
 *@param1								- IRQ number of the interrupt been used in the MCU Cortex M4 peripheral
 *@param2								- IRQ priority of the interrupt been used in the MCU Cortex M4 peripheral

 *
 *@return								- none
 *
 *@Note									- One interrupt priority register is enough since only 3 interrupt set-enable registers are used.
 *										  One interrupt priority register is divided into four sections, for which each section handles one interrupt set-enable registers.
 *										  Priority bits implementation are done in most-significant bit of the section of the register, and the number of implementation is
 *										  processor specific, so kindly check MCU providers ref. manual
 */
void GPIO_InterruptPriorityConfig(uint8_t IRQNum, uint32_t IRQ_Priority){
	uint8_t iprx 		 = IRQNum / 4; 																			// To select interrupt priority register
	uint8_t iprx_section  = IRQNum % 4;       																	// To select section of selected interrupt priority register above
	uint8_t amount_shift = (8 * iprx_section) + (8 - STM32F407_PR_BIT_IMPLEMENTED); 							// STM32F407_PR_BIT_IMPLEMENTED has 4 bit implementation of priority, MCU such as TI.
	*(NVIC_IPR_BASE_ADDR + iprx) |= (IRQ_Priority << amount_shift);
}

// Interrupt Service Routine
/**********************************************************************************************
*@func name								- GPIO_IRQHandler
*
*@brief									- Function handles interrupt service routine
*
*@param1								- GPIO Pin number
*
*@return								- none
*
*@Note									- none
*/
void GPIO_IRQHandler(uint8_t PinNum){
	// checking the EXTI PR register corresponding to the pin number, set or not
	if(EXTI->PR & (1 << PinNum)){
		// Clear if set
		EXTI->PR |= (1 << PinNum);
	}
}
