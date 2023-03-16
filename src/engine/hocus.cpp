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
	addState("stand_left", Animation::createFromFrame(extract(sprite.header.standFrame, LEFT)));
	addState("stand_right", Animation::createFromFrame(extract(sprite.header.standFrame, RIGHT)));
	
	// Jump frames
	addState("jump_left", Animation::createFromFrame(extract(sprite.header.jumpFrame, LEFT)));
	addState("jump_right", Animation::createFromFrame(extract(sprite.header.jumpFrame, RIGHT)));
	
	// Fall frames
	addState("fall_left", Animation::createFromFrame(extract(sprite.header.fallFrame, LEFT)));
	addState("fall_right", Animation::createFromFrame(extract(sprite.header.fallFrame, RIGHT)));
	
	// Walking frames
	Animation walkLeft, walkRight;
	walkLeft.setFps(15);
	walkRight.setFps(15);
	for (uint32_t i = sprite.header.walkFrameBegin; i < sprite.header.walkFrameEnd; i++) {
		walkLeft.addFrame(extract(i, LEFT));
		walkRight.addFrame(extract(i, RIGHT));
	}
	addState("walk_left", std::move(walkLeft));
	addState("walk_right", std::move(walkRight));
	
	// Shooting frames
	addState("shoot_left", Animation::createFromFrame(extract(sprite.header.shootDashFrameBegin, LEFT)));
	addState("shoot_right", Animation::createFromFrame(extract(sprite.header.shootDashFrameBegin, RIGHT)));
	addState("shoot_up_left", Animation::createFromFrame(extract(sprite.header.shootDashFrameEnd, LEFT)));
	addState("shoot_up_right", Animation::createFromFrame(extract(sprite.header.shootDashFrameEnd, RIGHT)));
	
	setCurrentState("stand_right");
	
	this->setRect(Rect(getRect().getPosition(), Size(sprite.header.width4, sprite.header.height)));
}

void Hocus::startMovement(const Direction_t& direction) {
	this->setDirection(direction);
	
	auto getVelocityByDirection = [](const Direction_t& direction) -> float {
		if (direction == LEFT) { return -1.0f; }
		else if (direction == RIGHT) { return 1.0f; }
		
		return .0f;
	};
	
	this->setVelocityX(getVelocityByDirection(direction));
	
	switch (this->getState()) {
		case FALL:
			this->setCurrentState("fall_" + Entity::getDirectionName(direction));
			break;
			
		case JUMP:
			this->setCurrentState("jump_" + Entity::getDirectionName(direction));
			break;
			
		default:
			this->state = WALK;
			this->setCurrentState("walk_" + Entity::getDirectionName(direction));
			break;
	}
}

void Hocus::stopMovement(const Direction_t& direction) {
	this->setDirection(direction);
	
	if (this->getState() != FALL && this->getState() != JUMP) {
		setCurrentState("stand_" + Entity::getDirectionName(direction));
	}
	
	this->setVelocityX(0.0f);
}

void Hocus::startFalling() {
	this->state = FALL;
	this->setVelocityY( 1.f);
	setCurrentState("fall_" + Entity::getDirectionName(this->getDirection()));
}

void Hocus::grounded() {
	this->setVelocityY( 0.f);
	
	if (this->getVelocity().getX() != 0.f) {
		this->state = WALK;
		setCurrentState("walk_" + Entity::getDirectionName(this->getDirection()));
	}
	else {
		this->state = STAND;
		setCurrentState("stand_" + Entity::getDirectionName(this->getDirection()));
	}
}

void Hocus::jump() {
	this->state = JUMP;
	this->setVelocityY(-2.5f);
	setCurrentState("jump_" + Entity::getDirectionName(this->getDirection()));
}

void Hocus::move(float dt) {
	Entity::move(dt);
	
	if (this->getState() == JUMP) {
		this->setVelocityY(this->getVelocity().getY() + .33f);
		
		if (this->getVelocity().getY() >= .0f) {
			this->setVelocityY(.0f);
			startFalling();
		}
	}
	else if (getState() == FALL && this->getVelocity().getY() < 2.5f) {
		this->setVelocityY(this->getVelocity().getY() + 0.33f);
		if (this->getVelocity().getY() > 2.5f) {
			this->setVelocityY(2.5f);
		}
	}
}