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
	
	pocus::data::asset::PlayerCoordinates playerCoordinates;
	playerCoordinates.loadFromStream(playerCoordinatesFile.getContent(), playerCoordinatesFile.getLength());
	
	pocus::data::asset::TileAnimationSettings tileAnimationSettings;
	tileAnimationSettings.loadFromStream(tileAnimationSettingsFile.getContent(), tileAnimationSettingsFile.getLength());
	
	pocus::data::asset::Messages messages;
	messages.loadFromStream(messagesFile.getContent(), messagesFile.getLength());
	
	pocus::data::asset::Teleports teleports;
	teleports.loadFromStream(teleportsFile.getContent(), teleportsFile.getLength());
	
	pocus::data::asset::SwitchCoordinates switchCoordinates;
	switchCoordinates.loadFromStream(switchesFile.getContent(), switchesFile.getLength());
	
	pocus::data::asset::ToggleCoordinates insertToggles;
	insertToggles.loadFromStream(insertsFile.getContent(), insertsFile.getLength());
	
	pocus::data::asset::ToggleCoordinates keyHoleToggles;
	keyHoleToggles.loadFromStream(keyHolesFile.getContent(), keyHolesFile.getLength());
	
	pocus::data::asset::TileProperties tileProperties;
	tileProperties.loadFromStream(tilePropertiesFile.getContent(), tilePropertiesFile.getLength());
	
	pocus::data::asset::EnemyTrigger enemyTrigger;
	enemyTrigger.loadFromStream(enemyTriggersFile.getContent(), enemyTriggersFile.getLength());
	
	pocus::data::asset::MapLayer backgroundLayer;
	backgroundLayer.loadFromStream(backgroundLayerFile.getContent(), backgroundLayerFile.getLength());
	
	pocus::data::asset::MapLayer mapLayer;
	mapLayer.loadFromStream(mapLayerFile.getContent(), mapLayerFile.getLength());
	
	pocus::data::asset::MapLayer additionalLayer;
	additionalLayer.loadFromStream(additionalLayerFile.getContent(), additionalLayerFile.getLength());
	
	pocus::data::asset::EventLayer eventLayer;
	eventLayer.loadFromStream(eventLayerFile.getContent(), eventLayerFile.getLength());
}

void StateGame::loadLevelStuff(pocus::data::Data& data, uint8_t episode, uint8_t stage) {
	pocus::data::asset::Pcx backgroundPcx;
	
	pocus::data::DataFile& backgroundFile = data.fetchFile(DATFILE_IMAGE_BACKGROUND_01);
	
	backgroundPcx.loadFromStream(backgroundFile.getContent(), backgroundFile.getLength());
	
	this->backgroud = backgroundPcx.createTexture();
}

void StateGame::onCreate(pocus::data::Data& data) {
	loadLevel(data, 1, 1);
	loadLevelStuff(data, 1, 1);
	
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
	renderer.drawTexture(*this->backgroud, 0, 0);
	renderer.drawTexture(*this->textureHud, 0, SCREEN_HEIGHT - this->textureHud->getHeight());
	renderer.drawTexture(*this->label, 0, 0);
}

void StateGame::update(float dt) {

}