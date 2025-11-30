/*
 * command_parser_fsm.c
 *
 *  Created on: Nov 26, 2025
 *      Author: MinhTri
 */

#include "command_parser_fsm.h"


uint8_t command_data_index = 0;

void command_parser_fsm(void) {
	switch (status) {
	case INIT:
		if (buffer_character == '!') {
			status = READING;
			command_data_index = 0;
		}
		break;
	case READING:
		if (buffer_character != '!' && buffer_character != '#') {
			if (command_data_index < MAX_COMMAND_SIZE - 1) {
				command_data[command_data_index] = buffer_character;
				command_data_index++;
			}
		} else if (buffer_character == '#') {
			status = INIT;
			command_data[command_data_index] = '\0';
			command_data_index = 0;
			command_status = IDLE;
		}
		break;
	default:
		break;
	}
}
