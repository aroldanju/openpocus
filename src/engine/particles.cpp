/*
 * Copyright (C) 2023, A. Roldán. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <complex>
#include <iostream>
#include "particles.h"

using namespace pocus;

Particle::Particle(float x, float y, float angle, float speed, const Color& color):
	x(x), y(y),
	angle(angle),
	speed(speed),
	color(color),
	tickCreation(getNow())
{
}

float Particle::getX() const {
	return x;
}

void Particle::setX(float x) {
	Particle::x = x;
}

float Particle::getY() const {
	return y;
}

void Particle::setY(float y) {
	Particle::y = y;
}

void Particles::createStars(data::asset::Palette& palette, uint32_t width, uint32_t height, uint32_t amount) {
	this->x = width / 2.0f;
	this->y = height / 2.0f;
	this->palette = palette;
	this->bounds = std::make_pair(width, height);
	
	const data::asset::PaletteColor& color = this->palette.colors[127];
	
	for (uint32_t i = 0; i < amount; i++) {
		this->particles.emplace_back(x, y, (float)(rand() % 314) / 10.0f, .2f + ((float)(rand() % 100) / 100.f),
									 (Color){ color.r, color.g, color.b, 0 });
	}
}

void Particles::render(Renderer &renderer) {
	for (auto& particle : this->particles) {
		renderer.drawPoint((int)particle.x, (int)particle.y, particle.color);
	}
}

void Particles::update(float dt) {
	
	for (auto& particle : this->particles) {
		particle.x += std::cos(particle.angle) * (particle.speed * dt);
		particle.y += std::sin(particle.angle) * (particle.speed * dt);
		
		if ((int)particle.x >= this->bounds.first || particle.x < 0 || (int)particle.y >= this->bounds.second || particle.y < 0) {
			particle.color.alpha = 0;
			particle.x = this->x;
			particle.y = this->y;
			particle.angle = (float)(rand() % 314) / 10.0f;
			particle.tickCreation = getNow();
		}
		else {
			uint32_t alpha = particle.color.alpha + (uint32_t)(2.5f * dt);
			if (alpha > 255) {
				alpha = 255;
			}
			
			particle.color.alpha = alpha;
		}
	}
}
