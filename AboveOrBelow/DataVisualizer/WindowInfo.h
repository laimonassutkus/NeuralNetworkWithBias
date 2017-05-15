#pragma once

struct WindowInfo
{
	unsigned window_width;
	unsigned window_height;
	unsigned padding;

	WindowInfo(unsigned w, unsigned h, unsigned p) : window_width(w), window_height(h), padding(p) { }
};
