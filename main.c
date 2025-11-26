#include "stm32f10x.h"                  // Device header


void GPIOB_LED_Init(void);
void SetSysClockTo72(void);
void GPIOA_But_Init(void);
void LED_switch(int);


int main()
{
  SetSysClockTo72();
  GPIOB_LED_Init();
  GPIOA_But_Init();
  int But_state = 0;
  while(1)
  {
    But_state = !READ_BIT(GPIOA -> IDR, GPIO_IDR_IDR0);
    LED_switch(But_state);
  }
}

void LED_switch (int but_state)
{
  if (but_state)
  {
    GPIOB -> BSRR = GPIO_BSRR_BR2;
  }else
  {
    GPIOB -> BSRR = GPIO_BSRR_BS2;
  }
}
// --- Init LED pin ---
void GPIOB_LED_Init(void)
{
  RCC -> APB2ENR |= RCC_APB2ENR_IOPBEN;
  // --- CLear Bits of PB2 ---
  GPIOB -> CRL &= ~(GPIO_CRL_CNF2 | GPIO_CRL_MODE2);
  // --- Set conf MODE2 = 10, CNF2 = 00 ---
  GPIOB -> CRL |= GPIO_CRL_MODE2_1;
}

// --- Init button pin ---
void GPIOA_But_Init(void)
{
  RCC -> APB2ENR |= RCC_APB2ENR_IOPAEN;
  // --- Clear bits of PA0 ---
  GPIOA -> CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
  // --- Set conf MODE0 = 00, CNF0 = 10 ---
  GPIOA -> CRL |= GPIO_CRL_CNF0_1;
}

void SetSysClockTo72(void)
{
  // --- Enable HSE ---
  RCC->CR |= RCC_CR_HSEON;

  // --- Wait HSE is ready ---
  while (!READ_BIT(RCC->CR, RCC_CR_HSERDY)) {}

  // --- Setting Flash ---
  FLASH->ACR |= FLASH_ACR_PRFTBE;        // Prefetch enable
  FLASH->ACR &= ~FLASH_ACR_LATENCY;      
  FLASH->ACR |= FLASH_ACR_LATENCY_2;     // 2 wait states 72

  // --- Setting bus ---
  RCC->CFGR &= ~RCC_CFGR_HPRE;  
  RCC->CFGR |= RCC_CFGR_HPRE_DIV1;  // AHB setting

  RCC->CFGR &= ~RCC_CFGR_PPRE1;
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 max = 36MHz

  RCC->CFGR &= ~RCC_CFGR_PPRE2;
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 setting

  // --- Setting PLL ---
  RCC->CFGR &= ~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLMULL);
  RCC->CFGR |= RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL9;  // HSE*9 = 72

  // --- Enable PLL ---
  RCC->CR |= RCC_CR_PLLON;

  // --- Wait PLL ---
  while (!READ_BIT(RCC->CR, RCC_CR_PLLRDY)) {}

  // --- Switch SYSCLK to PLL ---
  RCC->CFGR &= ~RCC_CFGR_SW;
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  // --- Wait for switching ---
  while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) {}
}
