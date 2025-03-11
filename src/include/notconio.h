/* 
    Duplicate or similar to CONIO functions
*/

#ifndef NOTCONIO_H
#define NOTCONIO_H

#include <stdbool.h>
#include <string.h>

// Text mode compatibility functions
void clrscr(void);
void cputsxy(unsigned int x, unsigned int y, const char* str);
void cputcxy(unsigned int x, unsigned int y, char c);
void gotoxy(unsigned int x, unsigned int y);
void cursor(int show);
int cgetc(void);
void refresh(void);
void echo(void);

// Display functions
void output_message(void);
void draw_screen(void);
void draw_momentary_object(unsigned int obj_old_x, unsigned int obj_old_y, 
                          unsigned int obj_x, unsigned int obj_y, 
                          unsigned int obj_tile, unsigned int delay);
void draw_move(bool replace);


#endif /* NOTCONIO_H */ 