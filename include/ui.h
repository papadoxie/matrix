#pragma once

#ifndef _UI_H
#define _UI_H

#include <wchar.h>

#define WIDTH 256
#define HEIGHT 60

#define MAX_INTENSITY 13
#define MIN_INTENSITY 3

#define CURSES_MIN_COLOR_PAIRS 6

typedef struct _cell
{
    unsigned int char_value;
    int intensity;
} cell;

extern cell matrix[WIDTH][HEIGHT];

bool uiInit();
void uiCleanup();
void showMatrix();

#endif