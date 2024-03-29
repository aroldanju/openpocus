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
#include <cmath>
#include "game.h"

using namespace pocus;

Map& Game::getMap() {
	return this->map;
}

Player& Game::getPlayer() {
	return this->player;
}

Hud& Game::getHud() {
	return this->hud;
}

Point& Game::getOffset() {
	return this->offset;
}

Hocus& Game::getHocus() {
	return this->hocus;
}

Size& Game::getViewportSize() {
	return this->viewportSize;
}

data::asset::ItemInfo& Game::getItemInfo() {
	return this->itemInfo;
}

std::map<uint32_t, std::unique_ptr<Texture>>& Game::getScoreTextures() {
	return this->scoreTextures;
}

std::vector<std::unique_ptr<Texture>>& Game::getHintTextures() {
	return this->hintTextures;
}

std::unique_ptr<Sound>& Game::getSoundHint() {
	return this->soundHint;
}

std::unique_ptr<Sound>& Game::getSoundItem() {
	return this->soundItem;
}

std::unique_ptr<Sound>& Game::getSoundCrystal() {
	return this->soundCrystal;
}

std::unique_ptr<Sound>& Game::getSoundPotion() {
	return this->soundPotion;
}

std::unique_ptr<Sound>& Game::getSoundHit() {
	return this->soundHit;
}

void Game::start() {
	this->hud.updateScore(this->player.getScore());
	this->hud.updateCrystals(this->player.getCrystals(), this->map.getCrystals());
	this->hud.updateHealth(this->player.getHealth());
	this->hud.updateLevel(this->player.getLevel());
	
	this->labelPaused = this->font.writeShadow("Game Paused", this->palette, this->textColor);
	
	this->tickStart = getNow();
	this->map.start();
}

void Game::render(Renderer &renderer) {
	this->map.render(renderer, this->offset);
	
	this->hocus.render(renderer, this->offset);
	
	this->hud.render(renderer);
	
	for (auto& scoreText : this->scoreTexts) {
		if (getElapsedTime(scoreText.getTickCreation()) < SCORE_TEXT_LIFETIME) {
			scoreText.render(renderer, this->offset);
		}
	}

#ifdef __DEBUG_POCUS__
#ifdef __DEBUG_COLLISION__
	const Point tilePosition = this->hocus.getTilePosition();
	renderer.drawRect(Rect(
		Point(
		tilePosition.getX() * TILE_SIZE - this->offset.getX(),
		tilePosition.getY() * TILE_SIZE - this->offset.getY()
		),
		Size(TILE_SIZE, TILE_SIZE * 2)), color::blueAlpha);
#endif
#endif
	
	if (this->paused) {
		if (isShowingHint()) {
			Texture& hintTexture = *this->hintTextures[this->currentHint];
			renderer.drawTexture(hintTexture,
								 Point(
									 this->viewportSize.getWidth() / 2 - hintTexture.getWidth() / 2,
									 (this->viewportSize.getHeight() - this->hud.getBackground().getHeight()) / 2 -
										 hintTexture.getHeight() / 2
								 )
			);
		}
		else {
			renderer.drawTexture(*this->labelPaused,
								 Point(
									 renderer.getWidth() / 2 - this->labelPaused->getWidth() / 2,
									 (renderer.getHeight() - this->hud.getBackground().getHeight()) / 2 -
									 this->labelPaused->getHeight() / 2)
			);
		}
	}
}

void Game::update(float dt) {
	if (this->paused) {
		return;
	}
	
	this->map.update(dt);
	
	this->hocus.update();
	
	for (auto& scoreText : this->scoreTexts) {
		if (getElapsedTime(scoreText.getTickCreation()) < SCORE_TEXT_LIFETIME) {
			scoreText.move(dt);
		}
	}
	
	move(dt);
	
	checkItems();
	checkHazards();
}

/*
uint32_t Game::getElapsedTime() {
	return ::getElapsedTime(this->tickStart) / 1000;
}
*/

