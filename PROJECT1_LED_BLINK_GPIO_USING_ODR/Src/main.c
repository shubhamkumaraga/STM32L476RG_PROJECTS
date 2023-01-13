#include "stm32l476xx.h"
void Delay_MS(int delay);

int main(void)
{

	RCC->AHB2ENR |= (1<<0); // Enable clock for GPIOA
	GPIOA->MODER |= (1<<10); // Set the mode to general purpose output mode
	GPIOA->MODER &= ~(1<<11);

	while(1)
	{
		// Using ODR register to turn on built in LED at PA5
		GPIOA->ODR |= (1<<5);
		
		// Using BSRR register to turn on and off built in LED at PA5
		/*
		GPIOA->BSRR |= (1<<5);
		Delay_MS(10);
		GPIOA->BSRR |= (1<<21);
		Delay_MS(10);
		*/
	}

}

void Delay_MS(int delay)
{
	int i;
	for(;delay>0;delay--)
		for(i=0;i<=3195;i++);
}
