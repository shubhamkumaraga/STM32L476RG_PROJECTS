#include<stm32l476xx.h>

void delayMS(int delay);
void USART2_Init(void);
char USART2_Read(void);

int main(void)
{
	char c;
	RCC->AHB2ENR |= (1<<0); // ENABLE GPIOA CLOCK
	GPIOA->MODER |= (1<<10); // SET PIN5 (INBUILT LED) AS GENERAL PURPOSE OUTPUT MODE (01)
	GPIOA->MODER &= ~(1<<11);

	USART2_Init();

	while(1)
	{
		c = USART2_Read();
		if(c=='A')
		{
			// ENABLE BUILTIN LED
			// GPIOA->ODR |= (1<<5);
			GPIOA->BSRR |= (1<<5);
		}
		else
		{
			// DISABLE BUILTIN LED
			// GPIOA->ODR &= ~(1<<5);
			GPIOA->BSRR |= (1<<21);
		}
	}
}

void USART2_Init(void)
{
	// USART2 -> APB1 BUS
	RCC->APB1ENR1 |= (1<<17);
	// PA3 RX PIN -> AHB2 BUS - GPIOA
	RCC->AHB2ENR |= (1<<0);
	// ALTERNATIVE FUNCTION REGISTER, 0111 FOR PA3 PIN
	GPIOA->AFR[0] |= (7<<12);
	GPIOA->AFR[0] &=  ~(1<<15);
	// MODE REGISTER, 10 FOR PA3 PIN, ALTERNATIVE FUNCITON MODE
	GPIOA->MODER |= (1<<7);
	GPIOA->MODER &= ~(1<<6);
	// USART2 BAUD RATE 9600 FOR 80MHz
	//0x208D - 9600 baud rate for 40MHz
	USART2->BRR |= 0x0683; // 2400 at 80MHz
	USART2->CR1 |= (1<<2); // RE ENABLED
	USART2->CR1 |= (1<<0); // UE ENABLED
}

char USART2_Read(void)
{
	while(!(USART2->ISR & (1<<5)));
	return USART2->RDR;
}

void delayMS(int delay)
{
	int i;
	for( ; delay>0; delay--)
		for(i=0; i<=3195; i++);
}
