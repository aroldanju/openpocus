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
#include "map.h"

using namespace pocus;

// Tile -----------------------------------------------------------------------------------------------

Tile::Tile(uint32_t x, uint32_t y):
	tilePosition(Point((float)x, (float)y))
{
}

const Point &Tile::getTilePosition() const {
	return tilePosition;
}

void Tile::setTilePosition(const Point &tilePosition) {
	Tile::tilePosition = tilePosition;
}

bool Tile::isVisible() const {
	return visible;
}

void Tile::setVisible(bool visible) {
	Tile::visible = visible;
}

uint16_t Tile::getId() const {
	return id;
}

void Tile::setId(uint16_t id) {
	Tile::id = id;
}

Animation& Tile::getAnimation() {
	return this->animation;
}

/*
void Tile::setAnimation(const Animation& animation) {
	this->animation = animation;
}
*/

// Layer -----------------------------------------------------------------------------------------------


Layer::Layer(uint32_t width, uint32_t height)   {
	create(width, height);
}

void Layer::create(uint32_t width, uint32_t height)    {
	this->width = width;
	this->height = height;
	
	for (uint32_t i = 0; i < this->height; i++) {
		for (uint32_t j = 0; j < this->width; j++) {
			this->tiles.emplace_back(j, i);
		}
	}
}

Tile& Layer::getTile(uint32_t x, uint32_t y) {
	return this->tiles[y * this->width + x];
}

bool Layer::isVisible() const {
	return visible;
}

void Layer::setVisible(bool visible) {
	Layer::visible = visible;
}

// Map -------------------------------------------------------------------------------------------------

Map::Chunk Map::getChunk(const Point& position, const Size& size) {
	Map::Chunk chunk(size);
	
	int fx = position.getX() - size.getWidth() / 2;
	int tx = position.getX() + size.getWidth() / 2;
	int fy = position.getY() - size.getHeight() / 2;
	int ty = position.getY() + size.getHeight() / 2;
	
	if (fx < 0) {
		fx = 0;
		tx = size.getWidth();
	}
	if (tx >= MAP_WIDTH) {
		fx = MAP_WIDTH - size.getWidth();
		tx = MAP_WIDTH;
	}
	
	if (fy < 0) {
		fy = 0;
		ty = size.getHeight();
	}
	if (ty >= MAP_HEIGHT) {
		fy = MAP_HEIGHT - size.getHeight();
		ty = MAP_HEIGHT;
	}
	
	std::cout << "Position = {" << position.getX() << ", " << position.getY() << "}" << std::endl;
	std::cout << "Size = {" << size.getWidth() << ", " << size.getHeight() << "}" << std::endl;
	std::cout << "Chunk = {" << fx << ", " << fy << "; " << tx << ", " << ty << "}" << std::endl;
	
	for (int i = fy; i < ty; i++) {
		for (int j = fx; j < tx; j++) {
			chunk.addTile(this->layers[1].getTile(j, i).getId());
		}
	}
	
	return chunk;
}

Layer& Map::getLayer(uint8_t layer) {
	return this->layers[layer];
}

void Map::setMusic(std::unique_ptr<Sound> music) {
	this->backgroundMusic = std::move(music);
}

void Map::setTileSet(const std::unique_ptr<Texture>& tileSet) {
	const uint32_t columns = 20;
	const uint32_t rows = 12;
	const uint32_t frameWidth = TILE_SIZE;
	const uint32_t frameHeight = TILE_SIZE;
	
	for (int i = 0; i < columns * rows; i++) {
		const uint32_t x = i % columns;
		const uint32_t y = i / columns;
		auto frame = tileSet->extract(x * frameWidth, y * frameHeight, frameWidth, frameHeight);
		this->tileSet.push_back(std::move(frame));
	}
}

void Map::setBackground(std::unique_ptr<Texture> texture) {
	this->backgroundImage = std::move(texture);
}

