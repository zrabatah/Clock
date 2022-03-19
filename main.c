//main.c
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

#include "main.h"

int main(int argc, char** argv)
{
	struct Clock now;
	update_clock_time(&now);
	
	//Init GTK
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL); //Make new window
	g_signal_connect(window, "delete_event", G_CALLBACK(gtk_main_quit), NULL); //Make delete signal

	vbox = gtk_box_new(VERTICAL, 0); /* Make container */
	
	/*Create menu bar and pack it*/
	menu_bar = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX(vbox), menu_bar, 0, 1, 0);

	/*Create menu items */
	file_item = gtk_menu_item_new_with_label("File");
	help_item = gtk_menu_item_new_with_label("Help");

	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), file_item);
	gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), help_item);

	/*Create Menus*/
	file_menu = gtk_menu_new();
	help_menu = gtk_menu_new();

	/*Attach menu items to menu*/
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file_item), file_menu);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(help_item), help_menu);

	/*Add exit to file menu*/
	exit_item = gtk_menu_item_new_with_label(EXIT);
	gtk_menu_shell_append(GTK_MENU_SHELL(file_menu), exit_item);

	/*Add about to help menu*/
	about_item = gtk_menu_item_new_with_label(ABOUT);
	gtk_menu_shell_append(GTK_MENU_SHELL(help_menu), about_item);
	
	/*Create notebook labels*/
	lblAnalogNotebookClock = gtk_label_new("Analog Clock");
	lblDigitalNotebookClock = gtk_label_new("Digital Clock");
	lblTimerNotebookClock = gtk_label_new("Timer");
	lblStopwatchNotebookClock = gtk_label_new("Stopwatch");
	
	/*Add notebook tabs*/
	notebook_clock = gtk_notebook_new();
	gtk_notebook_set_tab_pos(GTK_NOTEBOOK(notebook_clock), GTK_POS_TOP);
	
	/*Create boxes to contain each section of notebooks*/
	notebook_vbox_analog = gtk_box_new(VERTICAL, 0);
	notebook_vbox_digital = gtk_box_new(VERTICAL, 0);
	notebook_vbox_timer = gtk_box_new(VERTICAL, 0);
	notebook_vbox_stopwatch = gtk_box_new(VERTICAL, 0);
	
	/*Add boxes to notebook and make each page*/
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_clock), notebook_vbox_analog, lblAnalogNotebookClock);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_clock), notebook_vbox_digital, lblDigitalNotebookClock);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_clock), notebook_vbox_timer, lblTimerNotebookClock);
	gtk_notebook_append_page(GTK_NOTEBOOK(notebook_clock), notebook_vbox_stopwatch, lblStopwatchNotebookClock);

	/*Analog drawing area*/
	analog_drawing_area = gtk_drawing_area_new();
	gtk_widget_set_size_request (analog_drawing_area, 100, 100);
	
    gtk_box_pack_start(GTK_BOX(notebook_vbox_analog), analog_drawing_area, TRUE, TRUE, 0);                          

	/*Digital Label & Attributes*/	
	lblDigitalValue = gtk_label_new(DATE);
	label_attributes_set_init(lblDigitalValue, SIZE_48);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_digital), lblDigitalValue, TRUE, TRUE, 0);
	
	/*Timer Label & Buttons*/
	hbox_timer = gtk_box_new(HORIZONTAL, 0);
	vbox_timer_hour = gtk_box_new(VERTICAL, 0);
	vbox_timer_minute = gtk_box_new(VERTICAL, 0);
	vbox_timer_second = gtk_box_new(VERTICAL, 0);
	
	lblTimerSet = gtk_label_new("Timer Set");
	lblTimerCountdown = gtk_label_new("Timer");
	
	label_attributes_set_init(lblTimerSet, SIZE_36);
	label_attributes_set_init(lblTimerCountdown, SIZE_36);
	
	//Hour increment/decrement
	btnTimerHourIncrease = gtk_button_new_with_label(PLUS);
	lblTimerHour = gtk_label_new(DOUBLE_ZERO);
	label_attributes_set_init(lblTimerHour, SIZE_48);
	btnTimerHourDecrease = gtk_button_new_with_label(MINUS);
	
	lblTimerHourMinuteColon = gtk_label_new(COLON);
	label_attributes_set_init(lblTimerHourMinuteColon, SIZE_48);
	
	//Minute increment/decrement
	btnTimerMinuteIncrease = gtk_button_new_with_label(PLUS);
	lblTimerMinute = gtk_label_new(DOUBLE_ZERO);
	label_attributes_set_init(lblTimerMinute, SIZE_48);
	btnTimerMinuteDecrease = gtk_button_new_with_label(MINUS);
	
	lblTimerMinuteSecondColon = gtk_label_new(COLON);
	label_attributes_set_init(lblTimerMinuteSecondColon, SIZE_48);
	
	//Second increment/decrement
	btnTimerSecondIncrease = gtk_button_new_with_label(PLUS);
	lblTimerSecond = gtk_label_new(DOUBLE_ZERO);
	label_attributes_set_init(lblTimerSecond, SIZE_48);
	btnTimerSecondDecrease = gtk_button_new_with_label(MINUS);
	
	lblTimerValue = gtk_label_new(ZERO_HR_MIN_SEC);
	label_attributes_set_init(lblTimerValue, SIZE_48);
	
	btnTimerStart = gtk_button_new_with_label(START);
	btnTimerCancel = gtk_button_new_with_label(CANCEL);
	
	gtk_box_pack_start(GTK_BOX(vbox_timer_hour), btnTimerHourIncrease, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox_timer_hour), lblTimerHour, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox_timer_hour), btnTimerHourDecrease, TRUE, TRUE, 5);
	
	gtk_box_pack_start(GTK_BOX(vbox_timer_minute), btnTimerMinuteIncrease, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox_timer_minute), lblTimerMinute, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox_timer_minute), btnTimerMinuteDecrease, TRUE, TRUE, 5);
	
	gtk_box_pack_start(GTK_BOX(vbox_timer_second), btnTimerSecondIncrease, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox_timer_second), lblTimerSecond, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(vbox_timer_second), btnTimerSecondDecrease, TRUE, TRUE, 5);
	
	gtk_box_pack_start(GTK_BOX(hbox_timer), vbox_timer_hour, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(hbox_timer), lblTimerHourMinuteColon, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(hbox_timer), vbox_timer_minute, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(hbox_timer), lblTimerMinuteSecondColon, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(hbox_timer), vbox_timer_second, TRUE, TRUE, 5);
	
	gtk_box_pack_start(GTK_BOX(notebook_vbox_timer), lblTimerSet, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_timer), hbox_timer, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_timer), lblTimerCountdown, FALSE, FALSE, 5);
	
	gtk_box_pack_start(GTK_BOX(notebook_vbox_timer), lblTimerValue, TRUE, TRUE, 5);
	
	gtk_box_pack_start(GTK_BOX(notebook_vbox_timer), btnTimerStart, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_timer), btnTimerCancel, FALSE, FALSE, 5);
	
	/*Stopwatch Label & Buttons*/
	btnStopWatchStart = gtk_button_new_with_label(START);
	btnStopWatchStop = gtk_button_new_with_label(STOP);
	btnStopWatchReset = gtk_button_new_with_label(RESET);
	
	lblStopWatchValue = gtk_label_new(ZERO_HR_MIN_SEC);
	label_attributes_set_init(lblStopWatchValue, SIZE_48);
	
	gtk_box_pack_start(GTK_BOX(notebook_vbox_stopwatch), lblStopWatchValue, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_stopwatch), btnStopWatchStart, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_stopwatch), btnStopWatchStop, FALSE, FALSE, 5);
	gtk_box_pack_start(GTK_BOX(notebook_vbox_stopwatch), btnStopWatchReset, FALSE, FALSE, 5);

	/*Callback functions setpoint*/
	g_signal_connect(G_OBJECT(exit_item), "activate", G_CALLBACK(gtk_main_quit), (gpointer)NULL);
	g_signal_connect(G_OBJECT(about_item), "activate", G_CALLBACK(help_message), (gpointer)NULL);
	
	g_signal_connect(G_OBJECT(notebook_clock), "switch-page", G_CALLBACK(notebook_tab_changed), (gpointer)NULL);
	
	//Timer signals
	g_signal_connect(G_OBJECT(btnTimerHourIncrease), "clicked", G_CALLBACK(timer_increase_hour), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnTimerHourDecrease), "clicked", G_CALLBACK(timer_decrease_hour), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnTimerMinuteIncrease), "clicked", G_CALLBACK(timer_increase_minute), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnTimerMinuteDecrease), "clicked", G_CALLBACK(timer_decrease_minute), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnTimerSecondIncrease), "clicked", G_CALLBACK(timer_increase_second), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnTimerSecondDecrease), "clicked", G_CALLBACK(timer_decrease_second), (gpointer)NULL);
	
	
	g_signal_connect(G_OBJECT(btnTimerStart), "clicked", G_CALLBACK(timer_start_click), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnTimerCancel), "clicked", G_CALLBACK(timer_cancel_click), (gpointer)NULL);
	
	//Stopwatch signals
	g_signal_connect(G_OBJECT(btnStopWatchStart), "clicked", G_CALLBACK(stopwatch_start_click), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnStopWatchStop), "clicked", G_CALLBACK(stopwatch_stop_click), (gpointer)NULL);
	g_signal_connect(G_OBJECT(btnStopWatchReset), "clicked", G_CALLBACK(stopwatch_reset_click), (gpointer)NULL);
	
	g_signal_connect(G_OBJECT(analog_drawing_area), "draw", G_CALLBACK(clock_draw), (gpointer)NULL);
	
	//Pack and finalize GUI
	gtk_box_pack_start(GTK_BOX(vbox), notebook_clock, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	gtk_window_set_title(GTK_WINDOW(window), "Clock"); //Set title of window
	gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
	
	gtk_window_maximize(GTK_WINDOW(window)); //Maximize window
	
	clock_now.analog_id = g_timeout_add_seconds(1, analog_update, NULL);

	//Show window and start main
	gtk_widget_show_all(window);
		
	gtk_main();

	return 0;
}

