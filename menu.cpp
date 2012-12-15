#include "menu.h"
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

#define MAIN_MENU_TOP 2
#define OPTIONS_MENU_TOP 3
#define MENU_BOTTOM 0

#define VIDEO_BUTTON 3
#define AUDIO_BUTTON 2
#define GAME_BUTTON 1
#define BACK_BUTTON 0

using namespace std;

const int SCREEN_W = 799;
const int SCREEN_H = 599;
enum MYKEYS {
	KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, ENTER
};

enum mainMenuButtons {
	QUIT, OPTIONS, PLAY
};

mainMenu::mainMenu()
{
	play = button("Play", SCREEN_W/2, 300);
	options = button("Options", SCREEN_W/2, 375);
	quit = button("Quit", SCREEN_W/2, 450);
	font24 = al_load_font("korataki.ttf",24,0);

	// Selects Default Button
	selected_button = PLAY;

	color_r = 0;
}
void mainMenu::draw()
{
	if (selected_button == PLAY)
	{
		al_draw_text(font24, al_map_rgb(color_r,255,255), play.get_x(), play.get_y(), ALLEGRO_ALIGN_CENTRE, "Play");
		/*if (color_r > 0)
			color_r -= 1;
		else if (color_r < 255)
			color_r += 1;*/
	}
	else
		al_draw_text(font24, al_map_rgb(255,255,255), play.get_x(), play.get_y(), ALLEGRO_ALIGN_CENTRE, "Play");


	if (selected_button == OPTIONS)
	{
		al_draw_text(font24, al_map_rgb(color_r,255,255), options.get_x(), options.get_y(), ALLEGRO_ALIGN_CENTRE, "Options");
	}
	else
		al_draw_text(font24, al_map_rgb(255,255,255), options.get_x(), options.get_y(), ALLEGRO_ALIGN_CENTRE, "Options");

	if (selected_button == QUIT)
	{
		al_draw_text(font24, al_map_rgb(color_r,255,255), quit.get_x(), quit.get_y(), ALLEGRO_ALIGN_CENTRE, "Quit");
	}
	else
		al_draw_text(font24, al_map_rgb(255,255,255), quit.get_x(), quit.get_y(), ALLEGRO_ALIGN_CENTRE, "Quit");

}
void mainMenu::key_handling(const bool key[], bool* done)
{
	// if defined allegro event key pressed move.  Otherwise don't do anything.  Don't poll per frame like this

	if (key[KEY_UP])						// If up is pressed
	{
		if (selected_button == MENU_TOP)	// if button is at the top of the menu
			selected_button = MENU_BOTTOM;		// Loop through to bottom of menu
		else								
			selected_button++;					// Move up a button
	}

	if (key[KEY_DOWN])						// If Down is pressed
	{											
		if (selected_button == MENU_BOTTOM)		// If selection is at bottom of menu
			selected_button = MAIN_MENU_TOP;	// Loop through to top of menu
		else									// Otherwise, if player presses down, and there's a button below
			selected_button--;					// Move down a button
	}


	if (key[ENTER])
	{
		switch (selected_button)
		{
			case PLAY:
				// junk
				break;
			
			case OPTIONS:
				//junk
				break;

			case QUIT:
				*done = true;
				break;
		}
	}
}

optionsMenu::optionsMenu()
{
	video = button("Video", SCREEN_W/2, 200);
	audio = button("Audio", SCREEN_W/2, 300);
	game = button("Game", SCREEN_W/2, 400);
	back = button("BACK", SCREEN_W/2, 500);

	font24 = al_load_font("korataki.ttf",24,0);
	selected_button = VIDEO_BUTTON;

	color_r = 0;
}

button::button(string label, int x, int y)
{
	this->label = label;
	this->x = x;
	this->y = y;
}
button::button()
{
	label = "";
	x = 0;
	y = 0;
}
int button::get_x()
{
	return x;
}
int button::get_y()
{
	return y;
}
string button::get_label()
{
	return label;
}