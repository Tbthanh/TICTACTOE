#pragma once
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include "D:\TAI_LIEU\ET-E9\Program\20231\Ky_thuat_lap_trinh_C_Cpp\TICTACTOE\SDL_learnin\SDL2_gfx-1.0.1\SDL2_gfx-1.0.1\SDL2_gfxPrimitives.h"
#include "D:\TAI_LIEU\ET-E9\Program\20231\Ky_thuat_lap_trinh_C_Cpp\TICTACTOE\SDL_learnin\SDL2_ttf-devel-2.0.14-VC\include\SDL_ttf.h"
#include "GameState.h"

// Function to render the title screen
void renderTitleScreen(SDL_Renderer* renderer)
{
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Render button: for simplicity, our teams use rectangles button
	// https://wiki.libsdl.org/SDL2/SDL_Rect
	// SDL_Rect <> {x, y, w, h};
	SDL_Rect startButton = { 200, 300, 200, 50 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
	SDL_RenderFillRect(renderer, &startButton);

	SDL_Rect helpButton = { 200, 400, 200, 50 };
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color
	SDL_RenderFillRect(renderer, &helpButton);

	SDL_Rect quitButton = { 200, 500, 200, 50 };
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue color
	SDL_RenderFillRect(renderer, &quitButton);

	// Render title text
	TTF_Font* font = TTF_OpenFont("D:/TAI_LIEU/ET-E9/Program/20231/Ky_thuat_lap_trinh_C_Cpp/TICTACTOE/Attempt_3/SDL_TICTACTOE/arial.ttf", 24);  // Replace with your font file
	SDL_Color textColor = { 0, 0, 0, 255 };  // Black text color

	const char* titleText =
		"CO CARO\n"
		"Made by: Nhom 26";

	SDL_Surface* titleTextSurface = TTF_RenderText_Blended_Wrapped(font, titleText, textColor, 400);  // 400 is the wrap length
	SDL_Texture* titleTextTexture = SDL_CreateTextureFromSurface(renderer, titleTextSurface);

	SDL_Rect titleTextRect = { 150, 10, 700, 250 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, titleTextTexture, nullptr, &titleTextRect);


	const char* startButtonText = "Start  ";

	SDL_Surface* startButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, startButtonText, textColor, 10);  // 400 is the wrap length
	SDL_Texture* startButtonTextTexture = SDL_CreateTextureFromSurface(renderer, startButtonTextSurface);

	SDL_Rect startButtonTextRect = { 210, 300, 150, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, startButtonTextTexture, nullptr, &startButtonTextRect);

	const char* helpButtonText = "Help   ";

	SDL_Surface* helpButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, helpButtonText, textColor, 10);
	SDL_Texture* helpButtonTextTexture = SDL_CreateTextureFromSurface(renderer, helpButtonTextSurface);

	SDL_Rect helpButtonTextRect = { 210, 400, 150, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, helpButtonTextTexture, nullptr, &helpButtonTextRect);

	const char* quitButtonText = "Quit   ";

	SDL_Surface* quitButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, quitButtonText, textColor, 10);
	SDL_Texture* quitButtonTextTexture = SDL_CreateTextureFromSurface(renderer, quitButtonTextSurface);

	SDL_Rect quitButtonTextRect = { 210, 500, 150, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, quitButtonTextTexture, nullptr, &quitButtonTextRect);

	// Free resources
	SDL_FreeSurface(titleTextSurface);
	SDL_DestroyTexture(titleTextTexture);
	SDL_FreeSurface(startButtonTextSurface);
	SDL_DestroyTexture(startButtonTextTexture);
	SDL_FreeSurface(helpButtonTextSurface);
	SDL_DestroyTexture(helpButtonTextTexture);
	SDL_FreeSurface(quitButtonTextSurface);
	SDL_DestroyTexture(quitButtonTextTexture);
	TTF_CloseFont(font);

	// Present the renderer
	SDL_RenderPresent(renderer);
}

// Function to handle title screen events
void handleTitleScreenEvents(SDL_Event& event, GameState& gameState, bool& quit)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		int mouseX, mouseY;
		SDL_GetMouseState(&mouseX, &mouseY);

		// Check for button clicks
		if (mouseX >= 200 && mouseX <= 400)
		{
			if (mouseY >= 300 && mouseY <= 350)
			{
				// Start button clicked
				gameState = GameState::GAME_MODE;
			}
			else if (mouseY >= 400 && mouseY <= 450)
			{
				// Help button clicked
				gameState = GameState::HELP_SCREEN;
			}
			else if (mouseY >= 500 && mouseY <= 550)
			{
				// Quit button clicked
				quit = true;
			}
		}
	}
}