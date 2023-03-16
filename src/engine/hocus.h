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

#ifndef _HOCUS_H
#define _HOCUS_H

#include <unordered_map>
#include <string>
#include "entity.h"
#include "animation.h"
#include "data/asset/spriteset.h"

namespace pocus {

class Hocus : public Entity {
public:
	enum State_t { STAND, WALK, JUMP, FALL, SHOOT };
	
public:
	State_t getState() const;
	void setState(State_t state);
	void setSprite(const data::asset::Sprite& sprite, Texture& sheet);

	void startMovement(const Direction_t& direction);
	void stopMovement(const Direction_t& direction);
	void startFalling();
	void grounded();
	void jump();
	
	virtual void move(float dt) override;
	
private:
	State_t state { STAND };
	Tick tickHit;
	bool hitBlinking;
	
};

}

#endif //_HOCUS_H