void Map::render(Renderer &renderer, const Point& offset) {
	if (this->backgroundImage) {
		const auto backgroundOffset = (float)((int)((offset.getX() * -1.0f) / 2.0f) % (int)this->backgroundImage->getWidth());
		if (backgroundOffset < 0.0f) {
			renderer.drawTexture(*this->backgroundImage, Point(backgroundOffset, 0));
			renderer.drawTexture(*this->backgroundImage, Point(this->backgroundImage->getWidth() + backgroundOffset, 0));
		}
		else if (backgroundOffset > 0.0f) {
			renderer.drawTexture(*this->backgroundImage, Point(backgroundOffset, 0));
			renderer.drawTexture(*this->backgroundImage, Point(-(float)this->backgroundImage->getWidth() + backgroundOffset, 0));
		}
		else {
			renderer.drawTexture(*this->backgroundImage, Point(0, 0));
		}
	}
	
	for (auto& layer : this->layers) {
		if (!layer.isVisible()) {
			continue;
		}
		
		for (uint32_t y = 0; y < this->height; y++) {
			for (uint32_t x = 0; x < this->width; x++) {
				const uint16_t tileId = layer.getTile(x, y).getId();
				if (tileId != 0xff && layer.getTile(x, y).isVisible()) {
					layer.getTile(x, y).getAnimation().render(
						renderer, Point(
				  		x * 16 - offset.getX(),
						y * 16 - offset.getY()
					));
				}
			}
		}
	}
}

void Map::update(float dt) {
	for (auto& layer : this->layers) {
		for (uint32_t y = 0; y < this->height; y++) {
			for (uint32_t x = 0; x < this->width; x++) {
				layer.getTile(x, y).getAnimation().update(dt);
			}
		}
	}
}

void Map::start() {
	//this->backgroundMusic->play();
}

void Map::create(uint32_t width, uint32_t height) {
	this->width = width;
	this->height = height;
	
	this->crystals = 0;
	
	// Create fixed layers: 0 background; 1 tiles
	this->layers.emplace_back(width, height);
	this->layers.emplace_back(width, height);
	
	// Create tile animation prototypes
	for (uint32_t i = 0; i < data::asset::TileAnimationSettings::TILES; i++) {
		const data::asset::TileAnimationSettings::Entry& entry = this->tileAnimationSettings.getEntries()[i];
		
		Animation animation;
		animation.setFps(10);
		
		if (entry.animationType == data::asset::TileAnimationSettings::RANDOM) {
			animation.setRandomStart(true);
		}
		
		if (entry.firstIndex != entry.lastIndex && entry.animationType == data::asset::TileAnimationSettings::PERMANENT) {
			for (uint16_t frameIndex = entry.firstIndex; frameIndex < entry.lastIndex + 1; frameIndex++) {
				animation.addFrame(
					this->tileSet[frameIndex]->extract(0, 0, TILE_SIZE, TILE_SIZE)
				);
			}
			
			// Randomize starting frame
			animation.setCurrentFrame(rand() % animation.getFrameCount());
			
			this->animatedTileSet.emplace_back(std::move(animation));
		}
		else {
			animation.addFrame(this->tileSet[i]->extract(0, 0, TILE_SIZE, TILE_SIZE));
			this->animatedTileSet.emplace_back(std::move(animation));
		}
	}
	
	for (uint32_t i = 0; i < width * height; i++) {
		const uint32_t x = i % width;
		const uint32_t y = i / width;
		
		// Events
		const uint16_t eventId = this->eventLayer.getData()[i];
		if (eventId == 5) {
			this->crystals++;
		}
		
		// Background layer
		const uint16_t backgroundId = this->backgroundLayer.getData()[i];
		Tile& backgroundTile = this->layers[0].getTile(x, y);
		backgroundTile.setId(backgroundId);
		backgroundTile.setVisible(backgroundId != data::asset::MapLayer::TILE_EMPTY);
		if (backgroundTile.isVisible()) {
			backgroundTile.getAnimation().createFrom(this->animatedTileSet[backgroundId]);
		}

		// Foreground layer
		const uint16_t tileId = this->mapLayer.getData()[i];
		Tile& mapTile = this->layers[1].getTile(x, y);
		mapTile.setId(tileId);
		mapTile.setVisible(tileId != data::asset::MapLayer::TILE_EMPTY);
		if (mapTile.isVisible()) {
			mapTile.getAnimation().createFrom(this->animatedTileSet[tileId]);
		}
	}
}

