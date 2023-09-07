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

#include <iostream>
#include "projectile.h"

using namespace pocus;

void Projectile::setSprite(const data::asset::Sprite& sprite, Texture& sheet) {
	
	const Color colorKey = color::pink;
	const uint32_t width = sprite.header.width4;
	const uint32_t height = sprite.header.height;
	
	// Extract a frame from sheet given a frame index, width, height and direction
	auto extract = [colorKey, &sheet, width, height](uint8_t frame, Direction_t direction) -> std::unique_ptr<Texture> {
		uint32_t y = 0;
		if (direction == LEFT) {
			y = height;
		}
		
		return sheet.extract(frame * width, y, width, height, &colorKey);
	};
	
	addState("right", Animation::createFromFrame(extract(sprite.header.projectileFrame, RIGHT)));
	addState("left", Animation::createFromFrame(extract(sprite.header.projectileFrame, LEFT)));
	addState("up_right", Animation::createFromFrame(extract(sprite.header.projectileFrame + 1, RIGHT)));
	addState("up_left", Animation::createFromFrame(extract(sprite.header.projectileFrame + 1, LEFT)));
	
	setCurrentState("right");
}
