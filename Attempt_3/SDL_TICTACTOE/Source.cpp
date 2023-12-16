/*
Title		:Xay dung game X-O su dung C++ va SDL
Author		:nhom 26 - Tran Ba Thanh, Nguyen Duy Nhat Quang, Pham Huu Quang Khai
Date created:15-12-2023
Last edited	: 15-12-2023

This code was writen with the help of OpenAI-ChatGPT and some handsome Indian guys
*/

#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include "D:\TAI_LIEU\ET-E9\Program\20231\Ky_thuat_lap_trinh_C_Cpp\TICTACTOE\SDL_learnin\SDL2_gfx-1.0.1\SDL2_gfx-1.0.1\SDL2_gfxPrimitives.h"
#include "D:\TAI_LIEU\ET-E9\Program\20231\Ky_thuat_lap_trinh_C_Cpp\TICTACTOE\SDL_learnin\SDL2_ttf-devel-2.0.14-VC\include\SDL_ttf.h"

// Define some constant
#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800
#define CELL_WIDTH WINDOW_WIDTH/3
#define CELL_HEIGHT WINDOW_HEIGHT/3

using namespace std;

// Game logic class 
enum class Player {NONE, X, O};
Player currentPlayer = Player::X;
Player board[3][3] = {{Player::NONE, Player::NONE, Player::NONE},
					  {Player::NONE, Player::NONE, Player::NONE},
					  {Player::NONE, Player::NONE, Player::NONE}};
Player winner = Player::X;

enum class GameState {TITLE_SCREEN, GAME_PLAY, HELP_SCREEN, WIN_SCREEN, DRAW_SCREEN};

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
					"Tic-Tac-Toe!\n"
					"Made by: Nhom 26";

	SDL_Surface* titleTextSurface = TTF_RenderText_Blended_Wrapped(font, titleText, textColor, 400);  // 400 is the wrap length
	SDL_Texture* titleTextTexture = SDL_CreateTextureFromSurface(renderer, titleTextSurface);

	SDL_Rect titleTextRect = { 150, 10, 700, 200 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, titleTextTexture, nullptr, &titleTextRect);


	const char* startButtonText		= "Start  ";

	SDL_Surface* startButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, startButtonText, textColor, 10);  // 400 is the wrap length
	SDL_Texture* startButtonTextTexture = SDL_CreateTextureFromSurface(renderer, startButtonTextSurface);

	SDL_Rect startButtonTextRect = { 210, 300, 180, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, startButtonTextTexture, nullptr, &startButtonTextRect);

	const char* helpButtonText		= "Help   ";
	
	SDL_Surface* helpButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, helpButtonText, textColor, 10);
	SDL_Texture* helpButtonTextTexture = SDL_CreateTextureFromSurface(renderer, helpButtonTextSurface);

	SDL_Rect helpButtonTextRect = { 210, 400, 180, 50 };  // Adjust position and size accordingly
	SDL_RenderCopy(renderer, helpButtonTextTexture, nullptr, &helpButtonTextRect);

	const char* quitButtonText		= "Quit   ";

	SDL_Surface* quitButtonTextSurface = TTF_RenderText_Blended_Wrapped(font, quitButtonText, textColor, 10); 
	SDL_Texture* quitButtonTextTexture = SDL_CreateTextureFromSurface(renderer, quitButtonTextSurface);

	SDL_Rect quitButtonTextRect = { 210, 500, 180, 50 };  // Adjust position and size accordingly
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
				gameState = GameState::GAME_PLAY;
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

// Function handling player moves
void handleMove(int row, int col)
{
	if (board[row][col] == Player::NONE)
	{
		board[row][col] = currentPlayer;
		
		// Switch players
		currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
	}
}

// Function to check for a winner
void checkForWinner(GameState& gameState)
{
	// Own homecook winning conditions
	// Check for 3 in a row or 3 in a colum (check cot/hang)
	for (int i = 0; i < 3; i++) 
	{
		if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
			(board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer)) 
		{
			winner = currentPlayer;
			gameState = GameState::WIN_SCREEN;
			return;
		}
	}
	// Check for 3 in a diagnal (check duong cheo)
	if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
		(board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) 
	{
		winner = currentPlayer;
		gameState = GameState::WIN_SCREEN;
		return;
	}

	// Check for a draw
	bool draw = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == Player::NONE) {
				draw = false;
				break;
			}
		}
		if (!draw) {
			break;
		}
	}

	if (draw) {
		gameState = GameState::DRAW_SCREEN;  // Adjust to the appropriate draw state
	}

	// No 3 in a row/diagnal/colum nothing happen
}

