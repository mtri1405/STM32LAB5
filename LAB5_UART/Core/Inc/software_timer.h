/*
 * software_timer.h
 *
 *  Created on: Nov 25, 2025
 *      Author: MinhTri
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include <stdint.h>

void setTimer(int index, uint32_t duration);
int isTimeExpired(int index);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
