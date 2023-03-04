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

#include "pocusengine.h"
#include "log.h"

#include <chrono>
#include <thread>

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

	createStates(this->stateManager);
	if (!this->stateManager.getCurrentState()) {
		LOGE << "Engine: no state was selected.";
		return false;
	}

	this->running = true;

	return this->running;
}

void PocusEngine::loop() {
	LOGI << "OpenPocus is running";

	while (this->running) {
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
			state->update(1.0f);
		}

		this->renderer->clear();
		if (state) {
			state->render(*this->renderer);
		}

		if (this->stateManager.getQuit()) {
			this->running = false;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
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