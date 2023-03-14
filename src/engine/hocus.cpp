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

#include "hocus.h"

using namespace pocus;

Hocus::State_t Hocus::getState() const {
	return state;
}

void Hocus::setState(Hocus::State_t state) {
	Hocus::state = state;
}

void Hocus::setSprite(const data::asset::Sprite& sprite, Texture& sheet) {
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
	
	// Stand frames
	Animation standLeft;
	standLeft.addFrame(extract(sprite.header.standFrame, LEFT));
	addState("stand_left", std::move(standLeft));
	
	Animation standRight;
	standRight.addFrame(extract(sprite.header.standFrame, RIGHT));
	addState("stand_right", std::move(standRight));
	
	// Jump frames
	Animation jumpLeft;
	jumpLeft.addFrame(extract(sprite.header.jumpFrame, LEFT));
	addState("jump_left", std::move(jumpLeft));
	
	Animation jumpRight;
	jumpRight.addFrame(extract(sprite.header.jumpFrame, RIGHT));
	addState("jump_right", std::move(jumpRight));
	
	// Fall frames
	Animation fallLeft;
	fallLeft.addFrame(extract(sprite.header.fallFrame, LEFT));
	addState("fall_left", std::move(fallLeft));
	
	Animation fallRight;
	fallRight.addFrame(extract(sprite.header.fallFrame, RIGHT));
	addState("fall_right", std::move(fallRight));
	
	// Walking frames
	Animation walkLeft, walkRight;
	for (uint32_t i = sprite.header.walkFrameBegin; i < sprite.header.walkFrameEnd; i++) {
		walkLeft.addFrame(extract(i, LEFT));
		walkRight.addFrame(extract(i, RIGHT));
	}
	addState("walk_left", std::move(walkLeft));
	addState("walk_right", std::move(walkRight));
	
	// Shooting frames
	Animation shootLeft, shootRight, shootUpLeft, shootUpRight;
	shootLeft.addFrame(extract(sprite.header.shootDashFrameBegin, LEFT));
	shootRight.addFrame(extract(sprite.header.shootDashFrameBegin, RIGHT));
	shootUpLeft.addFrame(extract(sprite.header.shootDashFrameEnd, LEFT));
	shootUpRight.addFrame(extract(sprite.header.shootDashFrameEnd, RIGHT));
	
	addState("shoot_left", std::move(shootLeft));
	addState("shoot_right", std::move(shootRight));
	addState("shoot_up_left", std::move(shootUpLeft));
	addState("shoot_up_right", std::move(shootUpRight));
	
	setCurrentState("stand_right");
}