void label_attributes_set_init(GtkWidget* label, int font_size)
{
	PangoAttrList* lblAttributes = pango_attr_list_new();
	PangoAttribute* lblSize = pango_attr_size_new(font_size * PANGO_SCALE);
	pango_attr_list_insert(lblAttributes, lblSize);
	gtk_label_set_attributes(GTK_LABEL(label), lblAttributes);
	gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
}

void help_message()
{
	const gchar *people[] = {"zrabatah", NULL};
	GtkWidget* dialog;
	GdkPixbuf* image;
	GError* err = NULL;
	GtkDialogFlags flags = GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT;

	image = gdk_pixbuf_new_from_file("Clock_Small.png", &err);

	dialog = gtk_about_dialog_new();

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(window));

	gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "Clock");
	gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "1.00.0");
	gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Copyright © 2022 zrabatah");

	gtk_about_dialog_set_license(GTK_ABOUT_DIALOG(dialog), liscense); //liscense from constants.h
	gtk_about_dialog_set_wrap_license(GTK_ABOUT_DIALOG(dialog), TRUE);

	gtk_about_dialog_add_credit_section(GTK_ABOUT_DIALOG(dialog), "Created By:", people);

	gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), "https://github.com/zrabatah/Clock");

	gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "General clock program");
	gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog),image);

	int result = gtk_dialog_run(GTK_DIALOG(dialog));

	switch(result)
	{
		case GTK_RESPONSE_ACCEPT:

			break;
		default:

			break;
	}

	gtk_widget_destroy(dialog);
}

