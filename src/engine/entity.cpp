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

void Entity::render(Renderer &renderer) {
	if (this->currentState) {
		this->currentState->render(renderer, this->rect.getPosition());
	}
}

void Entity::update(float dt) {
	if (this->currentState) {
		this->currentState->update(dt);
	}
}

const Entity::Direction_t& Entity::getDirection() const {
	return direction;
}

void Entity::setDirection(Entity::Direction_t direction) {
	Entity::direction = direction;
}
