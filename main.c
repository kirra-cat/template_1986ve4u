/*
 * main.c
 *
 *  Created on: 16 февр. 2017 г.
 *      Author: kirra
 */

#include <stdbool.h>
#include <stdint.h>

#include "MDR1986BE4.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_port.h"

int main(void)
{
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
	RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
	RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul2);/** 16 * 2 = 32 MHz */
	RST_CLK_CPU_PLLcmd(ENABLE);
	RST_CLK_CPU_PLLuse(ENABLE);

	PORT_InitTypeDef GPIO_InitStructure;

	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTB, ENABLE);
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);

	PORT_DeInit(MDR_PORTB);
	GPIO_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
	GPIO_InitStructure.PORT_OE    = PORT_OE_OUT;
	GPIO_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	GPIO_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	GPIO_InitStructure.PORT_Pin   = PORT_Pin_1 | PORT_Pin_12;
	PORT_Init(MDR_PORTB, &GPIO_InitStructure);

	PORT_StructInit(&GPIO_InitStructure);
	PORT_DeInit(MDR_PORTC);
	GPIO_InitStructure.PORT_FUNC  = PORT_FUNC_PORT;
	GPIO_InitStructure.PORT_OE    = PORT_OE_OUT;
	GPIO_InitStructure.PORT_MODE  = PORT_MODE_DIGITAL;
	GPIO_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
	GPIO_InitStructure.PORT_Pin   = PORT_Pin_1 | PORT_Pin_6 | PORT_Pin_7;
	PORT_Init(MDR_PORTC, &GPIO_InitStructure);

	while (true)
	{
		PORT_SetBits(MDR_PORTB, PORT_Pin_1 | PORT_Pin_12);
		PORT_SetBits(MDR_PORTC, PORT_Pin_1 | PORT_Pin_6 | PORT_Pin_7);
		PORT_ResetBits(MDR_PORTB, PORT_Pin_1 | PORT_Pin_12);
		PORT_ResetBits(MDR_PORTC, PORT_Pin_1 | PORT_Pin_6 | PORT_Pin_7);
	}

	return 0;
}
