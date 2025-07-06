
void USART_Config(void);

// PD1: USART TXD
#define TXD_GPIO_PORT     GPIOD
#define TXD_GPIO_CLK      RCC_AHBPeriph_GPIOD
#define TXD_GPIO_PIN      GPIO_Pin_1

// PD7 (VCAP): USART RXD
#define RXD_GPIO_PORT     GPIOD
#define RXD_GPIO_CLK      RCC_AHBPeriph_GPIOD
#define RXD_GPIO_PIN      GPIO_Pin_7

#define  DEBUG_USART_BAUDRATE   115200
