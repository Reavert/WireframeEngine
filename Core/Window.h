#pragma once
#include <string>
#include "glew.h"
#include "freeglut.h"
#include "Keyboard.h"

#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600
#define DEFAULT_TITLE "Application" 

class Window
{
public:
	Window();
	~Window();

	void Create(int argc, char* argv[]);

	void SetTitle(std::string title);
	std::string GetTitle();

	void SetSize(uint32_t width, uint32_t height);
	uint32_t GetWidth();
	uint32_t GetHeight();

	void (*OnInitialize)();
	void (*OnUpdate)();
	void (*OnRelease)();
	void StartLoop();

private:
	std::string m_title;
	int m_handle;

	uint32_t m_width;
	uint32_t m_height;


	static void ResizeFunction(int width, int height, void* data);
	static void RenderFunction(void* data);
	static void IdleFunction(void* data);
};
