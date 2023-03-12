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
#include "engine/data/asset/pcx.h"
#include "engine/data/asset/midi.h"

void StateGame::loadLevel(pocus::data::Data& data, uint8_t episode, uint8_t stage) {
	episode--;
	stage--;
	
	const uint32_t filesPerType = EPISODES * STAGES;
	const uint32_t playerCoordinatesOffset = 0;
	const uint32_t tileAnimationSettingsOffset = 1;
	const uint32_t messagesOffset = 2;
	const uint32_t teleportsOffset = 3;
	const uint32_t switchesOffset = 4;
	const uint32_t toggleInsertsOffset = 5;
	const uint32_t toggleKeyHolesOffset = 6;
	const uint32_t tilePropertiesOffset = 7;
	const uint32_t enemyTriggersOffset = 8;
	const uint32_t backgroundLayerOffset = 9;
	const uint32_t mapLayerOffset = 10;
	const uint32_t additionalLayerOffset = 11;
	const uint32_t eventLayerOffset = 12;
	const uint32_t fileIndex = (STAGES * episode) + stage;
	
	const uint32_t offsetPlayerCoordinates = DATFILE_LEVELS_START + (playerCoordinatesOffset * filesPerType) + (fileIndex);
	const uint32_t offsetTileAnimationSettings = DATFILE_LEVELS_START + (tileAnimationSettingsOffset * filesPerType) + (fileIndex);
	const uint32_t offsetMessages = DATFILE_LEVELS_START + (messagesOffset * filesPerType) + (fileIndex);
	const uint32_t offsetTeleports = DATFILE_LEVELS_START + (teleportsOffset * filesPerType) + (fileIndex);
	const uint32_t offsetSwitches = DATFILE_LEVELS_START + (switchesOffset * filesPerType) + (fileIndex);
	const uint32_t offsetInserts = DATFILE_LEVELS_START + (toggleInsertsOffset * filesPerType) + (fileIndex);
	const uint32_t offsetKeyHoles = DATFILE_LEVELS_START + (toggleKeyHolesOffset * filesPerType) + (fileIndex);
	const uint32_t offsetTileProperties = DATFILE_LEVELS_START + (tilePropertiesOffset * filesPerType) + (fileIndex);
	const uint32_t offsetEnemyTriggers = DATFILE_LEVELS_START + (enemyTriggersOffset * filesPerType) + (fileIndex);
	const uint32_t offsetBackgroundLayer = DATFILE_LEVELS_START + (backgroundLayerOffset * filesPerType) + (fileIndex);
	const uint32_t offsetMapLayer = DATFILE_LEVELS_START + (mapLayerOffset * filesPerType) + (fileIndex);
	const uint32_t offsetAdditionalLayer = DATFILE_LEVELS_START + (additionalLayerOffset * filesPerType) + (fileIndex);
	const uint32_t offsetEventLayer = DATFILE_LEVELS_START + (eventLayerOffset * filesPerType) + (fileIndex);
	
	pocus::data::DataFile& playerCoordinatesFile = data.fetchFile(offsetPlayerCoordinates);
	pocus::data::DataFile& tileAnimationSettingsFile = data.fetchFile(offsetTileAnimationSettings);
	pocus::data::DataFile& messagesFile = data.fetchFile(offsetMessages);
	pocus::data::DataFile& teleportsFile = data.fetchFile(offsetTeleports);
	pocus::data::DataFile& switchesFile = data.fetchFile(offsetSwitches);
	pocus::data::DataFile& insertsFile = data.fetchFile(offsetInserts);
	pocus::data::DataFile& keyHolesFile = data.fetchFile(offsetKeyHoles);
	pocus::data::DataFile& tilePropertiesFile = data.fetchFile(offsetTileProperties);
	pocus::data::DataFile& enemyTriggersFile = data.fetchFile(offsetEnemyTriggers);
	pocus::data::DataFile& backgroundLayerFile = data.fetchFile(offsetBackgroundLayer);
	pocus::data::DataFile& mapLayerFile = data.fetchFile(offsetMapLayer);
	pocus::data::DataFile& additionalLayerFile = data.fetchFile(offsetAdditionalLayer);
	pocus::data::DataFile& eventLayerFile = data.fetchFile(offsetEventLayer);
	
	this->map.getPlayerCoordinates().loadFromStream(playerCoordinatesFile.getContent(), playerCoordinatesFile.getLength());
	this->map.getTileAnimationSettings().loadFromStream(tileAnimationSettingsFile.getContent(), tileAnimationSettingsFile.getLength());
	this->map.getMessages().loadFromStream(messagesFile.getContent(), messagesFile.getLength());
	this->map.getTeleports().loadFromStream(teleportsFile.getContent(), teleportsFile.getLength());
	this->map.getSwitchCoordinates().loadFromStream(switchesFile.getContent(), switchesFile.getLength());
	this->map.getInsertToggles().loadFromStream(insertsFile.getContent(), insertsFile.getLength());
	this->map.getKeyHoleToggles().loadFromStream(keyHolesFile.getContent(), keyHolesFile.getLength());
	this->map.getTileProperties().loadFromStream(tilePropertiesFile.getContent(), tilePropertiesFile.getLength());
	this->map.getEnemyTrigger().loadFromStream(enemyTriggersFile.getContent(), enemyTriggersFile.getLength());
	this->map.getBackgroundLayer().loadFromStream(backgroundLayerFile.getContent(), backgroundLayerFile.getLength());
	this->map.getMapLayer().loadFromStream(mapLayerFile.getContent(), mapLayerFile.getLength());
	this->map.getAdditionalLayer().loadFromStream(additionalLayerFile.getContent(), additionalLayerFile.getLength());
	this->map.getEventLayer().loadFromStream(eventLayerFile.getContent(), eventLayerFile.getLength());
	
	this->map.create(2, MAP_WIDTH, MAP_HEIGHT);
}

