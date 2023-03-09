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

#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>
#include <memory>
#include "texture.h"
#include "renderer.h"
#include "data/asset/font.h"

namespace pocus {

class Menu {
public:
	enum { SPACE_HEIGHT = 4, BOTTOM_TEXT_Y = 188 };
	
public:
	void addOption(const std::string& option);
	void addSpace();
	[[nodiscard]] const std::vector<std::string>& getOptions() const;
	void setFont(data::asset::Font font);
	void setPalette(data::asset::Palette& palette);
	void render(Renderer& renderer);
	void setPosition(uint32_t x, uint32_t y);
	void setLineSpacing(uint32_t spacing);
	void setTextColor(uint8_t color);
	void setCapitalLetterColor(uint8_t color);
	void setBottomText(const std::string& text);
	void setBottomTextColor(uint8_t color);
	
private:
	data::asset::Font font;
	data::asset::Palette palette;
	uint32_t x { 0 };
	uint32_t y { 0 };
	uint32_t lineSpacing { 10 };
	std::vector<std::string> options;
	std::vector<std::unique_ptr<Texture>> labels;
	uint8_t textColor, capitalLetterColor;
	uint8_t bottomTextColor;
	std::string bottomText;
	std::unique_ptr<Texture> bottomLabel { nullptr };
	
};

}

#endif // MENU_H
