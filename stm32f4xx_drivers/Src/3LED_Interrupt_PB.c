/*
 * 3LED_Interrupt_PB.c
 *
 *  Created on: Dec 15, 2024
 *      Author: Ayuba Tahiru
 */



#include "stm32f4xx.h"

void delay(void);

int main(void){

	GPIO_Handle_t led = {0}, btn = {0};

	led.pGPIOx = GPIOD;

	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_VH;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTY_PUSPUL;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPD_NO;

    GPIO_Init(&led);

	btn.pGPIOx = GPIOA;

	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INP_FE_T;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_VH;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPD_NO;




    GPIO_Init(&btn);

   // IRQ Configuration
    GPIO_InterruptPriorityConfig(IRQ_EXTI4, NVIC_IRQ_PRIORITY_15);
    GPIO_InterruptConfig(IRQ_EXTI4, ENABLE);

    while(1);

//	return 0;
}


void delay(void){
	for (uint32_t i = 0; i < 500000/2; i++);
}

void EXTI4_IRQHandler (void){
	delay();
	GPIO_IRQHandler(GPIO_PIN_NO_4);
	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
}