void Game::addScore(uint32_t score) {
	this->player.setScore(this->player.getScore() + score);
	this->hud.updateScore(this->player.getScore());
	
	auto iterator = this->scoreTextures.find(score);
	if (iterator != this->scoreTextures.end()) {
		addScoreText(*iterator->second, this->hocus.getRect().getPosition());
	}
}

void Game::addScoreText(Texture& texture, const Point& point) {
	
	const auto createScoreText = [&texture, point](Entity& scoreText) -> void {
		scoreText.resetStates();
		scoreText.setVelocity({ 0.f, -1.f });
		scoreText.setSpeed(.5f);
		scoreText.setPosition(point);
		scoreText.addState("show", Animation::createFromFrame(texture, &color::pink));
		scoreText.setCurrentState("show");
		scoreText.setTickCreation(getNow());
	};
	
	for (auto& scoreText : this->scoreTexts) {
		if (getElapsedTime(scoreText.getTickCreation()) >= SCORE_TEXT_LIFETIME) {
			createScoreText(scoreText);
			return;
		}
	}
	
	Entity scoreText;
	createScoreText(scoreText);
	this->scoreTexts.push_back(std::move(scoreText));
}

void Game::addCrystal(uint32_t amount) {
	this->player.setCrystals(this->player.getCrystals() + amount);
	this->hud.updateCrystals(this->player.getCrystals(), this->map.getCrystals());
}

void Game::removeHealth(uint8_t health) {
	if (this->player.getHealth() - health < 0) {
		this->player.setHealth(0);
	}
	else {
		this->player.setHealth(this->player.getHealth() - health);
	}
	
	this->hud.updateHealth(this->player.getHealth());
}

void Game::addHealth(uint8_t health) {
	if (this->player.getHealth() + health > PLAYER_MAX_HEALTH) {
		this->player.setHealth(PLAYER_MAX_HEALTH);
	}
	else {
		this->player.setHealth(this->player.getHealth() + health);
	}
	
	this->hud.updateHealth(this->player.getHealth());
}

void Game::addSilverKey() {
	this->player.setSilverKey(true);
	this->hud.updateKeys(this->player.hasSilverKey(), this->player.hasGoldenKey());
}

void Game::removeSilverKey(){
	this->player.setSilverKey(false);
	this->hud.updateKeys(this->player.hasSilverKey(), this->player.hasGoldenKey());
}

void Game::addGoldenKey(){
	this->player.setGoldKey(true);
	this->hud.updateKeys(this->player.hasSilverKey(), this->player.hasGoldenKey());
}

void Game::removeGoldenKey(){
	this->player.setGoldKey(false);
	this->hud.updateKeys(this->player.hasSilverKey(), this->player.hasGoldenKey());
}

void Game::togglePause() {
	this->paused = !this->paused;
}

data::asset::Palette& Game::getPalette() {
	return this->palette;
}

data::asset::Font& Game::getFont() {
	return this->font;
}

void Game::setTextColor(uint8_t color) {
	this->textColor = color;
}

void Game::startMovement(const Entity::Direction_t& direction) {
	if (this->paused) {
		if (isShowingHint()) {
			hideHint();
		}
		
		return;
	}
	
	this->hocus.startMovement(direction);
}

void Game::stopMovement(const Entity::Direction_t& direction) {
	if (this->paused) {
		if (isShowingHint()) {
			hideHint();
		}
		
		return;
	}
	
	this->hocus.stopMovement(direction);
}

void Game::centerCamera(const Hocus& hocus, const Size& viewportSize) {
	this->offset.set(
		(hocus.getRect().getPosition().getX() + TILE_SIZE - viewportSize.getWidth() / 2 - (hocus.getRect().getSize().getWidth() / 2)),
		(hocus.getRect().getPosition().getY() - viewportSize.getHeight() / 2)
	);
	
	const Point limitOffset = Point(
		MAP_WIDTH * TILE_SIZE - viewportSize.getWidth(),
		MAP_HEIGHT * TILE_SIZE - viewportSize.getHeight()
	);
	
	if (this->offset.getX() < 0.0f) {
		this->offset.setX(.0f);
	}
	else if (this->offset.getX() >= limitOffset.getX()) {
		this->offset.setX(limitOffset.getX());
	}
	
	if (this->offset.getY() < 0.0f) {
		this->offset.setY(.0f);
	}
	else if (this->offset.getY() >= limitOffset.getY()) {
		this->offset.setY(limitOffset.getY());
	}
}

