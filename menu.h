#pragma once
#include <string>
#include <vector>
#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>

using namespace std;

class button
{
public:
	button();
	button(string label, int x, int y);
	string get_label();
	int get_x();
	int get_y();
	
private:
	string label;
	int x;
	int y;
};

class mainMenu
{
public:
	mainMenu();
	void draw();
	void key_handling(const bool key[], bool* done);
	string get_play();
	string get_quit();


private:
	button play;
	button quit;
	button options;
	int selected_button;
	
	int color_r;

	ALLEGRO_FONT* font24;
};

class optionsMenu
{
public:
	optionsMenu();
	void draw();
	void key_handling(bool key[]);

private:
	button video;
	button audio;
	button game;
	button back;
	int selected_button;
	
	int color_r;

	ALLEGRO_FONT* font24;
};