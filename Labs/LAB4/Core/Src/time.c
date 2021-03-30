#include "time.h"
#include "main.h"

int16_t start_time()
{
	int16_t timecount = 0;

	timecount =  __HAL_TIM_GET_COUNTER(&htim4);

	return timecount;
}

int16_t stop_time(int16_t tim)
{
	int16_t timecount = 0;

	timecount =  __HAL_TIM_GET_COUNTER(&htim4);

	if(tim <= timecount)
	{
		return (tim + (0xffff - timecount));
	}
	else
	{
		return (tim - timecount);
	}
}


int32_t add_32(int32_t x, int32_t y)
{
	return x + y;
}

int64_t add_64(int64_t x, int64_t y)
{
	return x + y;
}

int32_t multiply_32(int32_t x, int32_t y)
{
	return x * y;
}

int64_t multiply_64(int64_t x, int64_t y)
{
	return x * y;
}

int32_t divide_32(int32_t x, int32_t y)
{
	if(y == 0)
		return -1;

	return x / y;
}

int64_t divide_64(int64_t x, int64_t y)
{
	if(y == 0)
		return -1;

	return x / y;
}

void structeight_Copy()
{
	struct eightbyte x , y;
	x = y;
}

void structonetwentyeight_Copy()
{
	struct oneTwentyEightByte x , y;
	x = y;
}

void structkilo_Copy()
{
	struct kiloByte x , y;
	x = y;
}
