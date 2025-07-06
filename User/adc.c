/*
 * Replacement firmware for XY-CD60L Charge Controller Battery Protection Board
 * Craig Peacock
 * July 2025
 * 
 */
#include "hk32f030m.h"
#include "adc.h"

void ADC_Config(void)
{
#if 0
    // Pins are configured analog by default. If the code below
    // is enabled, ADC_Init below will hang. Needs to be investigated.

    GPIO_InitTypeDef GPIO_InitStructure;

    // Analog
    RCC_AHBPeriphClockCmd(VOUT_GPIO_CLK | VIN_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Pin = VOUT_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(VOUT_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = VIN_GPIO_PIN;
    GPIO_Init(VIN_GPIO_PORT, &GPIO_InitStructure);
    printf("ADC GPIO Configured\n\r");
#endif

    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC, ENABLE);

    ADC_DeInit(ADC1);

    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStructure);
    printf("ADC Initalised");

    ADC_GetCalibrationFactor(ADC1);

    ADC_Cmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
}

uint16_t ADC_ConvertByChannel(uint32_t ADC_Channel)
{
    ADC_StopOfConversion(ADC1);
    ADC_ChannelConfig(ADC1, ADC_Channel, ADC_SampleTime_239_5Cycles);
    ADC_StartOfConversion(ADC1);
    // Wait till end-of-conversion is set
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    return ADC_GetConversionValue(ADC1);
}