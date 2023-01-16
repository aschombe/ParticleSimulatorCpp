#pragma once
#include <math.h>
#include <iostream>

class Particle {
public:
	double x, y, xvel, yvel, mass;
	int size;
	static constexpr int timescale = 3;
	static constexpr double G = 20;
	Particle() {
		this->x = x;
		this->y = y;
		this->xvel = xvel;
		this->yvel = yvel;
		this->size = size;
		this->mass = mass;
	}
	Particle(double x, double y, double xvel, double yvel, double mass, int size) {
		this->x = x;
		this->y = y;
		this->xvel = xvel;
		this->yvel = yvel;
		this->size = size;
		this->mass = mass;
	}

	void move() {
		for (int i = 0; i < timescale; i++) {
			x += xvel / (1.0 * timescale);
			y += yvel / (1.0 * timescale);
		}
	}

	void gravitate(Particle other) {
		double dx, dy, dist, angle, force;
		dx = other.x - x;
		dy = other.y - y;

		dist = hypot(dx, dy);
		angle = atan2(dy, dx);
		force = (G * mass * other.mass) / ((dist * dist));

		xvel += force * cos(angle) / (2.0 * mass) * (1.0 * timescale);
		yvel += force * sin(angle) / (2.0 * mass) * (1.0 * timescale);
		/*other.xvel += force * cos(angle) / (2.0 * other.mass);
		other.yvel += force * sin(angle) / (2.0 * other.mass);*/
	}

	/*static double x_momentum(Particle p){
		return p.mass * p.xvel;
	}

	static double y_momentum(Particle p) {
		return p.mass * p.yvel;
	}*/

	void collide(Particle other) {
		double dx, dy, dist;
		dx = x - other.x;
		dy = y - other.y;
		dist = hypot(dx, dy);

		// if particles placed are inside of each other, skip the placement of one
		if (dist == 0) {
			return;
		}
		if (dist < (other.size + size)) {
			double base_angle, self_angle, other_angle, self_vel, other_vel;

			base_angle = atan2(dy, dx);
			self_angle = atan2(yvel, xvel);
			other_angle = atan2(other.yvel, other.xvel);

			// find magnitude of velocity
			self_vel = sqrt(xvel * xvel + yvel * yvel);
			other_vel = sqrt(other.xvel * other.xvel + other.yvel * other.yvel);

			xvel = ((self_vel * cos(self_angle - base_angle) * (mass - other.mass) + 2 * other.mass * other_vel * cos(other_angle - base_angle)) \
				/ (mass + other.mass)) * cos(base_angle) + self_vel * sin(self_angle - base_angle) * cos(base_angle + M_PI / 2.0);

			yvel = ((self_vel * cos(self_angle - base_angle) * (mass - other.mass) + 2 * other.mass * other_vel * cos(other_angle - base_angle)) \
				/ (mass + other.mass)) * sin(base_angle) + self_vel * sin(self_angle - base_angle) * sin(base_angle + M_PI / 2.0);

			other.xvel = ((other_vel * cos(other_angle - base_angle) * (other.mass - mass) + 2 * mass * self_vel * cos(self_angle - base_angle)) \
				/ (mass + other.mass)) * cos(base_angle) + other_vel * sin(other_angle - base_angle) * cos(base_angle + M_PI / 2.0);

			other.yvel = ((other_vel * cos(other_angle - base_angle) * (other.mass - mass) + 2 * mass * self_vel * cos(self_angle - base_angle)) \
				/ (mass + other.mass)) * sin(base_angle) + other_vel * sin(other_angle - base_angle) * sin(base_angle + M_PI / 2.0);
		}
	}
};