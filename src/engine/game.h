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

#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "hud.h"

namespace pocus {

class Game {
public:
	enum { PLAYER_MAX_HEALTH = 100 };
	enum { DEFAULT_TEXT_COLOR = 104 };
	
public:
	Map& getMap();
	Player& getPlayer();
	Hud& getHud();
	data::asset::Palette& getPalette();
	data::asset::Font& getFont();
	Point& getOffset();
	
	void setTextColor(uint8_t color);
	
	void start();
	void render(Renderer& renderer);
	void update(float dt);
	
	uint32_t getElapsedTime();
	
	void addScore(uint32_t score);
	void removeHealth(uint8_t health);
	void addHealth(uint8_t health);
	void addSilverKey();
	void removeSilverKey();
	void addGoldenKey();
	void removeGoldenKey();
	void togglePause();
	
private:
	data::asset::Font font;
	data::asset::Palette palette;
	uint8_t textColor { DEFAULT_TEXT_COLOR };
	Point offset;
	Map map;
	Player player;
	Hud hud;
	Tick tickStart;
	bool paused { false };
	std::unique_ptr<Texture> labelPaused;
};

}

#endif // GAME_H
