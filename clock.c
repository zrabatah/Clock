//clock.c
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

#include "clock.h"

void update_clock_time(struct Clock *clk)
{
	time_t t = time(NULL);

	if(t == -1){
		return;
	}
	
	clk->local = localtime(&t);
	
	clk->clock_sec = clk->local->tm_sec;
	clk->clock_min = clk->local->tm_min;
	clk->clock_hour = clk->local->tm_hour;
	clk->clock_day = clk->local->tm_mday;
	clk->clock_month = clk->local->tm_mon;
	clk->clock_year = clk->local->tm_year;
	clk->clock_weekday = clk->local->tm_wday;
	clk->clock_yearday = clk->local->tm_yday;
	clk->clock_isdst = clk->local->tm_isdst;
}

void update_clock_type(struct Clock *clk, int type)
{
	clk->clock_type = type;
}

void update_stopwatch_start(struct Clock *clk)
{
	clk->stopwatch_type = STOPWATCH_START;
}

void update_stopwatch_stop(struct Clock *clk)
{
	clk->stopwatch_type = STOPWATCH_STOP;
}

void update_stopwatch_reset(struct Clock *clk)
{
	if(clk->stopwatch_type == STOPWATCH_START){
		clk->stopwatch_type = STOPWATCH_RESET_START;
	}
	else if(clk->stopwatch_type == STOPWATCH_STOP){
		clk->stopwatch_type = STOPWATCH_RESET_STOP;
	}
}

void set_delta_time(struct Clock *clk, int hours, int minutes, int seconds, long* deltaReturn)
{
	long total = 0;
	
	total = (long)hours * 3600 + (long)minutes * 60 + (long)seconds;
	
	*deltaReturn = total;
}

void get_formatted_time(struct Clock *clk, char** input, long* inputDelta)
{
	int char_count_print_char = 8;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	
	char seconds_minutes_char[8];
	
	long delta = *inputDelta;
	
	
	if(delta / 3600 > 0){
		hours = delta / 3600;
		delta = delta - 3600 * hours;
	}
	if(delta / 60 > 0){
		minutes = delta / 60;
		delta = delta - 60 * minutes;
	}
	seconds = delta;
	
	delta = hours;
	
	while((delta) >= 100){
		char_count_print_char++;
		delta = delta / 10;
	}
	
	*input = malloc(char_count_print_char + 8);
	memset(*input, '0', char_count_print_char + 8);
	
	snprintf(*input, sizeof(*input), "%0*d", char_count_print_char - 6, hours);
	
	snprintf(seconds_minutes_char, sizeof(seconds_minutes_char), ":%02d:%02d", minutes, seconds);	
	
	strncat(*input, seconds_minutes_char, sizeof(*input) + 1);
}