data::asset::PlayerCoordinates &Map::getPlayerCoordinates() {
	return playerCoordinates;
}

void Map::setPlayerCoordinates(const data::asset::PlayerCoordinates &playerCoordinates) {
	Map::playerCoordinates = playerCoordinates;
}

data::asset::TileAnimationSettings &Map::getTileAnimationSettings() {
	return tileAnimationSettings;
}

void Map::setTileAnimationSettings(const data::asset::TileAnimationSettings &tileAnimationSettings) {
	Map::tileAnimationSettings = tileAnimationSettings;
}

data::asset::Messages &Map::getMessages() {
	return messages;
}

void Map::setMessages(const data::asset::Messages &messages) {
	Map::messages = messages;
}

data::asset::Teleports &Map::getTeleports() {
	return teleports;
}

void Map::setTeleports(const data::asset::Teleports &teleports) {
	Map::teleports = teleports;
}

data::asset::SwitchCoordinates &Map::getSwitchCoordinates() {
	return switchCoordinates;
}

void Map::setSwitchCoordinates(const data::asset::SwitchCoordinates &switchCoordinates) {
	Map::switchCoordinates = switchCoordinates;
}

data::asset::ToggleCoordinates &Map::getInsertToggles() {
	return insertToggles;
}

void Map::setInsertToggles(const data::asset::ToggleCoordinates &insertToggles) {
	Map::insertToggles = insertToggles;
}

data::asset::ToggleCoordinates &Map::getKeyHoleToggles() {
	return keyHoleToggles;
}

void Map::setKeyHoleToggles(const data::asset::ToggleCoordinates &keyHoleToggles) {
	Map::keyHoleToggles = keyHoleToggles;
}

data::asset::TileProperties &Map::getTileProperties() {
	return tileProperties;
}

void Map::setTileProperties(const data::asset::TileProperties &tileProperties) {
	Map::tileProperties = tileProperties;
}

data::asset::EnemyTrigger &Map::getEnemyTrigger() {
	return enemyTrigger;
}

void Map::setEnemyTrigger(const data::asset::EnemyTrigger &enemyTrigger) {
	Map::enemyTrigger = enemyTrigger;
}

data::asset::MapLayer &Map::getBackgroundLayer() {
	return backgroundLayer;
}

void Map::setBackgroundLayer(const data::asset::MapLayer &backgroundLayer) {
	Map::backgroundLayer = backgroundLayer;
}

data::asset::MapLayer &Map::getMapLayer() {
	return mapLayer;
}

void Map::setMapLayer(const data::asset::MapLayer &mapLayer) {
	Map::mapLayer = mapLayer;
}

data::asset::MapLayer &Map::getAdditionalLayer() {
	return additionalLayer;
}

void Map::setAdditionalLayer(const data::asset::MapLayer &additionalLayer) {
	Map::additionalLayer = additionalLayer;
}

data::asset::EventLayer& Map::getEventLayer() {
	return eventLayer;
}

void Map::setEventLayer(const data::asset::EventLayer &eventLayer) {
	Map::eventLayer = eventLayer;
}

uint32_t Map::getLimitTime() const {
	return limitTime;
}

void Map::setLimitTime(uint32_t limitTime) {
	Map::limitTime = limitTime;
}

uint8_t Map::getCrystals() const {
	return crystals;
}

Map::Chunk::Chunk(const Size &size):
	size(size)
{}


std::vector<uint32_t>& Map::Chunk::getTiles() {
	return this->tiles;
}

const Size& Map::Chunk::getSize() const {
	return this->size;
}

void Map::Chunk::addTile(uint32_t id) {
	this->tiles.push_back(id);
}