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

#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <cstdint>
#include <memory>
#include "color.h"

namespace pocus {

class Texture {
public:
	virtual bool createBlank(uint32_t width, uint32_t height) = 0;
	virtual void setPixel(uint32_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) = 0;
	virtual void getPixel(uint32_t index, uint8_t* red, uint8_t* green, uint8_t* blue, uint8_t* alpha) = 0;
	virtual uint32_t getWidth() const = 0;
	virtual uint32_t getHeight() const = 0;
	virtual bool isReady() const = 0;
	virtual bool loadFromStream(const char* stream, uint32_t length) = 0;
	virtual void fill(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha = 255) = 0;
	virtual void paste(const Texture& texture, uint32_t fx, uint32_t fy, uint32_t tx, uint32_t ty) = 0;
	virtual void setColorKey(uint8_t red, uint8_t green, uint8_t blue) = 0;
	virtual std::unique_ptr<Texture> extract(uint32_t x, uint32_t y, uint32_t w, uint32_t h, const Color* colorKey = nullptr) = 0;
	virtual bool saveToFile(const std::string& filename) = 0;
	virtual void setOverlayColor(const Color& color) = 0;
	virtual void restoreColor() = 0;
};

}

#endif //_TEXTURE_H
