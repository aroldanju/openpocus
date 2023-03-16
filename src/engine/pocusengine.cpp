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
#include <filesystem>
#include "pocusengine.h"
#include "log.h"
#include "definitions.h"
#include "data/asset/leveltime.h"
#include "data/fatloader.h"
#include "data/asset/leveltileset.h"

using namespace pocus;

PocusEngine::PocusEngine(std::unique_ptr<Renderer> renderer, std::unique_ptr<EventHandler> eventHandler, std::unique_ptr<Audio> audio):
	renderer(std::move(renderer)),
	eventHandler(std::move(eventHandler)),
	audio(std::move(audio))
{
}

int PocusEngine::run(int argc, char **argv) {
	if (!initialize()) {
		LOGE << "Error initializing engine.";
		return 1;
	}

	loop();

	release();

	return 0;
}

bool PocusEngine::initialize() {
	Log::initialize("openpocus.log");

	LOGI << "Initializing OpenPocus...";

	if (!loadConfig()) {
		LOGE << "Engine: error loading config.xml file.";
		return false;
	}
	
	if (!this->renderer || !this->renderer->initialize()) {
		LOGE << "Engine: error initializing renderer.";
		return false;
	}
	
	if (!this->audio || !this->audio->initialize()) {
		LOGE << "Engine: error initializing audio system.";
		return false;
	}

	if (!loadData()) {
		LOGE << "Engine: error loading data.";
		return false;
	}
	
	if (!loadExecutable()) {
		LOGE << "Engine: error loading executable.";
		return false;
	}
	
	createStates(this->stateManager);
	this->stateManager.createStates(getDataManager());
	if (!this->stateManager.getCurrentState()) {
		LOGE << "Engine: no state was selected.";
		return false;
	}
	this->stateManager.changeState(this->stateManager.getStartupState());

	this->running = true;

	return this->running;
}

void PocusEngine::loop() {
	LOGI << "OpenPocus is running";

	const uint32_t fps = 24;
	const uint32_t delay = (1000 / fps);
	const uint32_t fixedFpsDelay = 16;
	float dt = 1.0f;

	while (this->running) {
		Tick startTick = getNow();

		State* state = this->stateManager.getCurrentState();

		while(this->eventHandler->poll()) {
			if (this->eventHandler->isQuit()) {
				this->stateManager.quit(0);
			}
			else {
				if (state) {
					state->handleEvents(*this->eventHandler);
				}
			}
		}

		if (state) {
			state->update(dt);
			processStateMessage(state);
		}

		this->renderer->clear();
		if (state) {
			state->render(*this->renderer);
		}
		this->renderer->render();

		if (this->stateManager.getQuit()) {
			this->running = false;
		}

		dt = processFrameRate(startTick, delay, fixedFpsDelay);
	}
}

float PocusEngine::processFrameRate(const Tick& startTick, int delay, int fixedFpsDelay) {
	wait(1);
	
	uint32_t elapsed = getElapsedTime(startTick);
	if (elapsed < delay) {
		wait(delay - elapsed);
	}
	
	elapsed = getElapsedTime(startTick);
	if (elapsed < fixedFpsDelay) {
		elapsed = fixedFpsDelay - elapsed;
	}
	
	return (float)elapsed / (float)fixedFpsDelay;
}

void PocusEngine::processStateMessage(State* state) {
	if (!state) {
		return;
	}

	const State::Message_t& message = state->message.first;
	switch (message) {
		case State::MESSAGE_QUIT:
			this->stateManager.quit(0);
			break;

		case State::MESSAGE_CHANGE:
			this->stateManager.changeState(reinterpret_cast<char*>(state->message.second));
			break;

		default:
			break;
	}
}

void PocusEngine::release() {
	LOGI << "Releasing OpenPocus...";

	if (auto state = this->stateManager.getCurrentState()) {
		state->onDetach();
	}
	
	if (this->audio) {
		this->audio->release();
		this->audio = nullptr;
	}

	if (this->renderer) {
		this->renderer->release();
	}
}

StateManager& PocusEngine::getStateManager() {
	return this->stateManager;
}

data::DataManager& PocusEngine::getDataManager() {
	return this->dataManger;
}

bool PocusEngine::loadConfig() {
	return this->config.load("../data/config.xml");
}

bool PocusEngine::loadData() {
	std::string path = this->config.getInstallationPath() + "/hocus.dat";
	
	if (!std::filesystem::exists(path)) {
		LOGE << "Data file not found at " << this->config.getInstallationPath();
		return false;
	}
	
	data::Fat fat = pocus::data::FatLoader::loadFromFile(getDatFatFilename());
	
	if (fat.getNumberEntries() == 0) {
		LOGE << "Data FAT file doesn't have any entries";
		return false;
	}
	
	return this->dataManger.getData().loadFromFile(path, fat);
}

bool PocusEngine::loadExecutable() {
	std::string path = this->config.getInstallationPath() + "/hocus.exe";
	
	if (!std::filesystem::exists(path)) {
		LOGE << "Executable file not found at " << this->config.getInstallationPath();
		return false;
	}
	
	data::Fat fat = pocus::data::FatLoader::loadFromFile(getExeFatFilename());
	
	if (fat.getNumberEntries() == 0) {
		LOGE << "Executable FAT file doesn't have any entries";
		return false;
	}
	
	return this->dataManger.getExecutable().loadFromFile(path, fat);
}