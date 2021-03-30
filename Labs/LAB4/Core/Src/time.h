#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_

#include "stm32f1xx_hal.h"
TIM_HandleTypeDef htim4;

int16_t start_time();
int16_t stop_time(int16_t tim);
void averageTimeTester();
int32_t add_32(int32_t x, int32_t y);
int64_t add_64(int64_t x, int64_t y);
int32_t multiply_32(int32_t x, int32_t y);
int64_t multiply_64(int64_t x, int64_t y);
int32_t divide_32(int32_t x, int32_t y);
int64_t divide_64(int64_t x, int64_t y);
void structeight_Copy();
void structonetwentyeight_Copy();
void structkilo_Copy();



struct eightbyte
{
	int64_t x;
};

struct oneTwentyEightByte
{
	int64_t y[16];
};

struct kiloByte
{
	int64_t y[128];
};

#endif /* SRC_TIMER_H_ */
