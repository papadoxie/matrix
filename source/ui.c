#include <string.h>
#include <curses.h>
#include <unistd.h>
#include <locale.h>
#include "../include/ui.h"

WINDOW *matrixWindow = NULL;

int colorMap[MAX_INTENSITY + 1] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 4, 5, 3, 6};

void setColors()
{
    // Use terminal colors
    use_default_colors();

    // Set background
    for (int i = 0; i < 8; i++)
    {
        init_pair(i + 1, i, -1);
    }

    // Set shades of green
    for (int i = 0; i < 6; i++)
    {
        init_color(i, 0, i * 200, 0);
    }
    // Set brightest color
    init_color(6, 800, 1000, 800);
}

bool uiInit()
{
    //Add support for unicode characters
    setlocale(LC_ALL, "");
    
    //Initialize ncurses
    matrixWindow = initscr();

    // Dont wait for user input
    nodelay(matrixWindow, true);

    // Make cursor invisible
    curs_set(0);

    //Check to see if ncurses initialized successfully
    if (matrixWindow == NULL)
    {
        return false;
    }

    //Initialize 256-color
    start_color();

    // Check whether colors are supported by terminal
    if (!has_colors() || !can_change_color() || COLOR_PAIRS < CURSES_MIN_COLOR_PAIRS)
    {
        puts("Your terminal does not support xterm-256color");
        return false;
    }

    setColors();

    return true;
}

// Cleanup before exiting
void uiCleanup()
{
    delwin(matrixWindow);
    endwin();
    refresh();
}

// Paint the matrix on the terminal
void showMatrix()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            int intensity = matrix[i][j].intensity;
            color_set(colorMap[intensity], NULL);
            mvaddch(j, i, matrix[i][j].char_value);
        }
    }

    refresh();
}