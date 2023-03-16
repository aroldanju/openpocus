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
	
	enum {
		TILES = 240,
		PERMANENT = 1,
		RANDOM = 2
	};
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getEntries() const;
	
	uint8_t getBackgroundTile() const;
	void setBackgroundTile(uint8_t backgroundTile);
	uint8_t getSwitchDownTile() const;
	void setSwitchDownTile(uint8_t switchDownTile);
	uint8_t getSwitchUpTile() const;
	void setSwitchUpTile(uint8_t switchUpTile);
	uint8_t getShootableTile() const;
	void setShootableTile(uint8_t shootableTile);

private:
	uint8_t backgroundTile { 0 };
	uint8_t switchDownTile { 0 };
	uint8_t switchUpTile { 0 };
	uint8_t shootableTile { 0 };
	
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

class ToggleCoordinates : public Asset {
public:
	struct Entry {
		uint16_t requiredKey;
		uint16_t requiredTile;
		uint16_t upperLeftX;
		uint16_t upperLeftY;
		uint16_t lowerRightX;
		uint16_t lowerRightY;
	};
	
	enum { TOGGLES = 25 };

public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getToggles() const;

private:
	Entry toggles[TOGGLES];
};

class TileProperties : public Asset {
public:
	struct Entry {
		uint16_t spriteSet;
		uint16_t health;
		uint16_t projectileHSpeed;
		uint16_t projectileVSpeed;
		uint16_t projectileXOffset;
		uint16_t targetPlayer;
		uint16_t unk2;
		uint16_t shootProjectiles;
		uint16_t unk3;
		uint16_t wobblyProjectiles;
		uint16_t unk4;
		uint16_t behaviour;
	};
	
	enum { PROPERTIES = 10 };

public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getProperties() const;

private:
	Entry properties[PROPERTIES];
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
	
	[[nodiscard]] const Entry *getEntries() const;

private:
	Entry entries[ENEMIES];
};

class MapLayer : public Asset {
public:
	enum { WIDTH = 240, HEIGHT = 60, TILE_EMPTY = 0xff };
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;

	[[nodiscard]] uint8_t* getData() const;
	
private:
	uint8_t data[HEIGHT][WIDTH];
};

class EventLayer : public Asset {
public:
	enum { WIDTH = 240, HEIGHT = 60 };
	
	enum Event_t {
		RUBY = 0x00,
		DIAMOND = 0x01,
		GLOBET = 0x02,
		CROWN = 0x03,
		HEAL_POTION = 0x04,
		CRYSTAL = 0x05,
		SPIKES = 0x06,
		ZAPPER = 0x07,
		INVISIBILITY = 0x08,
		GOLDEN_POTION = 0x09,
		WHITE_POTION = 0x0a,
		UNUSED1 = 0x0b,
		SILVER_KEY = 0x0c,
		GOLD_KEY = 0x0d,
		LAVA = 0x0e,
		WIZARD = 0x0f,
		GREY_POTION = 0x10,
		EMPTY = 30000
	};
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] uint16_t* getData() const;
	
private:
	uint16_t data[HEIGHT][WIDTH];
};

}

#endif // LEVEL_H
