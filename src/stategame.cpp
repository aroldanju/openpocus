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
#include "stategame.h"
#include "engine/log.h"
#include "engine/data/asset/image.h"
#include "engine/data/asset/palette.h"
#include "definitions.h"
#include "version.h"
#include "engine/data/asset/font.h"
#include "engine/data/asset/level.h"

void StateGame::loadLevel(pocus::data::Data& data, uint8_t episode, uint8_t stage) {
	episode--;
	stage--;
	
	const uint32_t filesPerType = EPISODES * STAGES;
	const uint32_t playerCoordinatesOffset = 0;
	const uint32_t tileAnimationSettingsOffset = 1;
	const uint32_t enemyTriggersOffset = 8;
	const uint32_t fileIndex = (STAGES * episode) + stage;
	
	const uint32_t offsetPlayerCoordinates = DATFILE_LEVELS_START + (playerCoordinatesOffset * filesPerType) + (fileIndex);
	const uint32_t offsetTileAnimationSettings = DATFILE_LEVELS_START + (tileAnimationSettingsOffset * filesPerType) + (fileIndex);
	const uint32_t offsetEnemyTriggers = DATFILE_LEVELS_START + (enemyTriggersOffset * filesPerType) + (fileIndex);
	
	pocus::data::DataFile& playerCoordinatesFile = data.fetchFile(offsetPlayerCoordinates);
	pocus::data::DataFile& offsetTileAnimationSettingsFile = data.fetchFile(offsetTileAnimationSettings);
	pocus::data::DataFile& enemyTriggersFile = data.fetchFile(offsetEnemyTriggers);
	
	pocus::data::asset::PlayerCoordinates playerCoordinates;
	playerCoordinates.loadFromStream(playerCoordinatesFile.getContent(), playerCoordinatesFile.getLength());
	
	pocus::data::asset::TileAnimationSettings tileAnimationSettings;
	tileAnimationSettings.loadFromStream(offsetTileAnimationSettingsFile.getContent(), offsetTileAnimationSettingsFile.getLength());
	
	pocus::data::asset::EnemyTrigger enemyTrigger;
	enemyTrigger.loadFromStream(enemyTriggersFile.getContent(), enemyTriggersFile.getLength());
	
	
	/*
	std::cout << "Player coordinates = " << playerCoordinates.getX() << ", " << playerCoordinates.getY() << std::endl;
	std::cout << "Settings: " << (int)tileAnimationSettings.getEntries()[0].firstIndex << std::endl;
	for (int i = 0; i < pocus::data::asset::EnemyTrigger::ENEMIES; i++) {
		std::cout << "Enemy: type = " << enemyTrigger.getEntries()[i].type[0] << ", offset = " << enemyTrigger.getEntries()[i].offsets[0]
				  << std::endl;
	}
	*/
}

void StateGame::onCreate(pocus::data::Data& data) {
	loadLevel(data, 1, 1);
	
	pocus::data::asset::Image image;
	pocus::data::asset::Palette palette {};
	pocus::data::asset::Font font;
	
	pocus::data::DataFile& paletteFile = data.fetchFile(DATFILE_PALETTE_GAME);
	pocus::data::DataFile& hudFile = data.fetchFile(DATFILE_IMAGE_HUD);
	pocus::data::DataFile& fontFile = data.fetchFile(DATFILE_FONT_MAIN);
	
	palette.loadFromStream(paletteFile.getContent(), paletteFile.getLength());
	image.loadFromStream(hudFile.getContent(), hudFile.getLength());
	font.loadFromStream(fontFile.getContent(), fontFile.getLength());
	
	this->textureHud = image.createTexture(palette);
	//this->label = font.writeShadow("This is a label using Hocus Pocus font.", palette, 8);
	//this->label = font.writeShadow("This is a label using Hocus Pocus font.", palette, 8);
	this->label = font.writeGradient("This is a label using Hocus Pocus font.", palette, 8);
}

void StateGame::onDetach() {
	LOGI << "StateGame: onDetach";
}

void StateGame::onAttach() {
	LOGI << "StateGame: onAttach";
}

void StateGame::release() {
	LOGI << "StateGame: release";
}

void StateGame::handleEvents(pocus::EventHandler &eventHandler) {

}

void StateGame::render(pocus::Renderer &renderer) {
	renderer.drawTexture(*this->textureHud, 0, SCREEN_HEIGHT - this->textureHud->getHeight());
	renderer.drawTexture(*this->label, 0, 0);
}

void StateGame::update(float dt) {

}