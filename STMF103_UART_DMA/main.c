#include "main.h"

uint8_t RxBuf[RX_SIZE];
uint8_t MainBuf[50];

int main (void)
{
  GPIO_USART_UsrInit();
  GPIO_LED_UsrInit();
  USART1_UsrInit();
  DMA1_UsrInit();
  DMA1_UsrConfig(&USART1->DR, RxBuf,RX_SIZE);
  NVIC_SetPriority(USART1_IRQn, 0);
  NVIC_EnableIRQ(USART1_IRQn);
  while(1)
  {
  }
}
