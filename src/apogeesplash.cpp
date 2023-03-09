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

#include "apogeesplash.h"
#include "engine/log.h"
#include "engine/data/asset/pcx.h"
#include "version.h"
#include "engine/data/asset/midi.h"

void ApogeeSplash::onCreate(pocus::data::Data& data) {
	pocus::data::asset::Pcx apogeeSplashImage;
	pocus::data::asset::Midi apogeeMusicMidi;
	
	pocus::data::DataFile& apogeeSplashFile = data.fetchFile(DATFILE_SPLASH_APOGEE);
	pocus::data::DataFile& apogeeMusicFile = data.fetchFile(DATFILE_MUSIC_APOGEE);
	
	apogeeSplashImage.loadFromStream(apogeeSplashFile.getContent(), apogeeSplashFile.getLength());
	apogeeMusicMidi.loadFromStream(apogeeMusicFile.getContent(), apogeeMusicFile.getLength());
	
	this->backgroundImage = apogeeSplashImage.createTexture();
	this->backgroundMusic = apogeeMusicMidi.createAsSound();
}

void ApogeeSplash::onDetach() {
	LOGI << "StateGame: onDetach";
}

void ApogeeSplash::onAttach() {
	LOGI << "StateGame: onAttach";
	
	this->fade.start(pocus::Fade::FADE_IN);
	this->startTick = pocus::getNow();
	this->backgroundMusic->play();
}

void ApogeeSplash::release() {
	LOGI << "StateGame: release";
}

void ApogeeSplash::handleEvents(pocus::EventHandler &eventHandler) {
	if (!this->fade.isRunning()) {
		this->fade.start(pocus::Fade::FADE_OUT, [this]{
			this->backgroundMusic->stop();
			setMessage(pocus::State::MESSAGE_CHANGE, (void*)"intro_splash");
		});
	}
}

void ApogeeSplash::render(pocus::Renderer &renderer) {
	renderer.drawTexture(*this->backgroundImage, 0, 0);
	this->fade.render(renderer);
}

void ApogeeSplash::update(float dt) {
	this->fade.update(dt);
	
	if (pocus::getElapsedTime(this->startTick) >= ApogeeSplash::TIME && !this->fade.isRunning()) {
		this->fade.start(pocus::Fade::FADE_OUT, [this]{
			this->backgroundMusic->stop();
			setMessage(pocus::State::MESSAGE_CHANGE, (void*)"intro_splash");
		});
	}
}