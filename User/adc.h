
void ADC_Config(void);
uint16_t ADC_ConvertByChannel(uint32_t ADC_Channel);

// PD5/AN0: VOUT
#define VOUT_GPIO_PORT      GPIOD
#define VOUT_GPIO_CLK       RCC_AHBPeriph_GPIOD
#define VOUT_GPIO_PIN       GPIO_Pin_5

// PD6/AN1: VIN 
#define VIN_GPIO_PORT       GPIOD
#define VIN_GPIO_CLK        RCC_AHBPeriph_GPIOD
#define VIN_GPIO_PIN        GPIO_Pin_6
