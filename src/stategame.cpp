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

#include "stategame.h"
#include "engine/log.h"

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

}

void StateGame::update(float dt) {

}