/*
 * particle.c
 *
 * Author: Michael Stegeman
 * Date: 2/25/08
 *
 * Description: Defines particle structures and their methods
 */

#include "particle.h"
#include <ncurses.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

/*
 * initializes array of particles to same position, velocity,
 * color, and life, and random symbols
 */
void particle_init(struct particle *p, int size)
{
	float init_vel;
	int i;
	float col;
	int init_color;
	srand((unsigned)time(NULL)); /* seed rand() function */
	init_vel = ((float) rand()) / ((float) RAND_MAX) * (-40) - 10; /* find random upward velocity */
	init_color = rand() % 7 + 1; /* pick random color */
	col = (rand() % (COLS * 3 / 4)) + (COLS / 8); /* pick random column to start in */
	for(i = 0; i < size; ++i) /* initialize particles */
	{
		p[i].pos[0] = (float)(LINES - 1); /* start particles at bottom of screen */
		p[i].pos[1] = col;
		p[i].vel[0] = init_vel;
		p[i].vel[1] = 0.0;
		p[i].life = 1.6;
		p[i].sym = (char)((rand() % 66) + '#'); /* pick random character */
		p[i].color = init_color;
	}
}

/*
 * updates particles positions, lifetimes, and velocities
 */
void particle_update(struct particle *p, float dt, int size)
{
	int i;
	srand((unsigned)time(NULL)); /* seed rand() function */
	for(i = 0; i < size; ++i)
	{
		p[i].life -= dt;
		p[i].pos[0] += p[i].vel[0]*dt;
		p[i].pos[1] += p[i].vel[1]*dt;
		
		/* check if time to explode */
		if((p[i].life < 0.76) && (p[i].life > 0.74))
		{
			/* explode! */
			p[i].vel[0] = ((float) rand() / (float) RAND_MAX) * 50 - 25;
			p[i].vel[1] = ((float) rand() / (float) RAND_MAX) * 100 - 50;
		}
	}
}

/*
 * draws particles onto display
 */
void particle_draw(struct particle *p, int size)
{
	/* find size of array */
	int i;
	/* turn on color scheme */
	attron(COLOR_PAIR(p[0].color));
	/* draw characters */
	for(i = 0; i < size; ++i)
	{
		/* display bright characters right after explosion */
		if(p[i].life > 0.55 && p[i].life < 0.76)
		{
			attron(A_BOLD);
		}

		/* display dim characters right before dying */
		if(p[i].life < 0.2)
		{
			attron(A_DIM);
		}
		mvaddch(p[i].pos[0], p[i].pos[1], p[i].sym);
	}
	/* turn off color scheme */
	attroff(A_BOLD);
	attroff(A_DIM);
	attroff(COLOR_PAIR(p[0].color));
}
