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

#include "introsplash.h"
#include "engine/data/asset/pcx.h"
#include "engine/data/asset/midi.h"
#include "version.h"
#include "engine/log.h"
#include "engine/data/asset/voc.h"
#include "engine/musicplayer.h"
#include "definitions.h"

void IntroSplash::onCreate(pocus::data::Data& data) {
	pocus::data::asset::Pcx introSplashImage;
	pocus::data::asset::Midi titleMusicMidi;
	pocus::data::asset::Voc laughSoundVoc;
	
	pocus::data::DataFile& introSplashFile = data.fetchFile(DATFILE_SPLASH_INTRO);
	pocus::data::DataFile& titleMusicFile = data.fetchFile(DATFILE_MUSIC_INTRO);
	pocus::data::DataFile& laughSoundFile = data.fetchFile(DATFILE_VOC_LAUGH);
	
	introSplashImage.loadFromStream(introSplashFile.getContent(), introSplashFile.getLength());
	titleMusicMidi.loadFromStream(titleMusicFile.getContent(), titleMusicFile.getLength());
	laughSoundVoc.loadFromStream(laughSoundFile.getContent(), laughSoundFile.getLength());
	
	this->backgroundImage = introSplashImage.createTexture();
	this->laughSound = laughSoundVoc.createAsSound();
	this->backgroundMusic = titleMusicMidi.createAsSound();
}

void IntroSplash::onDetach() {
	LOGI << "IntroSplash: onDetach";
}

void IntroSplash::onAttach() {
	LOGI << "IntroSplash: onAttach";
	
	this->fade.start(pocus::Fade::FADE_IN);
	this->startTick = pocus::getNow();
	this->laughSound->play();
	
	pocus::MusicPlayer::getInstance().play(std::move(this->backgroundMusic));
}

void IntroSplash::release() {
	LOGI << "IntroSplash: release";
}

void IntroSplash::handleEvents(pocus::EventHandler &eventHandler) {
	if (!this->fade.isRunning() && pocus::getElapsedTime(this->startTick) >= IntroSplash::MIN_TIME) {
		if (eventHandler.isAnyButtonDown()) {
			this->fade.start(pocus::Fade::FADE_OUT, [this] {
				setMessage(pocus::State::MESSAGE_CHANGE, (void*)STATE_MENU_MAIN);
			});
		}
	}
}

void IntroSplash::render(pocus::Renderer &renderer) {
	renderer.drawTexture(*this->backgroundImage, 0, 0);
	this->fade.render(renderer);
}

void IntroSplash::update(float dt) {
	this->fade.update(dt);
	
	if (pocus::getElapsedTime(this->startTick) >= IntroSplash::TIME && !this->fade.isRunning()) {
		this->fade.start(pocus::Fade::FADE_OUT, [this]{
			setMessage(pocus::State::MESSAGE_CHANGE, (void*)STATE_MENU_MAIN);
		});
	}
}