void Game::jump() {
	if (this->paused) {
		if (isShowingHint()) {
			hideHint();
		}
		
		return;
	}
	
	if (this->hocus.getState() == Hocus::JUMP || this->hocus.getState() == Hocus::FALL) {
		return;
	}
	
	const bool aboveTile = this->map.getLayer(1).getTile(this->hocus.getTilePosition().getX(), this->hocus.getTilePosition().getY() - 1).isVisible();
	if (aboveTile) {
		return;
	}
	
	this->hocus.jump();
}

void Game::showHint(uint32_t id) {
	this->currentHint = (int)id;
	this->paused = true;
	
	if (this->soundHint) {
		this->soundHint->play();
	}
}

void Game::hideHint() {
	this->currentHint = -1;
	this->paused = false;
}

void Game::activate() {
	const Point& tilePosition = this->hocus.getTilePosition();

	// Check for hint wizard messages
	for (int i = 0; i < data::asset::Messages::MESSAGES; i++) {
		const data::asset::Messages::Entry& message = this->map.getMessages().getMessages()[i];
		if (message.y == (int)tilePosition.getY() && message.x == (int)tilePosition.getX() &&
				this->map.getEvent(tilePosition) == data::asset::EventLayer::WIZARD) {
			showHint(i);
			return;
		}
	}
}

void Game::hurt(uint8_t health) {
	if (this->hocus.isInvulnerable()) {
		return;
	}
	
	removeHealth(health);
	
	this->hocus.hit(Entity::DEFAULT_HIT_TIME);
	
	if (this->soundHit) {
		this->soundHit->play();
	}
}

void Game::move(float dt) {
	if (this->hocus.getVelocity().getX() == .0f && this->hocus.getVelocity().getY() == .0f) {
		return;
	}
	
	const Point lastPosition = this->hocus.getRect().getPosition();
	
	this->hocus.move(dt);
	
	if (this->hocus.getRect().getPosition().getX() < .0f) {
		this->hocus.setPosition(lastPosition);
		return;
	}
	
	const Point tilePosition = this->hocus.getTilePosition();
	
	const Tile& tile = this->map.getLayer(1).getTile(tilePosition.getX(), tilePosition.getY());
	const Tile& tileAbove = this->map.getLayer(1).getTile(tilePosition.getX(), tilePosition.getY() - 1);
	const Tile& tileFeet = this->map.getLayer(1).getTile(tilePosition.getX(), tilePosition.getY() + 1);
	const Tile& tileBelow = this->map.getLayer(1).getTile(tilePosition.getX(), tilePosition.getY() + 2);
	
	if (this->hocus.getState() == Hocus::FALL) {
		if (tileFeet.isVisible()) {
			this->hocus.grounded();
			this->hocus.setPosition(Point(lastPosition.getX(), tileAbove.getTilePosition().getY() * TILE_SIZE));
			centerCamera(this->hocus,Size(this->viewportSize.getWidth(),this->viewportSize.getHeight() - this->hud.getBackground().getHeight()));
			return;
		}
	}
	else if (this->hocus.getState() == Hocus::JUMP) {
		const bool above = tileAbove.isVisible();
		if (above) {
			this->hocus.startFalling();
			this->hocus.setPosition(lastPosition);
		}
	}
	
	// Tile ahead blocked
	if (tile.isVisible() || (!tile.isVisible() && tileFeet.isVisible() && tileAbove.isVisible())) {
		this->hocus.setPosition(lastPosition);
		return;
	}
	
	if (this->hocus.getState() == Hocus::WALK) {
		if (!tileBelow.isVisible() && !tileFeet.isVisible()) {
			// Step down or falling
			if (tilePosition.getY() < MAP_HEIGHT - 3) {
				const Tile &tileFall = this->map.getLayer(1).getTile(tilePosition.getX(), tilePosition.getY() + 3);
				if (!tileFall.isVisible()) {
					this->hocus.startFalling();
				}
				else {
					this->hocus.setY(this->hocus.getRect().getPosition().getY() + TILE_SIZE);
				}
			}
			else {
				this->hocus.setY(this->hocus.getRect().getPosition().getY() + TILE_SIZE);
			}
		}
		else if (tileFeet.isVisible() && !tile.isVisible() && !tileAbove.isVisible()) {
			// Step up
			this->hocus.setY(this->hocus.getRect().getPosition().getY() - TILE_SIZE);
		}
	}
	
	centerCamera(this->hocus,
				 Size(
					 this->viewportSize.getWidth(),
					 this->viewportSize.getHeight() - this->hud.getBackground().getHeight()
				 ));
}

