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

#ifndef STATEGAME_H
#define STATEGAME_H

#include <memory>
#include "engine/game.h"
#include "engine/texture.h"
#include "engine/state.h"
#include "engine/map.h"
#include "engine/sound.h"

class StateGame : public pocus::State {
public:
	void onCreate(pocus::data::DataManager& dataManager) override;
	void onDetach() override;
	void onAttach() override;
	void release() override;
	void handleEvents(pocus::EventHandler &eventHandler) override;
	void render(pocus::Renderer &renderer) override;
	void update(float dt) override;
	
private:
	pocus::Game game;
	
	void loadSprites(pocus::data::Data& data);
	void loadLevel(pocus::data::Data& data, pocus::data::Data& executable, uint8_t episode, uint8_t stage);
	void createHud(pocus::data::Data& data);
	void createGame(pocus::data::Data& data);
	void loadItems(pocus::data::Data& executable);
	
	std::unique_ptr<pocus::Texture> loadTexture(pocus::data::Data& data, uint32_t paletteFileIndex, uint32_t imageFileIndex);
	std::unique_ptr<pocus::Texture> loadTexture(pocus::data::Data& data, const pocus::data::asset::Palette& palette, uint32_t imageFileIndex);
};

#endif //STATEGAME_H
