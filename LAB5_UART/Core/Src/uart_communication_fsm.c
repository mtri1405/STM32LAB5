/*
 * uart_communication_fsm.c
 *
 *  Created on: Nov 26, 2025
 *      Author: MinhTri
 */
#include "uart_communication_fsm.h"


bool cmdEqualRST(uint8_t str[]) {
	return strcmp((char*) str, "RST") == 0;
}

bool cmdEqualOK(uint8_t str[]) {
	return strcmp((char*) str, "OK") == 0;
}
void uart_communication_fsm(void) {
	static int last_ADC_value = 0;
	static uint8_t active_flag = 0;
	char str[100];
	int tx_len;

	switch (command_status) {
	case IDLE:
		if (cmdEqualRST(command_data)){
			command_status = RST;
		}
		if (cmdEqualOK(command_data)){
			command_status = OK;
		}
	case RST:
		if (active_flag == 0) {
			last_ADC_value = HAL_ADC_GetValue(&hadc1);
			active_flag = 1;
		}
		if (isTimeExpired(1)) {
			tx_len = sprintf(str, "!ADC=%d#\r\n", last_ADC_value);
			if (tx_len > 0) {
				HAL_UART_Transmit(&huart2, (uint8_t*)str, tx_len, UART_TX_TIMEOUT);
			}
			setTimer(1, UART_POLL_INTERVAL);
		}
		break;

	case OK:
		active_flag = 0;
		command_status = INIT;
		break;

	case INIT:
	default:
		if (isTimeExpired(1) && active_flag) {
			tx_len = sprintf(str, "!ADC=%d#\r\n", last_ADC_value);
			if (tx_len > 0) {
				HAL_UART_Transmit(&huart2, (uint8_t*)str, tx_len, UART_TX_TIMEOUT);
			}
			setTimer(1, UART_POLL_INTERVAL);
		}
		break;
	}
}
