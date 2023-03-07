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
#include "pocusengine.h"
#include "log.h"
#include "definitions.h"

using namespace pocus;

PocusEngine::PocusEngine(std::unique_ptr<Renderer> renderer, std::unique_ptr<EventHandler> eventHandler):
	renderer(std::move(renderer)),
	eventHandler(std::move(eventHandler))
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

	if (!this->renderer || !this->renderer->initialize()) {
		LOGE << "Engine: error initializing renderer.";
		return false;
	}

	if (!loadData(this->data)) {
		LOGE << "Engine: error loading data.";
		return false;
	}

	createStates(this->stateManager);
	if (!this->stateManager.getCurrentState()) {
		LOGE << "Engine: no state was selected.";
		return false;
	}
	this->stateManager.createStates(getData());

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

	if (this->renderer) {
		this->renderer->release();
	}
}

StateManager& PocusEngine::getStateManager() {
	return this->stateManager;
}

data::Data& PocusEngine::getData() {
	return this->data;
}
