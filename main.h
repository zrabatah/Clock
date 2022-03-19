//main.h
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

#ifndef CLOCK_MAIN_ZRABATAH_H
#define CLOCK_MAIN_ZRABATAH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> //M_PI
#include <gtk/gtk.h>
#include <alsa/asoundlib.h>

#include "clock.h"
#include "constants.h"

#define RATE 44100
#define FREQUENCY 250
#define DURATION 3

#define HORIZONTAL			0
#define VERTICAL			1

#define SIZE_36				36
#define SIZE_48				48

#define START				"Start"
#define RESUME				"Resume"
#define STOP				"Stop"
#define CANCEL				"Cancel"
#define PAUSE				"Pause"
#define RESET				"Reset"

#define DATE				"Date"

#define ABOUT				"About"
#define EXIT				"Exit"

#define PLUS				"+"
#define MINUS				"-"
#define COLON				":"

#define DOUBLE_ZERO			"00"
#define ZERO_HR_MIN_SEC		"00:00:00"

#define DEBUG_CLOCK_ZRAB

enum TAB{
	ANALOG,
	DIGITAL,
	TIMER,
	STOPWATCH
};

static cairo_surface_t* analog_surface = NULL;

GtkWidget* window;

GtkWidget* vbox;

GtkWidget* menu_bar;

//Menus
GtkWidget* file_menu;
GtkWidget* help_menu;

//Menu Items
GtkWidget* file_item;
GtkWidget* help_item;
GtkWidget* exit_item;
GtkWidget* about_item;

//Notebook clock
GtkWidget* notebook_clock;

//Vbox for each tab
GtkWidget* notebook_vbox_analog;
GtkWidget* notebook_vbox_digital;
GtkWidget* notebook_vbox_timer;
GtkWidget* notebook_vbox_stopwatch;

//Labels for notebook tabs
GtkWidget* lblAnalogNotebookClock;
GtkWidget* lblDigitalNotebookClock;
GtkWidget* lblTimerNotebookClock;
GtkWidget* lblStopwatchNotebookClock;

//Analog notebook vbox items
GtkWidget* analog_drawing_area;

//Digital notebook vbox items
GtkWidget* lblDigitalValue;

//Timer notebook vbox items
//Hour, minute, second (combobox)
GtkWidget* hbox_timer;

GtkWidget* vbox_timer_hour;
GtkWidget* vbox_timer_minute;
GtkWidget* vbox_timer_second;

GtkWidget* btnTimerHourIncrease;
GtkWidget* btnTimerHourDecrease;
GtkWidget* lblTimerHour;
GtkWidget* btnTimerMinuteIncrease;
GtkWidget* btnTimerMinuteDecrease;
GtkWidget* lblTimerMinute;
GtkWidget* btnTimerSecondIncrease;
GtkWidget* btnTimerSecondDecrease;
GtkWidget* lblTimerSecond;
GtkWidget* lblTimerValue;
GtkWidget* lblTimerHourMinuteColon;
GtkWidget* lblTimerMinuteSecondColon;

GtkWidget* lblTimerSet;
GtkWidget* lblTimerCountdown;

GtkWidget* btnTimerStart;
GtkWidget* btnTimerCancel;

//Stopwatch notebook vbox items
GtkWidget* btnStopWatchStart;
GtkWidget* btnStopWatchStop;
GtkWidget* btnStopWatchReset;
GtkWidget* lblStopWatchValue;

static void label_attributes_set_init(GtkWidget* label, int font_size);

static void help_message();

static void notebook_tab_changed(GtkNotebook * notebook, GtkWidget *page, guint page_number, gpointer user_data);

static gboolean analog_update();
static gboolean digital_update();
static gboolean timer_update();
static gboolean stopwatch_update();

static gboolean clock_draw(GtkWidget *widget, cairo_t *cr, gpointer data);

//Timer button functions
static void timer_decrement();
static void timer_increase_hour();
static void timer_decrease_hour();
static void timer_increase_minute();
static void timer_decrease_minute();
static void timer_increase_second();
static void timer_decrease_second();

static void timer_start_click();
static void timer_cancel_click();

//Stopwatch button functions
static void stopwatch_start_click();
static void stopwatch_stop_click();
static void stopwatch_reset_click();

#endif
