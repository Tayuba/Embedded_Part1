/*
 * 1LED_ToggleOD.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Ayuba Tahiru
 */



#include "stm32f4xx.h"

void delay(void);

int main(void){

	GPIO_Handle_t led = {0};

	led.pGPIOx = GPIOD;

	led.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_15;
	led.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUTPUT;
	led.GPIO_PinConfig.GPIO_PinSpeed = GPIO_OSPEED_L;
	led.GPIO_PinConfig.GPIO_PinOPType = GPIO_OTY_OPEN_DRAIN;
	led.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PUPD_PULUP;


    GPIO_Init(&led);


    while(1){
    	GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_15);
    	delay();
    }
	return 0;
}


void delay(void){
	for (uint32_t i = 0; i < 500000/3; i++);
}
