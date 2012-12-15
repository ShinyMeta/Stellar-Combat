#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>

short m_box(const char* message			= "No Message Given",
			const char* content_title	= "ERROR",
			const char* title			= "Exception");
