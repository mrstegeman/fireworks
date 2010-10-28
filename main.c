/*
 * main.c
 *
 * Author: Michael Stegeman
 * Date: 2/25/08
 *
 * Description: ASCII art fireworks demo
 */

#include "particle.h"
#include <ncurses.h>
#include <stdlib.h>

/*
 * initializes necessary ncurses attributes
 */
void ncurses_init()
{
	initscr(); /* initialize screen */
	noecho(); /* don't display typed characters */
	cbreak(); /* don't wait until RETURN is pressed */
	halfdelay(1); /* don't wait for key press */
	curs_set(0); /* make cursor invisible */
	start_color(); /* start color in terminal */
	init_pair(1, 7, 0); /* White on black */
	init_pair(2, 6, 0); /* Cyan on black */
	init_pair(3, 5, 0); /* Magenta on black */
	init_pair(4, 4, 0); /* Blue on black */
	init_pair(5, 3, 0); /* Yellow on black */
	init_pair(6, 2, 0); /* Green on black */
	init_pair(7, 1, 0); /* Red on black */
}

int main()
{
	int size = 200;
	ncurses_init();

	/* reserve memory for particle array */
	struct particle *p = (struct particle *) malloc(sizeof(struct particle) * size);
	struct particle *q = (struct particle *) malloc(sizeof(struct particle) * size);
	struct particle *r = (struct particle *) malloc(sizeof(struct particle) * size);
	struct particle *s = (struct particle *) malloc(sizeof(struct particle) * size);

	/* initialize particle array */
	particle_init(p, size);
	particle_init(q, size);
	particle_init(r, size);
	particle_init(s, size);

	while(getch() != 'q') /* check for user input to quit program */
	{
		/* check for end of life */
		if(p[0].life < 0.01)
		{
			particle_init(p, size); /* reinitialize array if dead */
		}

		if(p[0].life < 1.21 && p[0].life > 1.19) /* reinitialize second array at 3/4 life of first */
		{
			particle_init(q, size);
		}

		if(p[0].life < 0.81 && p[0].life > 0.79) /* reinitialize third array at 1/2 life of first */
		{
			particle_init(r, size);
		}

		if(p[0].life < 0.41 && p[0].life > 0.39) /* reinitialize fourth array at 1/4 life of first */
		{
			particle_init(s, size);
		}

		erase(); /* erase screen */

		/* update all particles */
		particle_update(p, 0.01, size);
		particle_update(q, 0.01, size);
		particle_update(r, 0.01, size);
		particle_update(s, 0.01, size);

		/* draw all particles to screen */
		particle_draw(p, size);
		particle_draw(q, size);
		particle_draw(r, size);
		particle_draw(s, size);

		refresh(); /* draw particles to screen */
	}

	/* free all memory used */
	free(p);
	p = NULL;
	free(q);
	q = NULL;
	free(r);
	r = NULL;
	free(s);
	s = NULL;
	endwin();
}
