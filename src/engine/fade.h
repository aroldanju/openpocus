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

#ifndef FADE_H
#define FADE_H

#include "definitions.h"
#include "renderer.h"
#include "color.h"
#include <chrono>
#include <functional>

namespace pocus {

class Fade {
public:
	enum Fade_t {
		FADE_IN, FADE_OUT
	};
	
public:
	Fade() = default;
	virtual ~Fade() = default;
	
	void start(const Fade_t& type);
	
	void stop();
	
	void update(float dt);
	
	void render(Renderer &renderer);
	
	void setSpeed(float speed);
	
	[[nodiscard]] float getSpeed() const;
	
	void setOnFinished(std::function<void()> onFinished);
	
	bool isRunning() const;
	
private:
	Tick tickStart;
	Tick tickLastUpdate;
	Color color { color::black };
	float alpha { 0.0f };
	float speed { 3.0f };
	bool running { false };
	Fade_t type { FADE_IN };
	
	std::function<void()> onFinished { nullptr };
	
};

}

#endif //FADE_H
