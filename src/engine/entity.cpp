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
#include "entity.h"

using namespace pocus;

const Rect& Entity::getRect() const {
	return this->rect;
}

void Entity::setRect(const Rect& rect) {
	this->rect = rect;
}

void Entity::addState(const std::string& state, Animation animation) {
	this->states.insert(std::make_pair(state, std::move(animation)));
}

void Entity::setCurrentState(const std::string& state) {
	this->currentStateId = state;
	this->currentState = &this->states.find(state)->second;
}

void Entity::render(Renderer &renderer, const Point& offset) {
	Point position = Point(
		this->rect.getPosition().getX() - offset.getX(),
		this->rect.getPosition().getY() - offset.getY()
	);
	
	if (this->currentState) {
		this->currentState->render(renderer, position);
	}
	
	renderer.drawRect(Rect(position, this->rect.getSize()), color::redAlpha);
}

void Entity::update() {
	if (this->currentState) {
		this->currentState->update(0.f);
	}
}

void Entity::move(float dt) {
	this->rect.setPosition(
		Point(
			this->rect.getPosition().getX() + (this->velocity.getX() * (float)this->speed * dt),
			this->rect.getPosition().getY() + (this->velocity.getY() * (float)this->speed * dt)
		)
	);
}

const Entity::Direction_t& Entity::getDirection() const {
	return direction;
}

void Entity::setDirection(Entity::Direction_t direction) {
	Entity::direction = direction;
}

Point Entity::getTilePosition() {
	return {
		this->rect.getPosition().getX() / TILE_SIZE,
		this->rect.getPosition().getY() / TILE_SIZE
	};
}

const Point &Entity::getVelocity() const {
	return velocity;
}

void Entity::setVelocity(const Point &velocity) {
	Entity::velocity = velocity;
}

float Entity::getSpeed() const {
	return speed;
}

void Entity::setSpeed(float speed) {
	Entity::speed = speed;
}

void Entity::setPosition(const Point& point) {
	this->rect.setPosition(point);
}