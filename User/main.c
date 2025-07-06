/*
 * Replacement firmware for XY-CD60L Charge Controller Battery Protection Board
 * Craig Peacock
 * July 2025
 * 
 */ 
#include "hk32f030m.h"
#include "systick_delay.h"
#include "gpio.h"

int main(void)
{
    SysTick_Init();
    GPIO_Config();

    while (1)
    {
        // Button Up turns on Backlight
        if (GPIO_ReadInputDataBit(BTN_UP_GPIO_PORT, BTN_UP_GPIO_PIN)) {
            GPIO_ResetBits(BACKLIGHT_GPIO_PORT, BACKLIGHT_GPIO_PIN);
        } else {
            GPIO_SetBits(BACKLIGHT_GPIO_PORT, BACKLIGHT_GPIO_PIN);
        }

        // Button down turns on relay
        if (GPIO_ReadInputDataBit(BTN_DOWN_GPIO_PORT, BTN_DOWN_GPIO_PIN)) {
            GPIO_ResetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
        } else {
            GPIO_SetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
        }

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
