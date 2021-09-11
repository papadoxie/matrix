#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include "../include/matrix.h"

#define NUM_LINES 512
#define LINE_SPAWN_PROB 0.95
#define CHANGE_PROB 0.65
#define DIM_PROB 0.55

#define CHARACTER (33 + rand() % 126)

typedef struct _line
{
    int x, y;
    int brightness;
    bool live;
} line;

cell matrix[WIDTH][HEIGHT];
line lines[NUM_LINES];

// Returns a random number between 0 and 1
double randProb()
{
    return (double)rand() / (double)RAND_MAX;
}

void initLine()
{
    for (int i = 0; i < NUM_LINES; i++)
    {
        lines[i].live = false;
    }
}

void initMatrix()
{
    // Clear the matrix
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            matrix[i][j].char_value = 0;
            matrix[i][j].intensity = 0;
        }
    }

    // Initialize the line
    initLine();
}

// Spawn a flowing line
void spawnLine()
{
    for (int i = 0; i < NUM_LINES; i++)
    {
        if (lines[i].live == false)
        {
            lines[i].live = true;
            lines[i].x = rand() % WIDTH;
            lines[i].y = 0; //Start flowing from the top
            lines[i].brightness = rand() % 2;
            return;
        }
    }
}

void updateLine()
{
    for (int i = 0; i < NUM_LINES; i++)
    {
        int x = lines[i].x;
        int y = lines[i].y;

        if (lines[i].live)
        {
            if (lines[i].brightness)
            {
                matrix[x][y].intensity = MAX_INTENSITY;
            }
            else
            {
                matrix[x][y].intensity = MIN_INTENSITY;
            }

            lines[i].y += 1;

            if (lines[i].y > HEIGHT)
            {
                lines[i].live = false;
            }
        }
    }
}

void fadeMatrix()
{
    for (int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            if (randProb() < CHANGE_PROB || matrix[i][j].char_value == 0)
            {
                matrix[i][j].char_value = CHARACTER;
            }

            if (randProb() < DIM_PROB)
            {
                if (matrix[i][j].intensity > 0)
                {
                    matrix[i][j].intensity--;
                }
            }

            if(matrix[i][j].intensity == 0)
            {
                matrix[i][j].char_value = ' ';
            }
        }
    }
}

void updateMatrix()
{
    if (randProb() < LINE_SPAWN_PROB)
    {
        spawnLine();
    }
    updateLine();
    fadeMatrix();
}
