#include <iostream>
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include "menu.h"

using namespace std;

/* CONSTANTS */
const float FPS = 60;
const int SCREEN_W = 799;
const int SCREEN_H = 599;
const int BOUNCER_SIZE = 32;

enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, ENTER
};

int main(int argc, char *argv[])
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *bouncer = NULL;
	float bouncer_x = SCREEN_W / 2.0 - BOUNCER_SIZE / 2.0;
	float bouncer_y = SCREEN_H / 2.0 - BOUNCER_SIZE / 2.0;
	bool key[5] = { false, false, false, false, false };
	bool redraw = true;
	bool done = false;

	/*--- Allegro initializtion ---*/
	if (!al_init())
	{
		al_show_native_message_box(NULL, "Error", "Error:",
        "failed to initialize allegro!", NULL, NULL);
		return -1;
	}
	/*--- Keyboard initializtion ---*/
	if(!al_install_keyboard())
	{
		al_show_native_message_box(NULL, "Error", "Error:",
        "failed to initialize keyboard!", NULL, NULL);
		return -1;
	}
	
	/*--- Timer initializtion ---*/
	timer = al_create_timer(1.0/FPS);
	if(!timer)	
	{
		al_show_native_message_box(NULL, "Error", "Error:",
        "failed to initialize timer!", NULL, NULL);
		return -1;
	}

	/*--- Display initializtion ---*/
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display)
	{
		al_show_native_message_box(NULL, "Error", "Error:",
        "failed to initialize display!", NULL, NULL);
		al_destroy_timer(timer);
		return -1;
	}

	/*--- Bouncer initializtion ---*/
	bouncer = al_create_bitmap(BOUNCER_SIZE, BOUNCER_SIZE);
	if(!bouncer)
	{al_show_native_message_box(NULL, "Error", "Error:",
        "failed to initialize Bouncer Bitmap!", NULL, NULL);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	/*--- Font initializtion ---*/
	al_init_font_addon();
	al_init_ttf_addon();


	al_set_target_bitmap(bouncer);
	al_clear_to_color(al_map_rgb(255,0,255));
	al_set_target_bitmap(al_get_backbuffer(display));

	event_queue = al_create_event_queue();
	if(!event_queue)
	{
		cout << "Failed to create event_queue!" << endl;
		al_destroy_bitmap(bouncer);
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_clear_to_color(al_map_rgb(0,0,0));
	al_flip_display();
	al_start_timer(timer);

	mainMenu main_menu;

	while(!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if(ev.type == ALLEGRO_EVENT_TIMER)
		{
			
			//else if (inGame)
			//{
			//	if(key[KEY_UP] && (bouncer_y >= 4.0))								// / \ 
			//		bouncer_y -= 4.0;												//  |
			//																	
			//	if(key[KEY_DOWN] && (bouncer_y <= SCREEN_H - BOUNCER_SIZE - 4.0))	//  |
			//		bouncer_y += 4.0;												// \ /
			//																	
			//	if(key[KEY_LEFT] && (bouncer_x >= 4.0))								
			//		bouncer_x -= 4.0;												// <---
			//																	
			//	if (key[KEY_RIGHT] && (bouncer_x <= SCREEN_W - BOUNCER_SIZE - 4.0))	// ---> 
			//		bouncer_x += 4.0;												

			//	redraw = true;
			//}
			redraw = true;
		}

		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			done = true;

		/*=======================================
				Check for Keyboard Input
		========================================= */
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode) 
			{
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = true;
					break;
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = true;
					break;
				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = true;
					break;
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = true;
					break;
				case ALLEGRO_KEY_ENTER:
					key[ENTER] = true;
					break;
			}
			main_menu.key_handling(key, &done);
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			switch (ev.keyboard.keycode)
			{
				case ALLEGRO_KEY_UP:
					key[KEY_UP] = false;
					break;
				case ALLEGRO_KEY_DOWN:
					key[KEY_DOWN] = false;
					break;
				case ALLEGRO_KEY_LEFT:
					key[KEY_LEFT] = false;
					break;
				case ALLEGRO_KEY_RIGHT:
					key[KEY_RIGHT] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					done = true;
					break;
			}
		}



		/*===============================
					Redraw
		================================*/
		if(redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;

			al_clear_to_color(al_map_rgb(0,0,0));
			main_menu.draw();
			al_flip_display();
		}
	}


	al_destroy_bitmap(bouncer);
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);
	return 0;
}