void notebook_tab_changed(GtkNotebook * notebook, GtkWidget *page, guint page_number, gpointer user_data)
{
	GtkWidget* child = gtk_notebook_get_nth_page(GTK_NOTEBOOK(notebook_clock), page_number);
	int page_selected = gtk_notebook_page_num(GTK_NOTEBOOK(notebook_clock), child);
	
	switch(page_selected)
	{
		case(ANALOG):
			{
				analog_update();
			}
			break;
		
		case(DIGITAL):
			{
				digital_update();
			}
			break;
			
		case(TIMER):
			{
				timer_update();
			}
			break;
			
		case(STOPWATCH):
			{
				stopwatch_update();
			}
			break;
			
		default:
		
			break;
			
	}
}

gboolean analog_update()
{	
	if(!(clock_now.clock_type == ANALOG))
	{
		if(clock_now.clock_type == DIGITAL){
			g_source_remove(clock_now.digital_id);
		}
		else if(clock_now.clock_type == TIMER){
			g_source_remove(clock_now.timer_id);
		}
		else if(clock_now.clock_type == STOPWATCH){
			g_source_remove(clock_now.stopwatch_id);
		}
		
		clock_now.analog_id = g_timeout_add_seconds(1, analog_update, NULL);
	}
	
	clock_now.clock_type = ANALOG;
	update_clock_time(&clock_now);
	
	gtk_widget_queue_draw(analog_drawing_area);
	return TRUE;
}

