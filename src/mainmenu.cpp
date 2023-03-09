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

#include "mainmenu.h"
#include "engine/log.h"
#include "version.h"

void MainMenu::onCreate(pocus::data::Data& data) {
	LOGI << "MainMenu: create";
	
	pocus::data::asset::Font font;
	pocus::data::asset::Palette palette;
	
	pocus::data::DataFile& fontFile = data.fetchFile(DATFILE_FONT_MAIN);
	pocus::data::DataFile& paletteFile = data.fetchFile(DATFILE_PALETTE_MENU);
	
	font.loadFromStream(fontFile.getContent(), fontFile.getLength());
	palette.loadFromStream(paletteFile.getContent(), paletteFile.getLength());
	
	this->menu.setFont(std::move(font));
	this->menu.setPalette(palette);
	this->menu.setPosition(93, 61);
	this->menu.setTextColor(72);
	this->menu.setCapitalLetterColor(88);
	
	this->menu.setBottomTextColor(88);
	this->menu.setBottomText("Use UP/DOWN/LETTER to move - ENTER to select");
	
	this->menu.addOption("Begin a new game");
	this->menu.addOption("Restore an old game");
	this->menu.addOption("Ordering Information");
	this->menu.addSpace();
	this->menu.addOption("Instructions");
	this->menu.addOption("Legends and hints!");
	this->menu.addSpace();
	this->menu.addOption("Change game options");
	this->menu.addOption("High scores");
	this->menu.addOption("Preview future levels");
	this->menu.addSpace();
	this->menu.addOption("Quit - rteturn to DOS");
}

void MainMenu::onDetach() {
	LOGI << "MainMenu: onDetach";
}

void MainMenu::onAttach() {
	LOGI << "MainMenu: onAttach";
}

void MainMenu::release() {
	LOGI << "MainMenu: release";
}

void MainMenu::handleEvents(pocus::EventHandler &eventHandler) {
}

void MainMenu::render(pocus::Renderer &renderer) {
	this->menu.render(renderer);
}

void MainMenu::update(float dt) {
}