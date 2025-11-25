/*
 * software_timer.c
 *
 *  Created on: Nov 25, 2025
 *      Author: MinhTri
 */

#include "software_timer.h"
#include <stdint.h>

#define MAX_TIMER 20

static uint32_t timer_counter[MAX_TIMER];
static uint8_t timer_flag[MAX_TIMER];

void setTimer(int index, uint32_t duration) {
	if (index < 0 || index >= MAX_TIMER) return;
	timer_counter[index] = duration;
	timer_flag[index] = 0;
}

int isTimeExpired(int index) {
	if (index < 0 || index >= MAX_TIMER) return 0;
	return timer_flag[index];
}

void timerRun(void) {
	for (int i = 0; i < MAX_TIMER; i++) {
		if (timer_counter[i] > 0) {
			timer_counter[i]--;
			if (timer_counter[i] == 0) timer_flag[i] = 1;
		}
	}
}
