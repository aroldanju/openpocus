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

#ifndef LEVEL_H
#define LEVEL_H

#include <cstdint>
#include "asset.h"

namespace pocus::data::asset {

class PlayerCoordinates : public Asset {
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] uint16_t getX() const;
	void setX(uint16_t x);
	[[nodiscard]] uint16_t getY() const;
	void setY(uint16_t y);
	[[nodiscard]] uint16_t getShootDelay() const;
	void setShootDelay(uint16_t shootDelay);

private:
	uint16_t unknown { 0 };
	uint16_t x { 0 };
	uint16_t y { 0 };
	uint16_t shootDelay { 0 };
};

class EnemyTrigger : public Asset {
public:
	struct Entry {
		uint16_t type[8];
		uint16_t offsets[8];
	};
	
	enum { ENEMIES = 250 };
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	const Entry *getEntries() const;

private:
	Entry entries[ENEMIES];
};

}

#endif // LEVEL_H