void StateGame::loadLevelStuff(pocus::data::Data& data, uint8_t episode, uint8_t stage) {
	pocus::data::asset::Pcx backgroundPcx;
	pocus::data::asset::Midi midi;
	pocus::data::asset::Pcx tileSet;
	
	pocus::data::DataFile& backgroundFile = data.fetchFile(DATFILE_IMAGE_BACKGROUND_01);
	pocus::data::DataFile& musicFile = data.fetchFile(DATFILE_MUSIC_03);
	pocus::data::DataFile& tileSetFile = data.fetchFile(DATFILE_TILESET_01);
	
	backgroundPcx.loadFromStream(backgroundFile.getContent(), backgroundFile.getLength());
	midi.loadFromStream(musicFile.getContent(), musicFile.getLength());
	tileSet.loadFromStream(tileSetFile.getContent(), tileSetFile.getLength());
	
	this->map.setMusic(midi.createAsSound());
	this->map.setBackground(backgroundPcx.createTexture());
	this->map.setTileSet(tileSet.createTexture());
}

void StateGame::onCreate(pocus::data::Data& data) {
	loadLevelStuff(data, 1, 1);
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
}

void StateGame::onDetach() {
	LOGI << "StateGame: onDetach";
}

void StateGame::onAttach() {
	LOGI << "StateGame: onAttach";
	
	this->map.start();
}

void StateGame::release() {
	LOGI << "StateGame: release";
}

void StateGame::handleEvents(pocus::EventHandler &eventHandler) {
	if (eventHandler.isButtonDown(pocus::BUTTON_LEFT)) {
		this->offset.setX(this->offset.getX() + 16.0f);
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_RIGHT)) {
		this->offset.setX(this->offset.getX() - 16.0f);
	}
	if (eventHandler.isButtonDown(pocus::BUTTON_UP)) {
		this->offset.setY(this->offset.getY() + 16.0f);
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_DOWN)) {
		this->offset.setY(this->offset.getY() - 16.0f);
	}
}

void StateGame::render(pocus::Renderer &renderer) {
	this->map.render(renderer, this->offset);
	renderer.drawTexture(*this->textureHud, 0, SCREEN_HEIGHT - this->textureHud->getHeight());
}

void StateGame::update(float dt) {
	this->map.update(dt);
}