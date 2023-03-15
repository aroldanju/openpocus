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

#ifndef ENTITY_H
#define ENTITY_H

#include <unordered_map>
#include <string>
#include "rect.h"
#include "animation.h"

namespace pocus {

class Entity {
public:
	enum Direction_t { LEFT, RIGHT };
	
public:
	[[nodiscard]] const Rect& getRect() const;
	void setRect(const Rect& rect);
	void addState(const std::string& state, Animation animation);
	void setCurrentState(const std::string& state);
	[[nodiscard]] const Direction_t& getDirection() const;
	void setDirection(Direction_t direction);
	
	void render(Renderer& renderer, const Point& offset);
	void update();
	void move(float dt);
	
	Point getTilePosition();
	
	const Point &getVelocity() const;
	
	void setVelocity(const Point &velocity);
	
	float getSpeed() const;
	
	void setSpeed(float speed);
	
	void setPosition(const Point& point);

private:
	Rect rect {};
	std::unordered_map<std::string, Animation> states;
	std::string currentStateId;
	Animation* currentState { nullptr };
	Direction_t direction { RIGHT };
	Point velocity { .0f, .0f };
	float speed { 3.0f };
};

}

#endif // ENTITY_H
