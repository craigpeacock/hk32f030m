
#include "hk32f030m.h"

void LCD_Config(void);
void LCD_ClearScreen(void);
void LCD_Send(uint16_t raw, uint8_t bits);
void LCD_Send_Command(uint16_t cmd);
void LCD_Send_Data(uint8_t addr, uint8_t data);
void LCD_DisplayValue(uint8_t line, uint16_t value, uint8_t decimal);

#define GN1621_CMD_SYS_DISABLE          0b000000000     // Turn off both system oscillator and LCD bias generator
#define GN1621_CMD_SYS_EN               0b000000010     // Turn on system oscillator
#define GN1621_CMD_LCD_OFF              0b000000100     // Turn off LCD Display
#define GN1621_CMD_LCD_ON               0b000000110     // Turn on LCD Dislay
#define GN1621_CMD_BIAS_4COM            0b001010000     // 1/2 Bias, 4 Common Ports

#define GN1621_OP_READ                  0b110
#define GN1621_OP_WRITE                 0b101
#define GN1621_OP_READ_MODIFY_WRITE     0b101
#define GN1621_OP_COMMAND               0b100

union LCD_Data {
    struct {
    uint16_t data: 4;
    uint16_t address: 6;
    uint16_t op: 3;
    } fields __packed;
    uint16_t raw;
};

union LCD_Command {
    struct {
        uint16_t cmd: 9;
        uint16_t op: 3;
    } fields __packed;
    uint16_t raw;
};

#define DIGIT_1     0b10100000
#define DIGIT_2     0b11001011
#define DIGIT_3     0b11101001
#define DIGIT_4     0b11100100
#define DIGIT_5     0b01101101
#define DIGIT_6     0b01101111
#define DIGIT_7     0b10101000
#define DIGIT_8     0b11101111
#define DIGIT_9     0b11101100
#define DIGIT_0     0b10101111

#define LCD_LINE_1  0x01
#define LCD_LINE_2  0x02