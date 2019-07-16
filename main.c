/**
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
#include <time.h>

/**
 * initializes necessary ncurses attributes
 */
void ncurses_init() {
    WINDOW *window = initscr(); // initialize screen
    noecho();                   // don't display typed characters
    cbreak();                   // don't wait until RETURN is pressed
    nodelay(window, TRUE);      // don't wait for key press
    curs_set(0);                // make cursor invisible
    start_color();              // start color in terminal
    init_pair(1, 7, 0);         // White on black
    init_pair(2, 6, 0);         // Cyan on black
    init_pair(3, 5, 0);         // Magenta on black
    init_pair(4, 4, 0);         // Blue on black
    init_pair(5, 3, 0);         // Yellow on black
    init_pair(6, 2, 0);         // Green on black
    init_pair(7, 1, 0);         // Red on black
}

int main() {
    struct timespec interval = { .tv_sec = 0, .tv_nsec = 25000000 };
    size_t size = 200;

    ncurses_init();
    srand((unsigned) time(NULL));

    // reserve memory for particle array
    particle *p = (particle *) calloc(sizeof(particle), size);
    particle *q = (particle *) calloc(sizeof(particle), size);
    particle *r = (particle *) calloc(sizeof(particle), size);
    particle *s = (particle *) calloc(sizeof(particle), size);

    // initialize particle array
    particle_init(p, size);
    particle_init(q, size);
    particle_init(r, size);
    particle_init(s, size);

    // check for user input to quit program
    while (getch() != 'q') {
        if (p[0].life < 1.21 && p[0].life > 1.19) {
            // reinitialize second array at 3/4 life of first
            particle_init(q, size);
        } else if (p[0].life < 0.81 && p[0].life > 0.79) {
            // reinitialize third array at 1/2 life of first
            particle_init(r, size);
        } else if (p[0].life < 0.41 && p[0].life > 0.39) {
            // reinitialize fourth array at 1/4 life of first
            particle_init(s, size);
        } else if (p[0].life < 0.01) {
            // check for end of life and reinitialize array if dead
            particle_init(p, size);
        }

        // erase screen
        erase();

        // update all particles
        particle_update(p, 0.01, size);
        particle_update(q, 0.01, size);
        particle_update(r, 0.01, size);
        particle_update(s, 0.01, size);

        // draw all particles to screen
        particle_draw(p, size);
        particle_draw(q, size);
        particle_draw(r, size);
        particle_draw(s, size);

        // draw particles to screen
        refresh();

        // wait a bit
        nanosleep(&interval, NULL);
    }

    free(p);
    p = NULL;
    free(q);
    q = NULL;
    free(r);
    r = NULL;
    free(s);
    s = NULL;

    endwin();

    return 0;
}
