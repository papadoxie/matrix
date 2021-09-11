#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include "../include/matrix.h"
#include "../include/ui.h"

#define REFRESH_DELAY 40000

int main()
{
    if (!uiInit())
    {
        return EXIT_FAILURE;
    }

    initMatrix();

    while (getch() != 'q')
    {
        updateMatrix();
        showMatrix();
        usleep(REFRESH_DELAY);
    }

    uiCleanup();

    return EXIT_SUCCESS;
}