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

void Game::start() {
	this->hud.updateScore(this->player.getScore());
	this->hud.updateCrystals(this->player.getCrystals(), this->map.getCrystals());
	this->hud.updateHealth(this->player.getHealth());
	this->hud.updateLevel(this->player.getLevel());
	
	this->tickStart = getNow();
	this->map.start();
}

void Game::render(Renderer &renderer) {
	this->map.render(renderer, this->offset);
	this->hud.render(renderer);
}

void Game::update(float dt) {
	this->map.update(dt);
}

uint32_t Game::getElapsedTime() {
	return ::getElapsedTime(this->tickStart) / 1000;
}

void Game::addScore(uint32_t score) {
	this->player.setScore(this->player.getScore() + score);
	this->hud.updateScore(this->player.getScore());
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
	
	this->hud.updateHealth(health);
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
