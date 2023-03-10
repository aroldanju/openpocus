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
#include "version.h"
#include "apogeesplash.h"
#include "definitions.h"
#include "introsplash.h"
#include "mainmenu.h"

OpenPocus::OpenPocus(const pocus::RendererParameters &rendererParameters):
	PocusEngine(
			pocus::Provider::provideRenderer(rendererParameters),
			pocus::Provider::provideEventHandler(),
			pocus::Provider::provideAudio()
			)
{
}

void OpenPocus::createStates(pocus::StateManager& stateManager) {
	stateManager.addState(STATE_SPLASH_APOGEE, std::make_unique<ApogeeSplash>());
	stateManager.addState(STATE_SPLASH_INTRO, std::make_unique<IntroSplash>());
	stateManager.addState(STATE_GAME, std::make_unique<StateGame>());
	stateManager.addState(STATE_MENU_MAIN, std::make_unique<MainMenu>());
	
	//stateManager.setStartupState(STATE_SPLASH_APOGEE);
	stateManager.setStartupState(STATE_MENU_MAIN);
}

bool OpenPocus::loadData(pocus::data::Data& data) {
	pocus::data::Fat fat = pocus::data::FatLoader::loadFromFile(FAT_FILE);
	return data.loadFromFile(DAT_PATH, fat);
}