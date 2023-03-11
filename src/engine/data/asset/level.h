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

class TileAnimationSettings : public Asset {
public:
	struct Entry {
		uint8_t firstIndex;
		uint8_t lastIndex;
		uint8_t animationType;
	};
	
	enum { TILES = 240 };
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getEntries() const;
	
private:
	uint8_t backgroundTile;
	uint8_t switchDownTile;
	uint8_t switchUpTile;
	uint8_t shootableTile;
	
	Entry entries[TILES];
};

class Messages : public Asset {
public:
	enum { MESSAGES = 10, LINES = 10, MESSAGE_LENGTH = 50 };
	
	struct Entry {
		uint16_t x;
		uint16_t y;
		uint8_t lines[LINES][MESSAGE_LENGTH];
	};
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getMessages() const;

private:
	Entry messages[MESSAGES];
	
};

class Teleports : public Asset {
public:
	struct Entry {
		uint16_t startOffset;
		uint16_t endOffset;
	};
	
	enum { TELEPORTS = 10 };
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getTeleports() const;

private:
	Entry teleports[TELEPORTS];
};

class SwitchCoordinates : public Asset {
public:
	struct Entry {
		uint16_t type;
		uint16_t offsets[4];
		uint8_t desiredTile[4];
		uint16_t upperLeftX;
		uint16_t upperLeftY;
		uint16_t lowerRightX;
		uint16_t lowerRightY;
	};
	
	enum { SWITCHES = 23 };
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getSwitches() const;
	
private:
	Entry switchCoordinates[SWITCHES];
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
