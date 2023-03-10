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

#include "level.h"
#include <cstring>

using namespace pocus::data::asset;

// Player coordinates ---------------------------------------------------------------------

bool PlayerCoordinates::loadFromStream(const char *stream, uint32_t length) {
	this->unknown = *(uint16_t*)(stream);
	stream += sizeof(uint16_t);
	
	this->x = *(uint16_t*)(stream);
	stream += sizeof(uint16_t);
	
	this->y = *(uint16_t*)(stream);
	stream += sizeof(uint16_t);
	
	this->shootDelay = *(uint16_t*)(stream);
	
	return true;
}

void PlayerCoordinates::release() {

}

uint16_t PlayerCoordinates::getX() const {
	return x;
}

void PlayerCoordinates::setX(uint16_t x) {
	PlayerCoordinates::x = x;
}

uint16_t PlayerCoordinates::getY() const {
	return y;
}

void PlayerCoordinates::setY(uint16_t y) {
	PlayerCoordinates::y = y;
}

uint16_t PlayerCoordinates::getShootDelay() const {
	return shootDelay;
}

void PlayerCoordinates::setShootDelay(uint16_t shootDelay) {
	PlayerCoordinates::shootDelay = shootDelay;
}

// Enemy trigger ---------------------------------------------------------------------

bool EnemyTrigger::loadFromStream(const char *stream, uint32_t length) {
	for (auto & entry : this->entries) {
		memcpy(entry.type, stream, sizeof(uint16_t) * 8);
		stream += sizeof(uint16_t) * 8;
		
		memcpy(entry.offsets, stream, sizeof(uint16_t) * 8);
		stream += sizeof(uint16_t) * 8;
	}
	
	return true;
}

void EnemyTrigger::release() {

}

const EnemyTrigger::Entry *EnemyTrigger::getEntries() const {
	return entries;
}
