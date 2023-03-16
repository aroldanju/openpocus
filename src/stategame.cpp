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
#include "engine/data/asset/iteminfo.h"
#include "engine/provider/provider.h"
#include "engine/data/asset/voc.h"

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
	
	pocus::data::DataFile& soundHintFile = data.fetchFile(DATFILE_VOC_HINT);
	pocus::data::asset::Voc vocHint;
	vocHint.loadFromStream(soundHintFile.getContent(), soundHintFile.getLength());
	this->game.getSoundHint() = vocHint.createAsSound();
	
	pocus::data::DataFile& soundItemFile = data.fetchFile(DATFILE_VOC_ITEM_1);
	pocus::data::asset::Voc vocItem;
	vocItem.loadFromStream(soundItemFile.getContent(), soundItemFile.getLength());
	this->game.getSoundItem() = vocItem.createAsSound();
	
	pocus::data::DataFile& soundCrystalFile = data.fetchFile(DATFILE_VOC_WIN);
	pocus::data::asset::Voc vocCrystal;
	vocCrystal.loadFromStream(soundCrystalFile.getContent(), soundCrystalFile.getLength());
	this->game.getSoundCrystal() = vocCrystal.createAsSound();
	
	pocus::data::DataFile& soundPotionFile = data.fetchFile(DATFILE_VOC_POTION);
	pocus::data::asset::Voc vocPotion;
	vocPotion.loadFromStream(soundPotionFile.getContent(), soundPotionFile.getLength());
	this->game.getSoundPotion() = vocPotion.createAsSound();
	
	pocus::data::DataFile& soundHitFile = data.fetchFile(DATFILE_VOC_HIT);
	pocus::data::asset::Voc vocHit;
	vocHit.loadFromStream(soundHitFile.getContent(), soundHitFile.getLength());
	this->game.getSoundHit() = vocHit.createAsSound();
	
	this->game.getHocus().setPosition(
		pocus::Point(
			this->game.getMap().getPlayerCoordinates().getX() * TILE_SIZE,
			this->game.getMap().getPlayerCoordinates().getY() * TILE_SIZE
		)
	);
	
	for (int i = 0; i < pocus::data::asset::Messages::MESSAGES; i++) {
		const auto& message = this->game.getMap().getMessages().getMessages()[i];
		
		if (message.x == 0xffff) {
			continue;
		}
		
		uint32_t lineIndex = 0;
		uint32_t maxWidth = 0;
		std::vector<std::unique_ptr<pocus::Texture>> textures;
		
		do {
			textures.push_back(this->game.getFont().writeShadow(std::string(message.lines[lineIndex]), this->game.getPalette(), pocus::Game::DEFAULT_TEXT_COLOR));
			if (textures[textures.size() - 1]->getWidth() > maxWidth) {
				maxWidth = textures[textures.size() - 1]->getWidth();
			}
		} while(message.lines[++lineIndex][0] != '\0');
		
		auto hintTexture = pocus::Provider::provideTexture(maxWidth, lineIndex * 8 + lineIndex * 3);
		hintTexture->fill(255, 0, 255);
		
		lineIndex = 0;
		
		for (auto& texture : textures) {
			hintTexture->paste(*texture, 0, 0, maxWidth / 2 - texture->getWidth() / 2, lineIndex * 12);
			lineIndex++;
		}
		
		hintTexture->setColorKey(255, 0, 255);
		
		this->game.getHintTextures().push_back(std::move(hintTexture));
	}
	
	this->game.getViewportSize().set(SCREEN_WIDTH, SCREEN_HEIGHT);
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
	
	// Score texts
	pocus::data::asset::Sprite& spriteScores = spriteSet.getSprite(SPRITE_SCORE);
	
	auto spriteScoresTexture = spriteScores.createAsTexture(paletteGame);
	auto texture100 = spriteScoresTexture->extract(0, 0, spriteScores.header.width4, spriteScores.header.height);
	auto texture250 = spriteScoresTexture->extract(spriteScores.header.width4, 0, spriteScores.header.width4, spriteScores.header.height);
	auto texture500 = spriteScoresTexture->extract(spriteScores.header.width4 * 2, 0, spriteScores.header.width4, spriteScores.header.height);
	auto texture1000 = spriteScoresTexture->extract(spriteScores.header.width4 * 3, 0, spriteScores.header.width4, spriteScores.header.height);
	
	this->game.getScoreTextures().insert(std::make_pair(100, std::move(texture100)));
	this->game.getScoreTextures().insert(std::make_pair(250, std::move(texture250)));
	this->game.getScoreTextures().insert(std::make_pair(500, std::move(texture500)));
	this->game.getScoreTextures().insert(std::make_pair(1000, std::move(texture1000)));
}

void StateGame::loadItems(pocus::data::Data& executable) {
	pocus::data::DataFile& itemsFile = executable.fetchFile(EXEFILE_ITEMS);
	
	this->game.getItemInfo().loadFromStream(itemsFile.getContent(), itemsFile.getLength());
}

void StateGame::onCreate(pocus::data::DataManager& dataManager) {
	pocus::data::Data& data = dataManager.getData();
	pocus::data::Data& executable = dataManager.getExecutable();
	
	loadLevel(data, executable, 1, 1);
	loadSprites(data);
	createHud(data);
	createGame(data);
	loadItems(executable);
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
	
	if (eventHandler.isButtonDown(pocus::BUTTON_LEFT)) {
		this->game.startMovement(pocus::Entity::LEFT);
	}
	else if (eventHandler.isButtonUp(pocus::BUTTON_LEFT)) {
		this->game.stopMovement(pocus::Entity::LEFT);
	}
	
	if (eventHandler.isButtonDown(pocus::BUTTON_RIGHT)) {
		this->game.startMovement(pocus::Entity::RIGHT);
	}
	else if (eventHandler.isButtonUp(pocus::BUTTON_RIGHT)) {
		this->game.stopMovement(pocus::Entity::RIGHT);
	}
	
	if (eventHandler.isButtonDown(pocus::BUTTON_JUMP)) {
		this->game.jump();
	}
	
	if (eventHandler.isButtonDown(pocus::BUTTON_UP)) {
		this->game.activate();
	}
	
	if (eventHandler.isButtonDown(pocus::BUTTON_SELECTION)) {
		this->game.hurt(5);
	}
	
	/*
	else if (eventHandler.isButtonDown(pocus::BUTTON_LEFT)) {
		this->game.getOffset().setX(this->game.getOffset().getX() + 16.0f);
		std::cout << "OFFSET: " << this->game.getOffset().getX() << ", " << this->game.getOffset().getY() << std::endl;
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_RIGHT)) {
		this->game.getOffset().setX(this->game.getOffset().getX() - 16.0f);
		std::cout << "OFFSET: " << this->game.getOffset().getX() << ", " << this->game.getOffset().getY() << std::endl;
	}
	if (eventHandler.isButtonDown(pocus::BUTTON_UP)) {
		this->game.getOffset().setY(this->game.getOffset().getY() + 16.0f);
		std::cout << "OFFSET: " << this->game.getOffset().getX() << ", " << this->game.getOffset().getY() << std::endl;
	}
	else if (eventHandler.isButtonDown(pocus::BUTTON_DOWN)) {
		this->game.getOffset().setY(this->game.getOffset().getY() - 16.0f);
		std::cout << "OFFSET: " << this->game.getOffset().getX() << ", " << this->game.getOffset().getY() << std::endl;
	}
	*/
}

void StateGame::render(pocus::Renderer &renderer) {
	this->game.render(renderer);
}

void StateGame::update(float dt) {
	this->game.update(dt);
}