#include "stm32l476xx.h"
void Delay_MS(int delay);
void USART2_init(void);
char USART2_Write(int ch);
void USART2_Text_Write(char *text);
char USART2_Read(void);

int main(void)
{

	char c;
	USART2_init();

	while(1)
	{
		c = USART2_Read();
		if(c=='a')
			USART2_Write('A');
	    if(c=='b')
	    	USART2_Write('B');
	}

}

void USART2_init(void)
{
	RCC->AHB2ENR  |=  (1<<0);             // Enable clock for GPIOA
	RCC->APB1ENR1 |=  (1<<17);            // Enable clock for USART2
	GPIOA->AFR[0] |=  (7<<12);            // Set PA3 as RX pin
	GPIOA->AFR[0] |=  (7<<8);             // Set PA2 as TX pin
	GPIOA->MODER  |=  ((1<<5) | (1<<7));  // Set mode as alternate function mode
	GPIOA->MODER  &= ~((1<<4) | (1<<6));

	USART2->BRR    =  0x208D;             // 9600 baud rate for 40MHz
	USART2->CR1   |=  ((1<<2) | (1<<3) | (1<<0));
}

char USART2_Write(int ch)
{
	while(!(USART2->ISR & (1<<7))){}
	USART2->TDR = (ch & 0xff);
	return ch;
}

void USART2_Text_Write(char *text)
{
	while(*text)
		USART2_Write(*text++);
}

char USART2_Read(void)
{
	while(!(USART2->ISR & (1<<5))){}
	return (USART2->RDR);
}

void Delay_MS(int delay)
{
	int i;
	for(;delay>0;delay--)
		for(i=0;i<=3195;i++);
}
