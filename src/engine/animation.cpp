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

#include "animation.h"

using namespace pocus;

void Animation::addFrame(std::unique_ptr<Texture> texture) {
	this->frames.push_back(std::move(texture));
}

void Animation::update(float dt) {
	if (getElapsedTime(this->lastUpdateTick) >= 1000 / this->fps) {
		this->lastUpdateTick = getNow();
		this->currentFrame++;
		if (this->currentFrame >= this->frames.size()) {
			this->currentFrame = 0;
		}
	}
}

void Animation::render(Renderer& renderer, int x, int y) {
	if (this->frames.empty()) {
		return;
	}
	
	renderer.drawTexture(*this->frames[this->currentFrame], x, y);
}

uint32_t Animation::getFps() const {
	return fps;
}

void Animation::setFps(uint32_t fps) {
	Animation::fps = fps;
}

Animation Animation::createFromTexture(Texture& texture, uint32_t columns, uint32_t rows) {
	Animation animation;
	const uint32_t frameWidth = texture.getWidth() / columns;
	const uint32_t frameHeight = texture.getHeight() / rows;
	
	for (int i = 0; i < columns * rows; i++) {
		const uint32_t x = i % columns;
		const uint32_t y = i / columns;
		
		auto frame = texture.extract(x * frameWidth, y * frameHeight, frameWidth, frameHeight);
		frame->setColorKey(0, 0, 0);
		animation.addFrame(std::move(frame));
	}
	
	return std::move(animation);
}

uint32_t Animation::getWidth() const {
	if (this->frames.empty()) {
		return 0;
	}
	
	return this->frames[this->currentFrame]->getWidth();
}

uint32_t Animation::getHeight() const {
	if (this->frames.empty()) {
		return 0;
	}
	
	return this->frames[this->currentFrame]->getHeight();
}