void resetBoard()
{
	// Reset all entries in the board array to Player::NONE
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
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
	for (int i = 1; i < 3; ++i)
	{
		SDL_RenderDrawLine(renderer, 0, i * (600 / 3), 800, i * (600 / 3));
	}
	// Draw vertical line
	for (int i = 1; i < 3; ++i)
	{
		SDL_RenderDrawLine(renderer, i * (800 / 3), 0, i * (800 / 3), 600);
	}
}

// Draw X,O based on player and board position
void drawSymbol(SDL_Renderer* renderer, int row, int col, Player player)
{
	/*
	* Comment out cause no need but still want it to remaain for future use.
	// Set draw collor to red for X and blue for 0
	if (player == Player::X)
	{
		SDL_SetRenderDrawColor(renderer, 255, 51, 51, 255);
	}
	else if (player == Player::O)
	{
		SDL_SetRenderDrawColor(renderer, 51, 153, 255, 255);
	}
	*/
	// Draw X or O based on player and board position
	if (player == Player::X) 
	{
		const double half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
		const double center_x = (CELL_WIDTH) * 0.5 + col * CELL_WIDTH;
		const double center_y = (CELL_HEIGHT) * 0.5 + row * CELL_HEIGHT;

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
			10,
			255,
			51,
			51,
			255);

		// Old render technique: ugly line and just 1 pixel wide
		//SDL_RenderDrawLine(renderer, col * (800 / 3), row * (600 / 3), (col + 1) * (800 / 3), (row + 1) * (600 / 3));
		//SDL_RenderDrawLine(renderer, col * (800 / 3), (row + 1) * (600 / 3), (col + 1) * (800 / 3), row * (600 / 3));
	}
	else if (player == Player::O) {
		const double half_box_size = fmin(CELL_WIDTH, CELL_HEIGHT) * 0.25;
		const double center_x = (CELL_WIDTH) * 0.5 + col * CELL_WIDTH;
		const double center_y = (CELL_HEIGHT) * 0.5 + row * CELL_HEIGHT;

		filledCircleRGBA(renderer,
			center_x, center_y, half_box_size + 5,
			51, 153, 255, 255);
		filledCircleRGBA(renderer,
			center_x, center_y, half_box_size - 5,
			255, 255, 255, 255);

		/*
		int centerX = col * (800 / 3) + (800 / 6);
		int centerY = row * (600 / 3) + (600 / 6);
		int radius = (800 / 3) / 2;

		// Draw a circle
		for (int i = 0; i <= 360; i += 1)
		{
			double rad = i * (3.14159265 / 180);
			int x = centerX + radius * cos(rad);
			int y = centerY + radius * sin(rad);
			SDL_RenderDrawPoint(renderer, x, y);
		}
		*/
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
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
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
	TTF_Font* font = TTF_OpenFont("D:/TAI_LIEU/ET-E9/Program/20231/Ky_thuat_lap_trinh_C_Cpp/TICTACTOE/Attempt_3/SDL_TICTACTOE/arial.ttf", 24);  // Replace with your font file
	SDL_Color textColor = { 0, 0, 0, 255 };  // Black text color

	const char* helpText = "Welcome to Tic-Tac-Toe!\n"
							"Made by Nhom 26 with love for KTLT & Huy sensei.\n\n"
							"Instructions:\n"
							"- Click on an empty cell to make a move.\n"
							"- Try to get three of your symbols in a row, column, or diagonal to win.\n"
							"- Switch turns with your opponent after each move.\n"
							"- Have fun playing!";

	SDL_Surface* helpTextSurface = TTF_RenderText_Blended_Wrapped(font, helpText, textColor, 400);  // 400 is the wrap length
	SDL_Texture* helpTextTexture = SDL_CreateTextureFromSurface(renderer, helpTextSurface);

	SDL_Rect helpTextRect = { 50, 50, 700, 500 };  // Adjust position and size accordingly
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

				case GameState::GAME_PLAY:
					// Handle mouse click or keyboard for player moves
					if (event.type == SDL_MOUSEBUTTONDOWN)
					{
						int mouseX, mouseY;
						SDL_GetMouseState(&mouseX, &mouseY);

						// Convert mouse coordiantes to board section
						int row = mouseY / (600 / 3);
						int col = mouseX / (800 / 3);

						// Handle player move
						handleMove(row, col);
					}
					// Check for a winner
					checkForWinner(gameState);
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