gboolean digital_update()
{
	if(!(clock_now.clock_type == DIGITAL)){
		if(clock_now.clock_type == ANALOG){
			g_source_remove(clock_now.analog_id);
		}
		else if(clock_now.clock_type == TIMER){
			g_source_remove(clock_now.timer_id);
		}
		else if(clock_now.clock_type == STOPWATCH){
			g_source_remove(clock_now.stopwatch_id);
		}
		
		clock_now.digital_id = g_timeout_add_seconds(1, digital_update, NULL);
	}
	
	clock_now.clock_type = DIGITAL;
	
	update_clock_time(&clock_now);
	
	gtk_label_set_text(GTK_LABEL(lblDigitalValue), asctime(clock_now.local));
	
	return TRUE;
}

gboolean timer_update()
{	
	if(!(clock_now.clock_type == TIMER)){
		if(clock_now.clock_type == ANALOG){
			g_source_remove(clock_now.analog_id);
		}
		else if(clock_now.clock_type == DIGITAL){
			g_source_remove(clock_now.digital_id);
		}
		else if(clock_now.clock_type == STOPWATCH){
			g_source_remove(clock_now.stopwatch_id);
		}
		
		clock_now.timer_id = g_timeout_add_seconds(1, timer_update, NULL);
	}
	
	clock_now.clock_type = TIMER;
	
	if(clock_now.timer_state == TIMER_START){
		timer_decrement();
	}
	else if(clock_now.timer_state == TIMER_RESUME){
		timer_decrement();
	}
	
	
	return TRUE;
}

gboolean stopwatch_update()
{	
	if(!(clock_now.clock_type == STOPWATCH)){
		if(clock_now.clock_type == ANALOG){
			g_source_remove(clock_now.analog_id);
		}
		else if(clock_now.clock_type == DIGITAL){
			g_source_remove(clock_now.digital_id);
		}
		else if(clock_now.clock_type == TIMER){
			g_source_remove(clock_now.timer_id);
		}
		
		clock_now.stopwatch_id = g_timeout_add_seconds(1, stopwatch_update, NULL);
	}
	
	clock_now.clock_type = STOPWATCH;
	
	if(clock_now.stopwatch_type == STOPWATCH_START){
		clock_now.stopwatch_delta++;
	}
	else if(clock_now.stopwatch_type == STOPWATCH_RESET_START){
		clock_now.stopwatch_delta = 0;
		update_stopwatch_start(&clock_now);
	}
	else if(clock_now.stopwatch_type == STOPWATCH_RESET_STOP){
		clock_now.stopwatch_delta = 0;
		update_stopwatch_stop(&clock_now);
	}
	
	char* input;
	
	get_formatted_time(&clock_now, &input, &clock_now.stopwatch_delta);
	gtk_label_set_text(GTK_LABEL(lblStopWatchValue), input);
	
	free(input);
	
	return TRUE;
}

