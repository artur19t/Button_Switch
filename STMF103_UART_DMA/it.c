#include "it.h"

uint8_t index_buf = 0;

void USART1_IRQHandler(void)
{
  if(USART1->SR & USART_SR_IDLE)
  {
    volatile uint32_t tmp;
    tmp = USART1->SR;
    tmp = USART1->DR;
    uint16_t received = RX_SIZE - DMA1_Channel5->CNDTR;
    USART_UsrLogic(RxBuf, received);
    
    DMA1_Channel5->CCR &= ~DMA_CCR1_EN;
    DMA1_Channel5->CNDTR = RX_SIZE;
    DMA1_Channel5->CCR |= DMA_CCR1_EN;
  }
}
