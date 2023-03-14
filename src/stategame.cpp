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
#include "engine/data/asset/leveltileset.h"
#include "engine/data/asset/leveltime.h"
#include "engine/data/asset/levelbackground.h"
#include "engine/data/asset/spriteset.h"

void StateGame::loadLevel(pocus::data::Data& data, pocus::data::Data& executable, uint8_t episode, uint8_t stage) {
	episode--;
	stage--;
	
	pocus::Map& map = this->game.getMap();
	
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
	
	map.getPlayerCoordinates().loadFromStream(playerCoordinatesFile.getContent(), playerCoordinatesFile.getLength());
	map.getTileAnimationSettings().loadFromStream(tileAnimationSettingsFile.getContent(), tileAnimationSettingsFile.getLength());
	map.getMessages().loadFromStream(messagesFile.getContent(), messagesFile.getLength());
	map.getTeleports().loadFromStream(teleportsFile.getContent(), teleportsFile.getLength());
	map.getSwitchCoordinates().loadFromStream(switchesFile.getContent(), switchesFile.getLength());
	map.getInsertToggles().loadFromStream(insertsFile.getContent(), insertsFile.getLength());
	map.getKeyHoleToggles().loadFromStream(keyHolesFile.getContent(), keyHolesFile.getLength());
	map.getTileProperties().loadFromStream(tilePropertiesFile.getContent(), tilePropertiesFile.getLength());
	map.getEnemyTrigger().loadFromStream(enemyTriggersFile.getContent(), enemyTriggersFile.getLength());
	map.getBackgroundLayer().loadFromStream(backgroundLayerFile.getContent(), backgroundLayerFile.getLength());
	map.getMapLayer().loadFromStream(mapLayerFile.getContent(), mapLayerFile.getLength());
	map.getAdditionalLayer().loadFromStream(additionalLayerFile.getContent(), additionalLayerFile.getLength());
	map.getEventLayer().loadFromStream(eventLayerFile.getContent(), eventLayerFile.getLength());
	
	// Load executable stuff
	
	const uint32_t absoluteLevel = (STAGES * episode) + stage;
	
	// Time limit
	pocus::data::DataFile& levelLimitFile = executable.fetchFile(EXEFILE_LIMIT_TIME);
	pocus::data::asset::LevelTime levelTime;
	levelTime.loadFromStream(levelLimitFile.getContent(), levelLimitFile.getLength());
	map.setLimitTime(levelTime.getTime()[absoluteLevel]);
	
	// Tile set
	pocus::data::DataFile& levelTileSetFile = executable.fetchFile(EXEFILE_TILESETS);
	pocus::data::asset::LevelTileSet levelTileSet;
	levelTileSet.loadFromStream(levelTileSetFile.getContent(), levelTileSetFile.getLength());
	pocus::data::asset::Pcx tileSet;
	pocus::data::DataFile& tileSetFile = data.fetchFile(DATFILE_TILESET_01 + levelTileSet.getTileSetIds()[absoluteLevel]);
	tileSet.loadFromStream(tileSetFile.getContent(), tileSetFile.getLength());
	map.setTileSet(tileSet.createTexture());
	
	// Background
	pocus::data::DataFile& backgroundInfoFile = executable.fetchFile(EXEFILE_BACKGROUNDS);
	pocus::data::asset::LevelBackground levelBackgroundInfo;
	levelBackgroundInfo.loadFromStream(backgroundInfoFile.getContent(), backgroundInfoFile.getLength());
	pocus::data::asset::Pcx background;
	pocus::data::DataFile& backgroundFile = data.fetchFile(DATFILE_IMAGE_BACKGROUND_01 + levelBackgroundInfo.getBackgroundIds()[absoluteLevel]);
	background.loadFromStream(backgroundFile.getContent(), backgroundFile.getLength());
	map.setBackground(background.createTexture());
	
	map.create(MAP_WIDTH, MAP_HEIGHT);
}