void Game::checkItems() {
	
	const auto checkItemAt = [this](const Point& position) -> void {
		data::asset::EventLayer::Event_t event = this->map.getEvent(position);
		
		if (event == data::asset::EventLayer::EMPTY) {
			return;
		}
		
		const data::asset::ItemInfo::Entry& item = this->itemInfo.getItems()[event];

#ifdef __DEBUG_POCUS__
#ifdef __DEBUG_ITEM__
		std::cout << "Item -> " << std::string(item.name) << std::endl;
		std::cout << "   Score: " << item.score << std::endl;
		std::cout << "   Heal: " << (int)item.heal << std::endl;
		std::cout << "   Fire power: " << (int)item.firePower << std::endl;
		std::cout << "   Type: " << (int)item.type << std::endl;
		std::cout << "   Padding: " << (int)item.padding << std::endl;
#endif // __DEBUG_ITEM__
#endif // __DEBUG_POCUS__
		
		namespace asset = data::asset;
		
		if (event == asset::EventLayer::RUBY || event == asset::EventLayer::DIAMOND || event == asset::EventLayer::GLOBET ||
				event == asset::EventLayer::CROWN) {
			this->map.removeTile(0, position);
			this->map.disableEvent(position);
			addScore(item.score);
			if (this->soundItem) {
				this->soundItem->play();
			}
		}
		else if (event == asset::EventLayer::CRYSTAL) {
			this->map.removeTile(0, position);
			this->map.disableEvent(position);
			addCrystal(1);
			if (this->soundCrystal) {
				this->soundCrystal->play();
			}
		}
		else if (event == asset::EventLayer::HEAL_POTION) {
			this->map.removeTile(0, position);
			this->map.disableEvent(position);
			addHealth(item.heal);
			if (this->soundPotion) {
				this->soundPotion->play();
			}
		}
		else if (event == asset::EventLayer::GOLD_KEY || event == asset::EventLayer::SILVER_KEY) {
			this->map.removeTile(0, position);
			this->map.disableEvent(position);
			switch (event) {
				case asset::EventLayer::GOLD_KEY: addGoldenKey(); break;
				case asset::EventLayer::SILVER_KEY: addSilverKey(); break;
			}
			if (this->soundCrystal) {
				this->soundCrystal->play();
			}
		}
	};
	
	const Point tilePosition = this->hocus.getTilePosition();
	
	checkItemAt(tilePosition);
	checkItemAt({tilePosition.getX(), tilePosition.getY() + 1});
}

void Game::checkHazards() {
	Point position = this->hocus.getTilePosition();
	position.setY(position.getY() + 1);
	
	data::asset::EventLayer::Event_t event = this->map.getEvent(position);
	if (event == data::asset::EventLayer::LAVA || event == data::asset::EventLayer::SPIKES) {
		// TODO move to constant
		hurt(4);
	}
}

bool Game::isShowingHint() const {
	return this->currentHint != -1;
}