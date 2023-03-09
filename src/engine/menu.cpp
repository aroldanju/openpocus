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

#include <iostream>
#include "menu.h"
#include "../definitions.h"

using namespace pocus;

void Menu::setFont(data::asset::Font font) {
	this->font = std::move(font);
}

void Menu::setPalette(data::asset::Palette& palette) {
	this->palette = palette;
}

void Menu::addOption(const std::string& option) {
	this->options.push_back(option);
	this->labels.push_back(this->font.writeGradient(option, this->palette, this->textColor, this->capitalLetterColor));
}

void Menu::addSpace() {
	this->options.emplace_back("");
}

const std::vector<std::string>& Menu::getOptions() const {
	return this->options;
}

void Menu::render(Renderer &renderer) {
	uint32_t label = 0;
	uint32_t yOffset = this->y;
	for (int i = 0; i < this->options.size(); i++) {
		uint32_t offset = this->lineSpacing;
		if (!this->options[i].empty()) {
			renderer.drawTexture(*this->labels[label], this->x, (int)yOffset);
			label++;
		}
		else {
			offset = Menu::SPACE_HEIGHT;
		}
		
		yOffset += offset;
	}
	
	// Bottom text
	if (this->bottomLabel) {
		renderer.drawTexture(*this->bottomLabel, SCREEN_WIDTH / 2 - this->font.calculateWidth(this->bottomText) / 2, Menu::BOTTOM_TEXT_Y);
	}
}

void Menu::setPosition(uint32_t x, uint32_t y) {
	this->x = x;
	this->y = y;
}

void Menu::setLineSpacing(uint32_t spacing) {
	this->lineSpacing = spacing;
}

void Menu::setTextColor(uint8_t color) {
	this->textColor = color;
}

void Menu::setCapitalLetterColor(uint8_t color) {
	this->capitalLetterColor = color;
}

void Menu::setBottomTextColor(uint8_t color) {
	this->bottomTextColor = color;
}

void Menu::setBottomText(const std::string& text) {
	this->bottomText = text;
	this->bottomLabel = this->font.writeGradient(text, this->palette, this->bottomTextColor);
}
