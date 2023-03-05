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

#include "openpocus.h"
#include "engine/provider/provider.h"
#include "stategame.h"
#include "engine/data/fatloader.h"

OpenPocus::OpenPocus(const pocus::RendererParameters &rendererParameters):
	PocusEngine(
			pocus::Provider::provideRenderer(rendererParameters),
			pocus::Provider::provideEventHandler())
{
}

void OpenPocus::createStates(pocus::StateManager& stateManager) {
	stateManager.addState("my_state", std::make_unique<StateGame>());
}

bool OpenPocus::loadData(pocus::data::Data& data) {
	pocus::data::Fat fat = pocus::data::FatLoader::loadFromFile("../data/shareware.fat");
	return data.loadFromFile("../hocuspocus", fat);
}