/*
 * Replacement firmware for XY-CD60L Charge Controller Battery Protection Board
 * Craig Peacock
 * July 2025
 * 
 * Routines for GN1621 / HK1621 / HT1621 LCD Controller
 */
#include "hk32f030m.h"
#include "gpio.h"
#include "lcd.h"

void LCD_Config(void)
{
    GPIO_SetBits(BACKLIGHT_GPIO_PORT, BACKLIGHT_GPIO_PIN);

    LCD_Send_Command(GN1621_CMD_SYS_EN);
    LCD_Send_Command(GN1621_CMD_BIAS_4COM);
    LCD_ClearScreen();
    LCD_Send_Command(GN1621_CMD_LCD_ON);
}

void LCD_ClearScreen(void)
{
    for (int addr = 0; addr < 18; addr++) {
        LCD_Send_Data(addr, 0x0);
    }
}

void LCD_Send(uint16_t raw, uint8_t bits)
{
    //printf("Sending Command 0x%04X (%d bits)\r\n", raw, bits);

    uint16_t mask = 1 << (bits - 1);

    // Set CS Low
    GPIO_ResetBits(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN);

    for (int i = 0; i < bits; i++) {

        if (raw & mask) {
            GPIO_SetBits(LCD_DATA_GPIO_PORT, LCD_DATA_GPIO_PIN);
        } else {
            GPIO_ResetBits(LCD_DATA_GPIO_PORT, LCD_DATA_GPIO_PIN);
        }
        raw <<= 1;

        GPIO_ResetBits(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN);
        //SysTick_DelayMs(1);
        GPIO_SetBits(LCD_WR_GPIO_PORT, LCD_WR_GPIO_PIN);    // Data clocked in on rising edge
        //SysTick_DelayMs(1);
    }
    // Finished, set CS High
    GPIO_SetBits(LCD_CS_GPIO_PORT, LCD_CS_GPIO_PIN);
}

void LCD_Send_Command(uint16_t cmd)
{
    union LCD_Command frame;

    frame.fields.op = GN1621_OP_COMMAND;
    frame.fields.cmd = cmd;

    LCD_Send(frame.raw, 12);
}

void LCD_Send_Data(uint8_t addr, uint8_t data)
{
    union LCD_Data frame;

    frame.fields.op = GN1621_OP_WRITE;
    frame.fields.address = addr;
    frame.fields.data = data;

    LCD_Send(frame.raw, 13);
}

/*
 * 7 Segment Routines
 *
 */

uint8_t DIGIT[] = { DIGIT_0, DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4, DIGIT_5, DIGIT_6, DIGIT_7, DIGIT_8,  DIGIT_9 };

void LCD_DisplayValue(uint8_t line, uint16_t value, uint8_t decimal)
{
    uint8_t segment_data;

    for (int digit = 0; digit < 4; digit++) {

        switch (digit) {
            case 0: segment_data = DIGIT[value % 10];
                    if (line == LCD_LINE_1) {
                        LCD_Send_Data(0x06, segment_data & 0x0F);
                        LCD_Send_Data(0x07, (segment_data & 0xF0) >> 4);
                    }
                    if (line == LCD_LINE_2) {
                        LCD_Send_Data(0x0A, segment_data & 0x0F);
                        LCD_Send_Data(0x09, (segment_data & 0xF0) >> 4);
                    }
                    break;

            case 1: segment_data = DIGIT[(value / 10) % 10];
                    if (decimal == 1) segment_data |= 0x10;
                    if (line == LCD_LINE_1) {
                        LCD_Send_Data(0x04, segment_data & 0x0F);
                        LCD_Send_Data(0x05, (segment_data & 0xF0) >> 4);
                    }
                    if (line == LCD_LINE_2) {
                        LCD_Send_Data(0x0C, segment_data & 0x0F);
                        LCD_Send_Data(0x0B, (segment_data & 0xF0) >> 4);
                    }
                    break;

            case 2: segment_data = DIGIT[(value / 100) % 10];
                    if (decimal == 2) segment_data |= 0x10;
                    if (line == LCD_LINE_1) {
                        LCD_Send_Data(0x02, segment_data & 0x0F);
                        LCD_Send_Data(0x03, (segment_data & 0xF0) >> 4);
                    }
                    if (line == LCD_LINE_2) {
                        LCD_Send_Data(0x0E, segment_data & 0x0F);
                        LCD_Send_Data(0x0D, (segment_data & 0xF0) >> 4);
                    }
                    break;

            case 3: segment_data = DIGIT[(value / 1000) % 10]; 
                    if (decimal == 3) segment_data |= 0x10;  
                    if (line == LCD_LINE_1) {                 
                        LCD_Send_Data(0x00, segment_data & 0x0F);
                        LCD_Send_Data(0x01, (segment_data & 0xF0) >> 4);
                    }
                    if (line == LCD_LINE_2) {
                        LCD_Send_Data(0x10, segment_data & 0x0F);
                        LCD_Send_Data(0x0F, (segment_data & 0xF0) >> 4);
                    }
                    break;
        }
    }
}