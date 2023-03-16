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

#ifndef SPRITESET_H
#define SPRITESET_H

#include <cstdint>
#include <vector>
#include <memory>
#include "asset.h"
#include "../../texture.h"
#include "palette.h"

namespace pocus::data::asset {

class Sprite {
public:
	enum { ROWS = 2, COLUMNS = 15 };
	
public:
	struct Header {
		uint32_t offset;
		uint8_t name[22];
		uint16_t width4;
		uint16_t height;
		uint16_t standFrame;
		uint16_t standFrame2;
		uint16_t walkFrameBegin;
		uint16_t walkFrameEnd;
		uint16_t jumpFrame;
		uint16_t fallFrame;
		uint16_t shootDashFrameBegin;
		uint16_t shootDashFrameEnd;
		uint16_t projectileWidth4;
		uint16_t projectileHeight;
		uint16_t projectileY;
		uint16_t projectileFrame;
		uint16_t projectileUnknown;
		uint16_t pixelsOffset;
		uint16_t pixelsSize;
		uint16_t layoutStartE[20];
		uint16_t layoutStartW[20];
		uint16_t pixelStartsE[20];
		uint16_t pixelStartsW[20];
	};
	
	std::unique_ptr<Texture> createAsTexture(const Palette& palette);
	
public:
	Header header;
	const char* data;
};

class SpriteSet : public Asset {
public:
	bool loadFromStream(const char* stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] Sprite& getSprite(uint32_t index);
	[[nodiscard]] uint32_t getSpriteCount() const;
	
private:
	std::vector<Sprite> sprites;
	
	Sprite loadSprite(const char *buffer);
};

}

#endif // SPRITESET_H
