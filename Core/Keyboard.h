#pragma once
#include "KeyboardDefines.h"
#define BUTTON_UP 0
#define BUTTON_DOWN 1

static class Keyboard
{
public:
	static void KeyboardDown(unsigned char, int, int);
	static void KeyboardUp(unsigned char, int, int);
	static int KeyPressed(unsigned char);
private:
	static int m_keyState[];
};

