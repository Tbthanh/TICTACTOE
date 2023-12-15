#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

// Tic Tac Toe constants
const int EMPTY = 0;
const int PLAYER_X = 1;
const int PLAYER_O = 2;

// Game state variables
int board[3][3] = {0};
int currentPlayer = PLAYER_X;
int winner = 0;
bool gameStarted = false;

// Function prototypes
void drawStartScreen();
void drawGame();
void drawEndScreen();
void drawText(const char* text, float x, float y);
void checkWin();
void resetGame();

// OpenGL initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glOrtho(0, 800, 600, 0, -1, 1);
}

// Draw text on the screen
void drawText(const char* text, float x, float y) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

// Draw the Tic Tac Toe grid
void drawGrid() {
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    // Vertical lines
    for (int i = 1; i < 3; ++i) {
        glBegin(GL_LINES);
        glVertex2i(i * 200, 0);
        glVertex2i(i * 200, 600);
        glEnd();
    }

    // Horizontal lines
    for (int i = 1; i < 3; ++i) {
        glBegin(GL_LINES);
        glVertex2i(0, i * 200);
        glVertex2i(800, i * 200);
        glEnd();
    }

    glLineWidth(1.0);
}

// Draw X or O in a cell
void drawSymbol(int row, int col) {
    if (board[row][col] == PLAYER_X) {
        glColor3f(0.0, 0.0, 1.0); // Blue for X
        glBegin(GL_LINES);
        glVertex2i(col * 200 + 50, row * 200 + 50);
        glVertex2i(col * 200 + 150, row * 200 + 150);
        glVertex2i(col * 200 + 50, row * 200 + 150);
        glVertex2i(col * 200 + 150, row * 200 + 50);
        glEnd();
    } else if (board[row][col] == PLAYER_O) {
        glColor3f(1.0, 0.0, 0.0); // Red for O
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < 360; i += 10) {
            float angle = i * 3.14159265359 / 180;
            float x = col * 200 + 100 + 50 * cos(angle);
            float y = row * 200 + 100 + 50 * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
}

// Draw the Tic Tac Toe game
void drawGame() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid();

    // Draw X or O in each cell
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            drawSymbol(i, j);
        }
    }

    // Display current player's turn
    glColor3f(0.0, 0.0, 0.0);
    drawText((currentPlayer == PLAYER_X) ? "Player X's turn" : "Player O's turn", 10, 20);

    glutSwapBuffers();
}

// Draw the start screen
void drawStartScreen() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    drawText("Tic Tac Toe", 300, 100);
    drawText("Start", 350, 250);
    drawText("Help", 350, 300);
    drawText("Quit", 350, 350);

    glutSwapBuffers();
}

// Draw the end screen
void drawEndScreen() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);
    if (winner == PLAYER_X)
        drawText("Player X wins!", 300, 100);
    else if (winner == PLAYER_O)
        drawText("Player O wins!", 300, 100);
    else
        drawText("It's a draw!", 320, 100);

    drawText("Again", 350, 250);
    drawText("Title", 350, 300);
    drawText("Quit", 350, 350);

    glutSwapBuffers();
}

// Check for a win or draw
void checkWin() {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
            winner = board[i][0];
            return;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != EMPTY) {
            winner = board[0][i];
            return;
        }
    }

    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        winner = board[0][0];
        return;
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        winner = board[0][2];
        return;
    }

    // Check for a draw
    bool draw = true;
    for (int i = 0; i < 3 && draw; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                draw = false;
                break;
            }
        }
    }

    if (draw)
        winner = 0;
}

// Reset the game state
void resetGame() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = EMPTY;
        }
    }
    currentPlayer = PLAYER_X;
    winner = 0;
}

// Mouse callback function for handling button clicks
void mouse(int button, int state, int x, int y) {
    if (gameStarted) {
        // Handle clicks during the game
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            int row = y / 200;
            int col = x / 200;
            if (board[row][col] == EMPTY && winner == 0) {
                board[row][col] = currentPlayer;
                checkWin();
                if (winner == 0) {
                    currentPlayer = (currentPlayer == PLAYER_X) ? PLAYER_O : PLAYER_X;
                }
            }
        }
    } else {
        // Handle clicks on the start/end screen
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
            int row = y / 50;
            if (!gameStarted) {
                // Start screen buttons
                if (row == 5) {
                    // Start button
                    resetGame();
                    gameStarted = true;
                } else if (row == 6) {
                    // Help button
                    std::cout << "Help: Tic Tac Toe instructions go here!" << std::endl;
                } else if (row == 7) {
                    // Quit button
                    exit(0);
                }
            } else {
                // End screen buttons
                if (row == 5) {
                    // Again button
                    resetGame();
                } else if (row == 6) {
                    // Title button
                    gameStarted = false;
                } else if (row == 7) {
                    // Quit button
                    exit(0);
                }
            }
        }
    }

    glutPostRedisplay();
}

// Display callback function
void display() {
    if (gameStarted) {
        drawGame();
    } else {
        drawStartScreen();
    }

    if (winner != 0 || (gameStarted && winner == 0)) {
        drawEndScreen();
    }
}

// Reshape callback function
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Tic Tac Toe");
    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
