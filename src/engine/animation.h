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

#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <memory>
#include "texture.h"
#include "definitions.h"
#include "renderer.h"

namespace pocus {

class Animation {
public:
	void addFrame(std::unique_ptr<Texture> texture);
	
	void update(float dt);
	void render(Renderer& renderer, const Point& point);
	
	[[nodiscard]] uint32_t getFps() const;
	
	void setFps(uint32_t fps);
	
	static Animation createFromTexture(Texture& texture, uint32_t columns, uint32_t rows);
	void createFrom(const Animation& animation);
	
	[[nodiscard]] uint32_t getWidth() const;
	[[nodiscard]] uint32_t getHeight() const;
	
	[[nodiscard]] bool isRandomStart() const;
	void setRandomStart(bool randomStart);
	
	void setCurrentFrame(uint32_t frame);
	[[nodiscard]] uint32_t getFrameCount() const;
	
	//Animation& operator=(const Animation& src);

private:
	uint32_t fps { 5 };
	std::vector<std::unique_ptr<Texture>> frames;
	uint32_t currentFrame { 0 };
	Tick lastUpdateTick;
	bool randomStart { false };
	bool playing { false };
};

}

#endif // ANIMATION_H
