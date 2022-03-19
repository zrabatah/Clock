//clock.h
//ZKR
//Clock

/*
MIT License

Copyright (c) 2022 zrabatah

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CLOCK_ZRABATAH_H
#define CLOCK_ZRABATAH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

enum TIMER_STATE{
	TIMER_STOP,
	TIMER_START,
	TIMER_PAUSE,
	TIMER_RESUME,
	TIMER_CANCEL
};

enum STOPWATCH_STATE{
	STOPWATCH_STOP,
	STOPWATCH_START,
	STOPWATCH_RESET_START,
	STOPWATCH_RESET_STOP
};

struct Clock{
	int clock_type;
	
	int analog_id;
	int digital_id;
	int timer_id;
	int stopwatch_id;
	
	//Time Info
	int clock_sec;
	int clock_min;
	int clock_hour;
	int clock_day;
	int clock_month;
	int clock_year;
	int clock_weekday;
	int clock_yearday;
	int clock_isdst;
	
	struct tm* local;
	
	int timer_state;
	long timer_delta;
	
	int timer_hour;
	int timer_minute;
	int timer_second;
	
	int stopwatch_type;
	long stopwatch_delta;
};

struct Clock clock_now;

void update_clock_time(struct Clock *clk);

void update_clock_type(struct Clock *clk, int type);

void update_stopwatch_start(struct Clock *clk);
void update_stopwatch_stop(struct Clock *clk);
void update_stopwatch_reset(struct Clock *clk);

void set_delta_time(struct Clock *clk, int hours, int minutes, int seconds, long* deltaReturn);

void get_formatted_time(struct Clock *clk, char** input, long* inputDelta);

#endif

