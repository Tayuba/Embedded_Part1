/*
 * 2LED_PB.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Ayuba Tahiru
 */



#include "stm32f4xx.h"

void delay(void);

int main(void){

	GPIO_Handle_t led, btn = {0};

	led.pGPIOx = GPIOD;

	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_VH;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTY_PUSPUL;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPD_NO;

	btn.pGPIOx = GPIOA;

	btn.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
	btn.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_INPUT;
	btn.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_VH;
	btn.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPD_NO;



    GPIO_Init(&led);
    GPIO_Init(&btn);



    while(1){
    	if (GPIO_ReadInputPin(GPIOA, GPIO_PIN_NO_0)) {
    		delay();
    		GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
		}
    }
	return 0;
}


void delay(void){
	for (uint32_t i = 0; i < 500000/2; i++);
}
