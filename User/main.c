/*
 * Replacement firmware for XY-CD60L Charge Controller Battery Protection Board
 * Craig Peacock
 * July 2025
 * 
 */ 
#include "hk32f030m.h"
#include "systick_delay.h"
#include "gpio.h"
#include "usart.h"
#include "adc.h"

int main(void)
{
    int ret;

    SysTick_Init();
    GPIO_Config();
    USART_Config();
    printf("XY-CD60L Multipurpose Replacement Firmware\r\n");
    ADC_Config();

    printf("Converting ADC CH1 (Input Voltage)");

    while (1)
    {
        ret = ADC_ConvertByChannel(ADC_Channel_1);
        /*
         * Ch1 is connected to the power supply input (VIN+).
         * This occurs via a voltage divider consisting of a 100k/5.1k resistor network (x20.6078)
         * The converter is 12 bits (4096 steps) with FS/Vref being 3.3V
         * Hence each step is 3.3/4096 x 20.6078 x 1000 (convert to mV)
         */
        ret = (uint16_t)(ret * 16.602963);
        printf("ADC CH0: %02d.%02d\r\n", ret / 1000, (ret % 1000)/10);

        SysTick_DelayMs(100);
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char* file , uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */    
       /* Infinite loop */
    
    while (1)
  {        
  }
}
#endif /* USE_FULL_ASSERT */
