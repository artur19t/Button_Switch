#include "hw_init.h"

int main (void)
{
  GPIO_USART_UsrInit();
  GPIO_LED_UsrInit();
  USART1_UsrInit();
  DMA1_UsrInit();
  while(1)
  {
  }
}
