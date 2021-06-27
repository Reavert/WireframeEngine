#include "Keyboard.h"

int Keyboard::m_keyState[256] = { BUTTON_UP };

void Keyboard::KeyboardDown(unsigned char key, int x, int y)
{
	if (key >= 0 && key < 256)
		Keyboard::m_keyState[key] = BUTTON_DOWN;
}

void Keyboard::KeyboardUp(unsigned char key, int x, int y)
{
	if (key >= 0 && key < 256)
		Keyboard::m_keyState[key] = BUTTON_UP;
}

int Keyboard::KeyPressed(unsigned char key)
{
	if (key >= 0 && key < 256)
		return Keyboard::m_keyState[key];
}