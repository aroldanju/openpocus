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
#include "mainmenu.h"
#include "engine/log.h"
#include "version.h"
#include "engine/data/asset/image.h"
#include "definitions.h"

void MainMenu::onCreate(pocus::data::DataManager& dataManager) {
	LOGI << "MainMenu: create";
	
	pocus::data::Data& data = dataManager.getData();
	
	pocus::data::asset::Font font;
	pocus::data::asset::Palette palette;
	pocus::data::asset::Image bottomImage, topImage;
	pocus::data::asset::Image selectionImage;
	
	pocus::data::DataFile& fontFile = data.fetchFile(DATFILE_FONT_MAIN);
	pocus::data::DataFile& paletteFile = data.fetchFile(DATFILE_PALETTE_MENU);
	pocus::data::DataFile& bottomImageFile = data.fetchFile(DATFILE_IMAGE_BOTTOM);
	pocus::data::DataFile& topImageFile = data.fetchFile(DATFILE_IMAGE_TOP);
	pocus::data::DataFile& selectionImageFile = data.fetchFile(DATFILE_IMAGE_MENU_SELECTION);
	
	font.loadFromStream(fontFile.getContent(), fontFile.getLength());
	palette.loadFromStream(paletteFile.getContent(), paletteFile.getLength());
	bottomImage.loadFromStream(bottomImageFile.getContent(), bottomImageFile.getLength());
	topImage.loadFromStream(topImageFile.getContent(), topImageFile.getLength());
	selectionImage.loadFromStream(selectionImageFile.getContent(), selectionImageFile.getLength());
	
	this->menu.setFont(std::move(font));
	this->menu.setPalette(palette);
	this->menu.setPosition(93, 61);
	this->menu.setTextColor(72);
	this->menu.setCapitalLetterColor(88);
	
	this->menu.setBottomTextColor(88);
	this->menu.setBottomText("Use UP/DOWN/LETTER to move - ENTER to select");
	
	auto selectionTexture = selectionImage.createTexture(palette, 128);
	this->menu.setIndicator(pocus::Animation::createFromTexture(*selectionTexture, 8, 1));
	
	this->menu.addOption("Begin a new game", [] { LOGI << "Not implemented yet."; });
	this->menu.addOption("Restore an old game", [] { LOGI << "Not implemented yet."; });
	this->menu.addOption("Ordering Information", [] { LOGI << "Not implemented yet."; });
	this->menu.addSpace();
	this->menu.addOption("Instructions", [] { LOGI << "Not implemented yet."; });
	this->menu.addOption("Legends and hints!", [] { LOGI << "Not implemented yet."; });
	this->menu.addSpace();
	this->menu.addOption("Change game options", [] { LOGI << "Not implemented yet."; });
	this->menu.addOption("High scores", [] { LOGI << "Not implemented yet."; });
	this->menu.addOption("Preview future levels", [] { LOGI << "Not implemented yet."; });
	this->menu.addSpace();
	this->menu.addOption("Quit - return to DOS", [this] {
		this->fade.start(pocus::Fade::FADE_OUT, [this] {
			setMessage(pocus::State::MESSAGE_QUIT);
		});
	});
	
	this->bottomTexture = bottomImage.createTexture(palette, 128);
	this->topTexture = topImage.createTexture(palette, 128);
	
	this->particles.createStars(palette, SCREEN_WIDTH, SCREEN_HEIGHT, 50);
}

void MainMenu::onDetach() {
	LOGI << "MainMenu: onDetach";
}

void MainMenu::onAttach() {
	LOGI << "MainMenu: onAttach";
	
	this->fade.start(pocus::Fade::FADE_IN);
}

void MainMenu::release() {
	LOGI << "MainMenu: release";
}

void MainMenu::handleEvents(pocus::EventHandler &eventHandler) {
	this->menu.handleEvents(eventHandler);
}

void MainMenu::render(pocus::Renderer &renderer) {
	this->particles.render(renderer);
	renderer.drawTexture(*this->bottomTexture, 0, SCREEN_HEIGHT - this->bottomTexture->getHeight());
	renderer.drawTexture(*this->topTexture, 0, 0);
	this->menu.render(renderer);
	this->fade.render(renderer);
}

void MainMenu::update(float dt) {
	this->fade.update(dt);
	this->particles.update(dt);
	this->menu.update(dt);
}