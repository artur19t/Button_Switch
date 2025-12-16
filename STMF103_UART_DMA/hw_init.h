#include "stm32f10x.h"                  // Device header

void GPIO_USART_UsrInit (void);
void GPIO_LED_UsrInit (void);
void USART1_UsrInit (void);
void DMA1_UsrInit (void);
void DMA1_UsrConfig(volatile uint32_t *srcAddr, uint8_t *destAddr, uint16_t dSize);