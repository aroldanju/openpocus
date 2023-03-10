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

#ifndef FONT_H
#define FONT_H

#include <cstdint>
#include <vector>
#include <unordered_map>
#include "asset.h"
#include "palette.h"
#include "../../texture.h"

namespace pocus::data::asset {

class FontGlyph {
public:
	FontGlyph(const std::vector<bool>& data, char character, uint8_t width);
	
	[[nodiscard]] const Texture& getTexture() const;
	
	[[nodiscard]] uint8_t getWidth() const;
	
private:
	uint8_t width { 8 };
	char character { ' ' };
	std::unique_ptr<Texture> texture { nullptr };
};

class Font : public Asset {
public:
	enum { GLYPH_SIZE = 8, SPACE_WIDTH = 4 };
	
public:
	bool loadFromStream(const char* stream, uint32_t length) override;
	void release() override;
	
	std::unique_ptr<Texture> write(const std::string& text, const Palette& palette, uint8_t color);
	std::unique_ptr<Texture> writeShadow(const std::string& text, const Palette& palette, uint8_t color);
	std::unique_ptr<Texture> writeGradient(const std::string& text, const Palette& palette, uint8_t startColor);
	std::unique_ptr<Texture> writeGradient(const std::string& text, const Palette& palette, uint8_t startColor, uint8_t capitalLetter);
	std::unique_ptr<Texture> writeGradientShadow(const std::string& text, const Palette& palette, uint8_t startColor);
	
	uint32_t calculateWidth(const std::string& text);
	
private:
	std::unordered_map<char, FontGlyph> glyphs;
	
	std::unique_ptr<Texture> internalWrite(const std::string& text);
};

}

#endif // FONT_H
