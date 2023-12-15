/*
Title		:Xay dung game X-O su dung C++ va SDL
Author		:nhom 26 - Tran Ba Thanh, Nguyen Duy Nhat Quang, Pham Huu Quang Khai
Date created:15-12-2023
Last edited	: 15-12-2023

This code was writen with the help of OpenAI-ChatGPT and some handsome Indian guys
*/

#include <iostream>
#include <SDL.h>

using namespace std;

int main(int argc, char* argv[])
{
	// test SDL working or not
	//cout << "Hello world!" << endl;
	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello world", "Successfull", NULL);

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to Initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// Create a window
	// https://wiki.libsdl.org/SDL2/SDL_WINDOWPOS_CENTERED
	// with w = 800p, h = 600p
	// the SDL wiki doesnt have definition for SDL_WINDOWPOS_CENTERED so ...
	SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe / X-O ghêm hay vcl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
	if (!window)
	{
		SDL_Log("Unable to Initialize SDL: %s", SDL_GetError());
		return 1;
	}

	// Create a renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Unable to create renderer: %s", SDL_GetError());
		return 1;
	}

	// Game loop and other logic

	//Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}