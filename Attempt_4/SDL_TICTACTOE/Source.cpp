﻿/*
Title		:Xay dung game co ca ro su dung C++ va SDL
Author		:nhom 26 - Tran Ba Thanh
Support		:nhom 26 - Nguyen Duy Nhat Quang, nhom 26 - Pham Huu Quang Khai
Date created:15-12-2023
Last edited	: 15-12-2023

This code was writen with the help of OpenAI-ChatGPT and some handsome Indian guys
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <SDL.h>
#include "D:\TAI_LIEU\ET-E9\Program\20231\Ky_thuat_lap_trinh_C_Cpp\TICTACTOE\SDL_learnin\SDL2_gfx-1.0.1\SDL2_gfx-1.0.1\SDL2_gfxPrimitives.h"
#include "D:\TAI_LIEU\ET-E9\Program\20231\Ky_thuat_lap_trinh_C_Cpp\TICTACTOE\SDL_learnin\SDL2_ttf-devel-2.0.14-VC\include\SDL_ttf.h"
#include "GameState.h"
#include "TitleScreen.h"

// Define some constant
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

using namespace std;
int BOARD_SIZE = 3;
float CELL_WIDTH = WINDOW_WIDTH / BOARD_SIZE;
float CELL_HEIGHT = WINDOW_HEIGHT / BOARD_SIZE;

// Game logic class 
enum class Player {NONE, X, O};
Player currentPlayer = Player::X;
Player winner = Player::X;

// Outer vector is the row
vector <vector<Player>> board;

// Function to change board size
void changeBOARD_SIZE(int newBOARD_SIZE = 3)
{	
	BOARD_SIZE = newBOARD_SIZE;
	CELL_WIDTH = WINDOW_WIDTH / BOARD_SIZE;
	CELL_HEIGHT = WINDOW_HEIGHT / BOARD_SIZE;
	board.assign(BOARD_SIZE, vector<Player>(BOARD_SIZE, Player::NONE));
}

// Function to render Gamemode
void renderGamemode(SDL_Renderer* renderer)
{
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Render Gamemode text
	TTF_Font* font = TTF_OpenFont("D:/TAI_LIEU/ET-E9/Program/20231/Ky_thuat_lap_trinh_C_Cpp/TICTACTOE/Attempt_3/SDL_TICTACTOE/arial.ttf", 24);  // Replace with your font file
	SDL_Color textColor = { 0, 0, 0, 255 };  // Black text color

	const char* gmText =
		"Choose game mode";

	SDL_Surface* gmTextSurface = TTF_RenderText_Blended_Wrapped(font, gmText, textColor, 400);  // 400 is the wrap length
	SDL_Texture* gmTextTexture = SDL_CreateTextureFromSurface(renderer, gmTextSurface);
	SDL_Rect gmTextRect = { 150, 10, 400, 100 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, gmTextTexture, nullptr, &gmTextRect);

	// Render button
	SDL_Rect x3Button = { 200, 300, 200, 50 };
	SDL_SetRenderDrawColor(renderer, 4, 170, 109, 255); // #04aa6d color RGB value is (4,170,109)
	SDL_RenderFillRect(renderer, &x3Button);

	SDL_Rect x5Button = { 200, 400, 200, 50 };
	SDL_SetRenderDrawColor(renderer, 104, 204, 167, 255); // #68cca7 color RGB value is (104,204,167)
	SDL_RenderFillRect(renderer, &x5Button);

	SDL_Rect x10Button = { 200, 500, 200, 50 };
	SDL_SetRenderDrawColor(renderer, 179, 229, 211, 255); // #b3e5d3 color RGB value is (179,229,211)
	SDL_RenderFillRect(renderer, &x10Button);

	const char* x3ButtonText = "03x03   ";
	SDL_Surface* x3ButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, x3ButtonText, textColor, 10);  // 400 is the wrap length
	SDL_Texture* x3ButtonTextTexture = SDL_CreateTextureFromSurface(renderer, x3ButtonTextSurface);
	SDL_Rect x3ButtonTextRect = { 210, 300, 150, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, x3ButtonTextTexture, nullptr, &x3ButtonTextRect);

	const char* x5ButtonText = "05x05   ";
	SDL_Surface* x5ButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, x5ButtonText, textColor, 10);
	SDL_Texture* x5ButtonTextTexture = SDL_CreateTextureFromSurface(renderer, x5ButtonTextSurface);
	SDL_Rect x5ButtonTextRect = { 210, 400, 150, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, x5ButtonTextTexture, nullptr, &x5ButtonTextRect);

	const char* x10ButtonText = "10x10   ";
	SDL_Surface* x10ButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, x10ButtonText, textColor, 10);
	SDL_Texture* x10ButtonTextTexture = SDL_CreateTextureFromSurface(renderer, x10ButtonTextSurface);
	SDL_Rect x10ButtonTextRect = { 210, 500, 150, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, x10ButtonTextTexture, nullptr, &x10ButtonTextRect);

	// Free resources
	SDL_FreeSurface(gmTextSurface);
	SDL_DestroyTexture(gmTextTexture);
	SDL_FreeSurface(x3ButtonTextSurface);
	SDL_DestroyTexture(x3ButtonTextTexture);
	SDL_FreeSurface(x5ButtonTextSurface);
	SDL_DestroyTexture(x5ButtonTextTexture);
	SDL_FreeSurface(x10ButtonTextSurface);
	SDL_DestroyTexture(x10ButtonTextTexture);
	TTF_CloseFont(font);

	// Present the renderer
	SDL_RenderPresent(renderer);
}

// Function to handle Gamemode
void handleGamemodeScreenEvents(SDL_Event& event, GameState& gameState)
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
				changeBOARD_SIZE(3);
				gameState = GameState::GAME_PLAY;
			}
			else if (mouseY >= 400 && mouseY <= 450)
			{
				changeBOARD_SIZE(5);
				gameState = GameState::GAME_PLAY;
			}
			else if (mouseY >= 500 && mouseY <= 550)
			{
				changeBOARD_SIZE(10);
				gameState = GameState::GAME_PLAY;
			}
		}
	}
}

// Function to check for a winner
void checkForWinner(GameState& gameState)
{
	int row_count = 0;
	int column_count = 0;
	int diag1_count = 0;
	int diag2_count = 0;

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		// Check for column and row
		row_count = 0;
		column_count = 0;
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			if (board[i][j] == currentPlayer) 
			{
				row_count++;
			}

			if (board[j][i] == currentPlayer) 
			{
				column_count++;
			}
			if (row_count >= BOARD_SIZE || column_count >= BOARD_SIZE) 
			{
				winner = currentPlayer;
				gameState = GameState::WIN_SCREEN;
				return;
			}
		}

		// Check for diagnal
		if (board[i][i] == currentPlayer)
		{
			diag1_count++;
		}

		if (board[(BOARD_SIZE - 1) - i][i] == currentPlayer)
		{
			diag2_count++;
		}
	}
	if (diag1_count >= BOARD_SIZE || diag2_count >= BOARD_SIZE)
	{
		winner = currentPlayer;
		gameState = GameState::WIN_SCREEN;
		return;
	}

	// Check for a draw
	bool draw = true;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (board[i][j] == Player::NONE)
			{
				draw = false;
				break;
			}
		}
		if (!draw)
		{
			break;
		}
	}

	if (draw)
	{
		gameState = GameState::DRAW_SCREEN;  // Adjust to the appropriate draw state
		return;
	}
	// No 5 or 3 depend on BOARD_SIZE  in a row/diagonal/column; nothing happens
}

// Function handling player moves
void handleMove(int m_row, int m_col, GameState& gameState)
{
	if (board[m_row][m_col] == Player::NONE)
	{
		board[m_row][m_col] = currentPlayer;

		// Check for a winner
		checkForWinner(gameState);
		
		// Switch players
		currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
	}
}

void resetBoard()
{
	// Reset all entries in the board array to Player::NONE
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j] = Player::NONE;
		}
	}

	// Reset the current player to Player::X
	currentPlayer = Player::X;
}

// Function to render the win screen
void renderWinScreen(SDL_Renderer* renderer, Player _winner)
{
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Render help text
	TTF_Font* font = TTF_OpenFont("D:/TAI_LIEU/ET-E9/Program/20231/Ky_thuat_lap_trinh_C_Cpp/TICTACTOE/Attempt_3/SDL_TICTACTOE/arial.ttf", 24);  // Replace with your font file
	SDL_Color textColor = { 0, 0, 0, 255 };  // Black text color

	if (winner == Player::X)
	{
		const char* winText = "Player X Wins!";
		SDL_Surface* winTextSurface = TTF_RenderText_Blended_Wrapped(font, winText, textColor, 400);  // 400 is the wrap length
		SDL_Texture* winTextTexture = SDL_CreateTextureFromSurface(renderer, winTextSurface);

		SDL_Rect winTextRect = { 100, 100, 700, 200 };  // Adjust position and size accordingly
		SDL_RenderCopy(renderer, winTextTexture, nullptr, &winTextRect);

		// Free resources
		SDL_FreeSurface(winTextSurface);
		SDL_DestroyTexture(winTextTexture);
		TTF_CloseFont(font);
	}
	else if (winner == Player::O)
	{
		const char* winText = "Player O Wins!";
		SDL_Surface* winTextSurface = TTF_RenderText_Blended_Wrapped(font, winText, textColor, 400);  // 400 is the wrap length
		SDL_Texture* winTextTexture = SDL_CreateTextureFromSurface(renderer, winTextSurface);

		SDL_Rect winTextRect = { 100, 100, 700, 200 };  // Adjust position and size accordingly
		SDL_RenderCopy(renderer, winTextTexture, nullptr, &winTextRect);

		// Free resources
		SDL_FreeSurface(winTextSurface);
		SDL_DestroyTexture(winTextTexture);
		TTF_CloseFont(font);
	}

	// Present the renderer
	SDL_RenderPresent(renderer);
}

// Function to handle win screen events
void handleWinScreenEvents(SDL_Event& event, GameState& gameState)
{
	resetBoard();

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		// Transition back to the title screen when any key is pressed
		gameState = GameState::TITLE_SCREEN;
	}
}

// Function to render the draw screen
void renderDrawScreen(SDL_Renderer* renderer)
{
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Render help text
	TTF_Font* font = TTF_OpenFont("D:/TAI_LIEU/ET-E9/Program/20231/Ky_thuat_lap_trinh_C_Cpp/TICTACTOE/Attempt_3/SDL_TICTACTOE/arial.ttf", 24);  // Replace with your font file
	SDL_Color textColor = { 0, 0, 0, 255 };  // Black text color


	const char* drawText = "It's a draw!";

	SDL_Surface* drawTextSurface = TTF_RenderText_Blended_Wrapped(font, drawText, textColor, 400);  // 400 is the wrap length
	SDL_Texture* drawTextTexture = SDL_CreateTextureFromSurface(renderer, drawTextSurface);

	SDL_Rect drawTextRect = { 100, 100, 700, 200 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, drawTextTexture, nullptr, &drawTextRect);

	// Free resources
	SDL_FreeSurface(drawTextSurface);
	SDL_DestroyTexture(drawTextTexture);
	TTF_CloseFont(font);

	// Present the renderer
	SDL_RenderPresent(renderer);
}

// Function to handle draw screen events
void handleDrawScreenEvents(SDL_Event& event, GameState& gameState)
{
	resetBoard();
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		// Transition back to the title screen when any key is pressed
		gameState = GameState::TITLE_SCREEN;
	}
}

// Function to draw the playing board
void drawBoard(SDL_Renderer* renderer)
{
	// Set draw color to black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Draw horizontal lines
	for (int i = 1; i < BOARD_SIZE; ++i)
	{
		SDL_RenderDrawLine(renderer, 0, i * (WINDOW_HEIGHT / BOARD_SIZE), WINDOW_WIDTH, i * (WINDOW_HEIGHT / BOARD_SIZE));
	}
	// Draw vertical line
	for (int i = 1; i < BOARD_SIZE; ++i)
	{
		SDL_RenderDrawLine(renderer, i * (WINDOW_WIDTH / BOARD_SIZE), 0, i * (WINDOW_WIDTH / BOARD_SIZE), WINDOW_HEIGHT);
	}
}

// Draw X,O based on player and board position
void drawSymbol(SDL_Renderer* renderer, int m_row, int m_col, Player player)
{
	if (player == Player::X) 
	{
		const double half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
		const double center_x = (CELL_WIDTH) * 0.5 + m_col * CELL_WIDTH;
		const double center_y = (CELL_HEIGHT) * 0.5 + m_row * CELL_HEIGHT;

		// Draw a line from (x1,y1) to (x2,y2)
		thickLineRGBA(renderer, 
			center_x - half_box_size, // x1
			center_y - half_box_size, // y1
			center_x + half_box_size, // x2
			center_y + half_box_size, // y2
			10,
			255, 51, 51, 255);
		thickLineRGBA(renderer,
			center_x + half_box_size,
			center_y - half_box_size,
			center_x - half_box_size,
			center_y + half_box_size,
			10, 255, 51, 51, 255);
	}
	else if (player == Player::O) {
		const double half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
		const double center_x = (CELL_WIDTH) * 0.5 + m_col * CELL_WIDTH;
		const double center_y = (CELL_HEIGHT) * 0.5 + m_row * CELL_HEIGHT;

		filledCircleRGBA(renderer,
			center_x, center_y, half_box_size + 5,
			51, 153, 255, 255);
		filledCircleRGBA(renderer,
			center_x, center_y, half_box_size - 5,
			255, 255, 255, 255);
	}
}

// Rendering code
void renderGameplay(SDL_Renderer* renderer)
{
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Draw the Tic-Tac-Toe board
	drawBoard(renderer);

	// Draw the X and O symbol based on board state
	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			drawSymbol(renderer, i, j, board[i][j]);
		}
	}

	// Present the renderer
	SDL_RenderPresent(renderer);
}

// Function to render the help screen
void renderHelpScreen(SDL_Renderer* renderer)
{
	// Clear the renderer
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	// Render help text
	TTF_Font* font = TTF_OpenFont("D:/TAI_LIEU/ET-E9/Program/20231/Ky_thuat_lap_trinh_C_Cpp/TICTACTOE/Attempt_3/SDL_TICTACTOE/arial.ttf", 20);  // Replace with your font file
	SDL_Color textColor = { 0, 0, 0, 255 };  // Black text color

	const char* helpText = "Welcome to Tic-Tac-Toe!\n"
							"Made by Nhom 26 with love for A+ KTLT & Huy sensei.\n"
							"Instructions:\n"
							"- Click on an empty cell to make a move.\n"
							"- Try to get three or five of your symbols in a row, column, or diagonal to win.\n"
							"- Switch turns with your opponent after each move.\n"
							"- Have fun playing!";

	SDL_Surface* helpTextSurface = TTF_RenderText_Blended_Wrapped(font, helpText, textColor, 400);  // 400 is the wrap length
	SDL_Texture* helpTextTexture = SDL_CreateTextureFromSurface(renderer, helpTextSurface);

	SDL_Rect helpTextRect = { 30, 30, 600, 500 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, helpTextTexture, nullptr, &helpTextRect);

	// Free resources
	SDL_FreeSurface(helpTextSurface);
	SDL_DestroyTexture(helpTextTexture);
	TTF_CloseFont(font);

	// Present the renderer
	SDL_RenderPresent(renderer);
}

// Function to handle help screen events
void handleHelpScreenEvents(SDL_Event& event, GameState& gameState)
{
	if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		// Transition back to the title screen when any key is pressed
		gameState = GameState::TITLE_SCREEN;
	}
}

// MAIN
int main(int argc, char* argv[])
{
	// test SDL working or not
	//cout << "Hello world!" << endl;
	//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello world", "Successfull", NULL);

	// Initialize SDL and SDL_ttf
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("Unable to Initialize SDL: %s", SDL_GetError());
		return 1;
	}

	SDL_SetHint(SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING, "1");  // Disable thread naming to avoid potential conflicts
	if (TTF_Init() != 0)
	{
		SDL_Log("Unable to initialize SDL_ttf: %s", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	// Create a window
	// https://wiki.libsdl.org/SDL2/SDL_WINDOWPOS_CENTERED
	// with w = 800p, h = 600p
	// the SDL wiki doesnt have definition for SDL_WINDOWPOS_CENTERED so ...
	SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe / X-O ghem rat hay", 
													SDL_WINDOWPOS_CENTERED, 
													SDL_WINDOWPOS_CENTERED, 
													WINDOW_WIDTH, WINDOW_HEIGHT, 0);
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
	GameState gameState = GameState::TITLE_SCREEN;
	bool quit = false;

	while (!quit)
	{
		// Reference: https://wiki.libsdl.org/SDL2/SDL_Event
		// To simplify, it a union that contain struct for different event
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}

			// Check events based on the current game State
			switch(gameState)
			{
				case GameState::TITLE_SCREEN: 
					handleTitleScreenEvents(event, gameState, quit);
					break;

				case GameState::GAME_MODE:
					handleGamemodeScreenEvents(event, gameState);
					break;

				case GameState::GAME_PLAY:
					// Handle mouse click or keyboard for player moves
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);

						// Convert mouse coordiantes to board section
						int m_row = mouseY / (WINDOW_HEIGHT / BOARD_SIZE);
						int m_col = mouseX / (WINDOW_WIDTH / BOARD_SIZE);

						// Handle player move
						handleMove(m_row, m_col, gameState);
					}
					break;

				case GameState::HELP_SCREEN:
					handleHelpScreenEvents(event, gameState);
					break;

				case GameState::WIN_SCREEN:
					handleWinScreenEvents(event, gameState);
					break;

				case GameState::DRAW_SCREEN:
					handleDrawScreenEvents(event, gameState);
					break;
			}
		}

		// games logic and rendering go here
		switch (gameState)
		{
		case GameState::TITLE_SCREEN:
			renderTitleScreen(renderer);
			break;

		case GameState::GAME_MODE:
			renderGamemode(renderer);
			break;

		case GameState::GAME_PLAY:
			renderGameplay(renderer);
			break;

		case GameState::HELP_SCREEN:
			renderHelpScreen(renderer);
			break;

		case GameState::WIN_SCREEN:
			renderWinScreen(renderer, winner);
			break;

		case GameState::DRAW_SCREEN:
			renderDrawScreen(renderer);
			break;
		}
	}

	//Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}