//Draws the analog clock
gboolean clock_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{	guint width, height;
	
	GtkStyleContext *context;

	context = gtk_widget_get_style_context (analog_drawing_area);
	width = gtk_widget_get_allocated_width(analog_drawing_area);
	height = gtk_widget_get_allocated_height(analog_drawing_area);
	
	if(width > 100 && height > 100){		
		GdkWindow* window_gdk = gtk_widget_get_window(analog_drawing_area);
		cairo_region_t * cairoRegion = cairo_region_create();
		
		GdkDrawingContext * drawingContext;
        drawingContext = gdk_window_begin_draw_frame (window_gdk,cairoRegion);
		
		cairo_t* cr = gdk_drawing_context_get_cairo_context(drawingContext);		
		
		{
			int i = 0;
			int offset = 10;
			int radius = 0;
	
			//Ensure clock stays on screen with maximum size
			if(height > width){
				radius = width / 2 - offset;
			}else{
				radius = height / 2 - offset;
			}
			
			//Background color
			cairo_set_source_rgb(cr, 0.66, 0.56, 0.56);
			cairo_arc(cr, width / 2, height / 2, radius / 1.1, 0.0, 2 * M_PI);
			cairo_fill(cr);
			
			//Clock center
			cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);			
			cairo_arc(cr, width / 2, height / 2, radius / 25, 0.0, 2 * M_PI);
			cairo_fill(cr);
			
			//Clock hour marks
			for (i = 0; i < ANALOG_HOUR_COUNT; i++){
				cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
				cairo_arc(cr, width / 2 + (radius / 1.1) * cos(2 * M_PI * i / 12 - M_PI / 2),
					height / 2 + (radius / 1.1) * sin(2 * M_PI * i / 12 - M_PI / 2),
					radius / 25, 0 + 2 * M_PI * i / ANALOG_HOUR_COUNT, M_PI + 2 * M_PI * i / ANALOG_HOUR_COUNT);
				cairo_fill(cr);
			}
			
			//Clock hands
			
			cairo_set_line_width(cr, radius / 16);
			//move hour hand
			cairo_move_to(cr, width / 2, height / 2); //move to center
			cairo_line_to(cr, 
				width / 2 + cos((2 * M_PI * clock_now.clock_hour / ANALOG_HOUR_COUNT) - (M_PI / 2) + 
					((M_PI / 6) * clock_now.clock_min / MINUTE_COUNT)) * (radius / 1.8), 
				height / 2 + sin((2 * M_PI * clock_now.clock_hour / ANALOG_HOUR_COUNT) - 
					(M_PI / 2) + ((M_PI / 6) * clock_now.clock_min / MINUTE_COUNT)) * (radius / 1.8));
			cairo_stroke(cr);
			
			//move minute hand
			cairo_set_line_width(cr, radius / 20);
			cairo_set_source_rgb(cr, 0.20, 0.20, 0.20);
			cairo_move_to(cr, width / 2, height / 2); //move to center
			cairo_line_to(cr, width / 2 + cos(2 * M_PI * clock_now.clock_min / MINUTE_COUNT - M_PI / 2)* (radius / 1.4), 
				height / 2 + sin(2 * M_PI * clock_now.clock_min / MINUTE_COUNT - M_PI / 2)* (radius / 1.4)); 
			cairo_stroke(cr);
			
			cairo_set_line_width(cr, radius / 30);
			cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
			cairo_move_to(cr, width / 2, height / 2); //move to center
			//move second hand
			cairo_line_to(cr, width / 2 + cos(2 * M_PI * clock_now.clock_sec / SECOND_COUNT - M_PI / 2)* (radius / 1.3), 
				height / 2 + sin(2 * M_PI * clock_now.clock_sec / SECOND_COUNT - M_PI / 2)* (radius / 1.3)); 
			cairo_stroke(cr);
			
			//Clock border
			cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
			cairo_set_line_width(cr, 1.0);	
			cairo_arc(cr, width / 2, height / 2, radius, 0.0, 2 * M_PI);
			cairo_stroke(cr);
			
			//Clock inner border
			cairo_arc(cr, width / 2, height / 2, radius / 1.1, 0.0, 2 * M_PI);
			cairo_stroke(cr);
			
			//Clock green border
			cairo_set_source_rgb(cr, 0.02, 0.87, 0.51);
			cairo_set_line_width(cr, radius / 10.5);
			cairo_arc(cr, width / 2, height / 2, radius / 1.05, 0.0, 2 * M_PI);
			cairo_stroke(cr);
			
			cairo_set_source_rgb(cr, 1.0, 0.84, 0.0); //gold
			cairo_arc(cr, width / 2, height / 2, radius / 50, 0.0, 2 * M_PI);
			cairo_fill(cr);
		}       
        gdk_window_end_draw_frame(window_gdk,drawingContext);
				
		// cleanup
        cairo_region_destroy(cairoRegion);
	}
	
	return FALSE;
}

void timer_decrement()
{
	char* time_update;
	
	if(clock_now.timer_delta < 0)
	{
		clock_now.timer_delta = 0;
		clock_now.timer_state = TIMER_STOP;
		
		snd_pcm_t *handle;
		unsigned char buffer[RATE * DURATION];

		for (int i = 0; i < sizeof(buffer); i++)
		{
			buffer[i] = 0xFF * sin(2 * M_PI * FREQUENCY * i / RATE);
		}

		snd_pcm_open(&handle, "default", SND_PCM_STREAM_PLAYBACK, 0);

		snd_pcm_set_params(handle, SND_PCM_FORMAT_U8, SND_PCM_ACCESS_RW_INTERLEAVED, 1, RATE, 1, 10000);

		snd_pcm_writei(handle, buffer, sizeof(buffer));

		snd_pcm_close(handle);
		
		gtk_button_set_label(GTK_BUTTON(btnTimerStart), START);
	}
	
	get_formatted_time(&clock_now, &time_update, &clock_now.timer_delta);
	
	gtk_label_set_text(GTK_LABEL(lblTimerValue), time_update);
	
	free(time_update);
	
	clock_now.timer_delta--;
}

