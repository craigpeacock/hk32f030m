/*
 * Replacement firmware for XY-CD60L Charge Controller Battery Protection Board
 * Craig Peacock
 * July 2025
 * 
 */ 
#include "hk32f030m.h"
#include "systick_delay.h"
#include "gpio.h"

void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    // Enable AHB Clock
    RCC_AHBPeriphClockCmd(BACKLIGHT_GPIO_CLK | RELAY_GPIO_CLK | LCD_DATA_GPIO_CLK | LCD_WR_GPIO_CLK | LCD_CS_GPIO_CLK , ENABLE);

    // LED1: Output, push-pull, speed 10Mhz
    GPIO_InitStructure.GPIO_Pin = BACKLIGHT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_Init(BACKLIGHT_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = RELAY_GPIO_PIN;
    GPIO_Init(RELAY_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_DATA_GPIO_PIN;
    GPIO_Init(LCD_DATA_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_WR_GPIO_PIN;
    GPIO_Init(LCD_WR_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_CS_GPIO_PIN;
    GPIO_Init(LCD_CS_GPIO_PORT, &GPIO_InitStructure);

    // Turn off all
    GPIO_ResetBits(BACKLIGHT_GPIO_PORT, BACKLIGHT_GPIO_PIN);
    GPIO_ResetBits(RELAY_GPIO_PORT, RELAY_GPIO_PIN);

    GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_GPIO_PIN);
    GPIO_SetBits(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN);
    GPIO_SetBits(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN);

    // Inputs
    RCC_AHBPeriphClockCmd(BTN_DOWN_GPIO_CLK | BTN_SET_GPIO_CLK | BTN_UP_GPIO_CLK, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = BTN_DOWN_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(BTN_DOWN_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BTN_SET_GPIO_PIN;
    GPIO_Init(BTN_SET_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = BTN_UP_GPIO_PIN;
    GPIO_Init(BTN_UP_GPIO_PORT, &GPIO_InitStructure);
}
