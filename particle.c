/**
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

/**
 * initializes array of particles to same position, velocity,
 * color, and life, and random symbols
 */
void particle_init(particle *p, size_t size) {
    float init_vel, col;
    size_t i;
    uint8_t init_color;

    // pick random upward velocity
    init_vel = (((float) rand()) / ((float) RAND_MAX) * (-LINES) - (LINES / (rand() % 4 + 1))) * 0.8;

    // pick random color
    init_color = (uint8_t) (rand() % 8);

    // pick random starting column
    col = rand() % COLS;

    // initialize particles
    for (i = 0; i < size; ++i) {
        p[i].pos[0] = (float) (LINES - 1); // start particles at bottom
        p[i].pos[1] = col;
        p[i].vel[0] = init_vel;
        p[i].vel[1] = 0.0;
        p[i].life = 1.6;
        p[i].color = init_color;
        p[i].exploded = FALSE;
    }
}

/**
 * updates particles positions, lifetimes, and velocities
 */
void particle_update(particle *p, float dt, size_t size) {
    size_t i;

    for (i = 0; i < size; ++i) {
        p[i].life -= dt;
        p[i].pos[0] += p[i].vel[0] * dt;
        p[i].pos[1] += p[i].vel[1] * dt;

        // check if time to explode
        if (p[i].life < 0.76 && !p[i].exploded) {
            p[i].exploded = TRUE;

            p[i].center[0] = p[i].pos[0];
            p[i].center[1] = p[i].pos[1];

            p[i].vel[0] = ((float) rand() / (float) RAND_MAX) * 50 - 25;
            p[i].vel[1] = ((float) rand() / (float) RAND_MAX) * 100 - 50;
        }
    }
}

/**
 * draws particles onto display
 */
void particle_draw(particle *p, size_t size) {
    size_t i;

    // turn on color scheme
    attron(COLOR_PAIR(p[0].color));

    for (i = 0; i < size; ++i) {
        // display bright characters right after explosion
        if (p[i].life > 0.55 && p[i].life < 0.76) {
            attron(A_BOLD);
        }

        // display dim characters right before dying
        if (p[i].life < 0.2) {
            attron(A_DIM);
        }

        float distance = sqrt(
            pow(p[i].pos[0] - p[i].center[0], 2) +       // line
            pow((p[i].pos[1] - p[i].center[1]) * 0.6, 2) // column, scaled down
        );
        if (p[i].exploded && distance > 9.5) {
            continue;
        }

        // draw the character
        mvaddch(p[i].pos[0], p[i].pos[1], 'o');
    }

    // turn off color scheme
    attroff(A_BOLD);
    attroff(A_DIM);
    attroff(COLOR_PAIR(p[0].color));
}
