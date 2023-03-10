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

#ifndef PARTICLES_H
#define PARTICLES_H

#include <cstdint>
#include <vector>
#include "data/asset/palette.h"
#include "definitions.h"
#include "color.h"
#include "renderer.h"

namespace pocus {

class Particle {
public:
	friend class Particles;
	
public:
	Particle(float x, float y, float angle, float speed, const Color& color);
	
	[[nodiscard]] float getX() const;
	void setX(float x);
	[[nodiscard]] float getY() const;
	void setY(float y);

private:
	float x, y;
	Color color;
	float speed;
	float angle;
	Tick tickCreation;
};

class Particles {
public:
	void update(float dt);
	
	void createStars(data::asset::Palette& palette, uint32_t width, uint32_t height, uint32_t amount = 50);
	
	void render(Renderer& renderer);
	
private:
	data::asset::Palette palette;
	float x, y;
	std::vector<Particle> particles;
	std::pair<uint32_t, uint32_t> bounds;
};

}

#endif // PARTICLES_H
