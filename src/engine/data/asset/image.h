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

#ifndef _IMAGE_H
#define _IMAGE_H

#include <cstdint>
#include <vector>
#include <memory>
#include "../../texture.h"
#include "asset.h"
#include "palette.h"

namespace pocus::data::asset {

class Image : public Asset {
public:
	enum { BLOCKS = 4 };
	
public:
	bool loadFromStream(const char* stream, uint32_t length) override;
	void release() override;
	
	std::unique_ptr<Texture> createTexture(const Palette& palette);
	
private:
	uint16_t width;
	uint16_t height;
	std::vector<uint8_t> blocks;
};

}

#endif //_IMAGE_H