void StateGame::createHud(pocus::data::Data& data) {
	pocus::data::asset::Palette paletteGame;
	pocus::data::DataFile& paletteGameFile = data.fetchFile(DATFILE_PALETTE_GAME);
	paletteGame.loadFromStream(paletteGameFile.getContent(), paletteGameFile.getLength());
	
	pocus::data::asset::Font font;
	pocus::data::DataFile& fontFile = data.fetchFile(DATFILE_FONT_MAIN);
	font.loadFromStream(fontFile.getContent(), fontFile.getLength());
	
	pocus::data::asset::Image imageStuff;
	pocus::data::DataFile& imageStuffFile = data.fetchFile(DATFILE_IMAGE_STUFF);
	imageStuff.loadFromStream(imageStuffFile.getContent(), imageStuffFile.getLength());
	auto stuffTexture = imageStuff.createTexture(paletteGame);
	
	this->game.getHud().setBackground(loadTexture(data, paletteGame, DATFILE_IMAGE_HUD));
	this->game.getHud().setSilverKeyTexture(stuffTexture->extract(88, 0, 7, 11));
	this->game.getHud().setGoldenKeyTexture(stuffTexture->extract(96, 0, 7, 11));
	this->game.getHud().setFont(std::move(paletteGame), std::move(font), pocus::Hud::DEFAULT_FONT_COLOR);
}

void StateGame::createGame(pocus::data::Data &data) {
	pocus::data::DataFile& paletteGameFile = data.fetchFile(DATFILE_PALETTE_GAME);
	pocus::data::DataFile& fontFile = data.fetchFile(DATFILE_FONT_MAIN);
	
	this->game.getPalette().loadFromStream(paletteGameFile.getContent(), paletteGameFile.getLength());
	this->game.getFont().loadFromStream(fontFile.getContent(), fontFile.getLength());
	this->game.setTextColor(pocus::Game::DEFAULT_TEXT_COLOR);
}

void StateGame::loadSprites(pocus::data::Data& data) {
	pocus::data::asset::Palette paletteGame;
	pocus::data::DataFile& paletteGameFile = data.fetchFile(DATFILE_PALETTE_GAME);
	paletteGame.loadFromStream(paletteGameFile.getContent(), paletteGameFile.getLength());
	
	pocus::data::asset::SpriteSet spriteSet;
	pocus::data::DataFile& spriteSetFile = data.fetchFile(DATFILE_SPRITE_SET);
	spriteSet.loadFromStream(spriteSetFile.getContent(), spriteSetFile.getLength());
	
	this->game.getHocus().setSprite(spriteSet.getSprite(SPRITE_HOCUS),
									*spriteSet.getSprite(SPRITE_HOCUS).createAsTexture(paletteGame));
}

void StateGame::onCreate(pocus::data::DataManager& dataManager) {
	pocus::data::Data& data = dataManager.getData();
	pocus::data::Data& executable = dataManager.getExecutable();
	
	loadLevel(data, executable, 1, 1);
	loadSprites(data);
	createHud(data);
	createGame(data);
}

std::unique_ptr<pocus::Texture> StateGame::loadTexture(pocus::data::Data& data, uint32_t paletteFileIndex, uint32_t imageFileIndex) {
	pocus::data::asset::Image image;
	pocus::data::asset::Palette palette {};
	
	pocus::data::DataFile& paletteFile = data.fetchFile(paletteFileIndex);
	palette.loadFromStream(paletteFile.getContent(), paletteFile.getLength());
	
	pocus::data::DataFile& imageFile = data.fetchFile(imageFileIndex);
	image.loadFromStream(imageFile.getContent(), imageFile.getLength());
	
	return image.createTexture(palette);
}

std::unique_ptr<pocus::Texture> StateGame::loadTexture(pocus::data::Data& data, const pocus::data::asset::Palette& palette, uint32_t imageFileIndex) {
	pocus::data::asset::Image image;
	pocus::data::DataFile& imageFile = data.fetchFile(imageFileIndex);
	image.loadFromStream(imageFile.getContent(), imageFile.getLength());
	return image.createTexture(palette);
}

void StateGame::onDetach() {
	LOGI << "StateGame: onDetach";
}

void StateGame::onAttach() {
	LOGI << "StateGame: onAttach";
	
	this->game.start();
}

void StateGame::release() {
	LOGI << "StateGame: release";
}

void StateGame::handleEvents(pocus::EventHandler &eventHandler) {
	if (eventHandler.isButtonDown(pocus::BUTTON_PAUSE)) {
		this->game.togglePause();
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_LEFT)) {
		this->game.getOffset().setX(this->game.getOffset().getX() + 16.0f);
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_RIGHT)) {
		this->game.getOffset().setX(this->game.getOffset().getX() - 16.0f);
	}
	if (eventHandler.isButtonDown(pocus::BUTTON_UP)) {
		this->game.getOffset().setY(this->game.getOffset().getY() + 16.0f);
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_DOWN)) {
		this->game.getOffset().setY(this->game.getOffset().getY() - 16.0f);
	}
}

void StateGame::render(pocus::Renderer &renderer) {
	this->game.render(renderer);
}

void StateGame::update(float dt) {
	this->game.update(dt);
}