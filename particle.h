/*
 * particle.h
 *
 * Author: Michael Stegeman
 * Date: 2/25/08
 *
 * Description: Forward declaration of particle structure
 */

struct particle
{
	float pos[2];
	float vel[2];
	float life;
	char sym;
	int color;
};

void particle_init(struct particle *p, int size);

void particle_update(struct particle *p, float dt, int size);

void particle_draw(struct particle *p, int size);