//Timer button functions
void timer_start_click()
{
	if(clock_now.timer_state == TIMER_STOP){
		set_delta_time(&clock_now, clock_now.timer_hour, clock_now.timer_minute, clock_now.timer_second, &clock_now.timer_delta);
		clock_now.timer_state = TIMER_START;
		gtk_button_set_label(GTK_BUTTON(btnTimerStart), PAUSE);
	}
	else if(clock_now.timer_state == TIMER_START){
		clock_now.timer_state = TIMER_PAUSE;
		gtk_button_set_label(GTK_BUTTON(btnTimerStart), RESUME);
	}
	else if(clock_now.timer_state == TIMER_PAUSE){
		clock_now.timer_state = TIMER_RESUME;
		gtk_button_set_label(GTK_BUTTON(btnTimerStart), PAUSE);
	}
	else if(clock_now.timer_state == TIMER_RESUME){
		clock_now.timer_state = TIMER_PAUSE;
		gtk_button_set_label(GTK_BUTTON(btnTimerStart), RESUME);
	}
	else if(clock_now.timer_state == TIMER_CANCEL){
		set_delta_time(&clock_now, clock_now.timer_hour, clock_now.timer_minute, clock_now.timer_second, &clock_now.timer_delta);
		clock_now.timer_state = TIMER_START;
		gtk_button_set_label(GTK_BUTTON(btnTimerStart), PAUSE);
	}
}

void timer_cancel_click()
{
	clock_now.timer_state = TIMER_CANCEL;
	gtk_button_set_label(GTK_BUTTON(btnTimerStart), START);
	gtk_label_set_text(GTK_LABEL(lblTimerValue), ZERO_HR_MIN_SEC);
}

void timer_increase_hour()
{
	clock_now.timer_hour++;
	if(clock_now.timer_hour > 99){
		clock_now.timer_hour = 0;
	}
	gtk_label_set_text(GTK_LABEL(lblTimerHour), g_strdup_printf("%02d", clock_now.timer_hour));
}
void timer_decrease_hour()
{
	clock_now.timer_hour--;
	if(clock_now.timer_hour < 0){
		clock_now.timer_hour = 99;
	}
	gtk_label_set_text(GTK_LABEL(lblTimerHour), g_strdup_printf("%02d", clock_now.timer_hour));
}

void timer_increase_minute()
{
	clock_now.timer_minute++;
	if(clock_now.timer_minute > 59){
		clock_now.timer_minute = 0;
	}
	gtk_label_set_text(GTK_LABEL(lblTimerMinute), g_strdup_printf("%02d", clock_now.timer_minute));
}
void timer_decrease_minute()
{
	clock_now.timer_minute--;
	if(clock_now.timer_minute < 0){
		clock_now.timer_minute = 59;
	}
	gtk_label_set_text(GTK_LABEL(lblTimerMinute), g_strdup_printf("%02d", clock_now.timer_minute));
}

void timer_increase_second()
{
	clock_now.timer_second++;
	if(clock_now.timer_second > 59){
		clock_now.timer_second = 0;
	}
	gtk_label_set_text(GTK_LABEL(lblTimerSecond), g_strdup_printf("%02d", clock_now.timer_second));
}
void timer_decrease_second()
{
	clock_now.timer_second--;
	if(clock_now.timer_second < 0){
		clock_now.timer_second = 59;
	}
	gtk_label_set_text(GTK_LABEL(lblTimerSecond), g_strdup_printf("%02d", clock_now.timer_second));
}

//Stopwatch button functions
void stopwatch_start_click()
{
	update_stopwatch_start(&clock_now);
}

void stopwatch_stop_click()
{
	update_stopwatch_stop(&clock_now);
}

void stopwatch_reset_click()
{
	update_stopwatch_reset(&clock_now);
}
