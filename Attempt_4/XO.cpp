#include <iostream>
#include <SDL.h>

using namespace std;

enum class Player { NONE, X, O };
Player currentPlayer = Player::X;
Player** board;
int rows = 3;
int cols = 3;

enum class GameState { TITLE_SCREEN, GAME_PLAY, HELP_SCREEN, WIN_SCREEN, CREDIT_SCREEN };

void updateBoardSize(int newRows, int newCols)
{
    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;

    rows = newRows;
    cols = newCols;

    board = new Player * [rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new Player[cols];
        for (int j = 0; j < cols; ++j) {
            board[i][j] = Player::NONE;
        }
    }
}

void drawBoard(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    for (int i = 1; i < rows; ++i) {
        SDL_RenderDrawLine(renderer, 0, i * (600 / rows), 800, i * (600 / rows));
    }

    for (int i = 1; i < cols; ++i) {
        SDL_RenderDrawLine(renderer, i * (800 / cols), 0, i * (800 / cols), 600);
    }
}

void handleTitleScreenEvents(SDL_Event& event, GameState& gameState, bool& quit)
{
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_1) {
            updateBoardSize(3, 3);
        }
        else if (event.key.keysym.sym == SDLK_2) {
            updateBoardSize(4, 4);
        }
    }
}

int main(int argc, char* argv[])
{
    board = new Player * [rows];
    for (int i = 0; i < rows; ++i) {
        board[i] = new Player[cols];
        for (int j = 0; j < cols; ++j) {
            board[i][j] = Player::NONE;
        }
    }

    // Game loop and event handling

    for (int i = 0; i < rows; ++i) {
        delete[] board[i];
    }
    delete[] board;

    return 0;
}s
