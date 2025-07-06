/*
 * Replacement firmware for XY-CD60L Charge Controller Battery Protection Board
 * Craig Peacock
 * July 2025
 * 
 * Provide debug USART on PD1 @ 115200bps 8N1.
 */
#include "hk32f030m.h"
#include "usart.h"

void USART_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // UART
    // Enable GPIO and UART clock
    RCC_AHBPeriphClockCmd(TXD_GPIO_CLK | RXD_GPIO_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    // AF config
    GPIO_PinAFConfig(TXD_GPIO_PORT, GPIO_PinSource1, GPIO_AF_1);
    GPIO_PinAFConfig(RXD_GPIO_PORT, GPIO_PinSource7, GPIO_AF_1);
    // USART TX
    GPIO_InitStructure.GPIO_Pin = TXD_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(TXD_GPIO_PORT, &GPIO_InitStructure);
    // USART RX
    GPIO_InitStructure.GPIO_Pin = RXD_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_Init(RXD_GPIO_PORT, &GPIO_InitStructure);

    USART_InitTypeDef USART_InitStructure;

    USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}
