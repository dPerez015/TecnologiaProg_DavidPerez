#pragma once
#include "Renderer.h"

namespace GUI {
	template<FontID fontID>
	static void DrawTextBlended(std::string &msg, SDL_Rect &rect) {
		R.Push(TTF_RenderText_Blended(R.getFont<fontID>(), msg.c_str(), R.theColors[Colors::BLACK]), rect);
	}
	template<FontID fontID>
	static void DrawTextSolid(std::string &msg, SDL_Rect &rect) {
		R.Push(TTF_RenderText_Solid(R.getFont<fontID>(), msg.c_str(),R.theColors[Colors::BLACK] ), rect);
	}

};