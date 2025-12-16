#include "hw_init.h"

// --- GPIO for USART1 Init ---
void GPIO_USART_UsrInit (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  // --- USART1_TX, PA9 ---
  GPIOA->CRH &= ~GPIO_CRH_CNF9;
  GPIOA->CRH |= GPIO_CRH_CNF9_1;
  GPIOA->CRH |= GPIO_CRH_MODE9;
  // --- USART1_RX, PA10 ---
  GPIOA->CRH &= ~GPIO_CRH_CNF10;
  GPIOA->CRH |= GPIO_CRH_CNF10_1;
  GPIOA->CRH |= GPIO_CRH_MODE10;
}

// --- GPIO LED PB2 ---
void GPIO_LED_UsrInit (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
  
  GPIOB->CRL &= ~GPIO_CRL_CNF2;
  GPIOB->CRL &= ~GPIO_CRL_MODE2;
  GPIOB->CRL |= GPIO_CRL_MODE2_1;
}

// --- USART1 Init ---
void USART1_UsrInit (void)
{
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
  USART1->BRR = (39 << 4) | 1;//115200
  USART1->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
  USART1->CR3 |= USART_CR3_DMAR | USART_CR3_DMAT;
}

// --- DMA Init ---
void DMA1_UsrInit (void)
{
  RCC->AHBENR |= RCC_AHBENR_DMA1EN;
  // --- DMA RX UART1 ---
  DMA1_Channel5->CCR |= DMA_CCR5_TEIE | DMA_CCR5_TCIE | DMA_CCR5_HTIE;
  DMA1_Channel5->CCR &= ~DMA_CCR5_DIR;
  DMA1_Channel5->CCR |= DMA_CCR5_CIRC;
  DMA1_Channel5->CCR &= ~DMA_CCR5_PINC;
  DMA1_Channel5->CCR |= DMA_CCR5_MINC;
  DMA1_Channel5->CCR &= ~DMA_CCR5_MSIZE;
  DMA1_Channel5->CCR &= ~DMA_CCR5_PSIZE;
  DMA1_Channel5->CCR &= ~DMA_CCR5_PL;
}

// --- DMA User Config ---
void DMA1_UsrConfig(volatile uint32_t *srcAddr, uint8_t *destAddr, uint16_t dSize)
{
  DMA1_Channel5->CCR &= ~DMA_CCR1_EN;
  DMA1_Channel5->CNDTR = dSize;
  DMA1_Channel5->CPAR = (uint32_t)srcAddr;
  DMA1_Channel5->CMAR = (uint32_t)destAddr;
  DMA1_Channel5->CCR |= DMA_CCR1_EN;
}