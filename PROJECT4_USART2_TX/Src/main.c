#include<stm32l476xx.h>

void delayMS(int delay);
void USART2_Init(void);
void USART2_Write(int ch);

int main(void)
{
	USART2_Init();

	while(1)
	{
		USART2_Write('S');
		USART2_Write('H');
		USART2_Write('U');
		USART2_Write('B');
		USART2_Write('H');
		USART2_Write('A');
		USART2_Write('M');
		USART2_Write('\r');
		USART2_Write('\n');
		delayMS(100);
	}
}

void USART2_Init(void)
{
	// USART2 -> APB1 BUS
	RCC->APB1ENR1 |= (1<<17);
	// PA2 TX PIN -> AHB2 BUS
	RCC->AHB2ENR |= (1<<0);
	// ALTERNATIVE FUNCTION REGISTER, 0111 FOR PA2 PIN
	GPIOA->AFR[0] |= (7<<8);
	GPIOA->AFR[0] &=  ~(1<<11);
	// MODE REGISTER, 10 FOR PA2 PIN, ALTERNATIVE FUNCITON MODE
	GPIOA->MODER |= (1<<5);
	GPIOA->MODER &= ~(1<<4);
	// USART2 BAUD RATE 9600 FOR 80MHz
	//0x208D // 9600 baud rate for 40MHz
	USART2->BRR |= 0x0683; // 2400 at 80MHz
	USART2->CR1 |= (1<<3); // TE ENABLED
	USART2->CR1 |= (1<<0); // UE ENABLED
}

void USART2_Write(int ch)
{
	while(!(USART2->ISR & (1<<7)));
	USART2->TDR = (ch & 0xFF);
}

void delayMS(int delay)
{
	int i;
	for( ; delay>0; delay--)
		for(i=0;i<=3195; i++);
}
