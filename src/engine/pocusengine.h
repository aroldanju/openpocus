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

#ifndef POCUSENGINE_H
#define POCUSENGINE_H

#include <memory>

#include "statemanager.h"
#include "renderer.h"
#include "eventhandler.h"
#include "data/data.h"
#include "definitions.h"

namespace pocus {

class PocusEngine {
public:
	PocusEngine(std::unique_ptr<Renderer> renderer, std::unique_ptr<EventHandler> eventHandler);
	virtual ~PocusEngine() = default;

	int run(int argc, char* argv[]);

protected:
	virtual void createStates(StateManager& stateManager) = 0;
	virtual bool loadData(data::Data& data) = 0;

	StateManager& getStateManager();
	data::Data& getData();

private:
	bool initialize();
	void loop();
	void release();
	
	void processStateMessageQueue(State* state);
	float processFrameRate(const Tick& startTick, int delay, int fixedFpsDelay);

private:
	StateManager stateManager;
	std::unique_ptr<Renderer> renderer;
	std::unique_ptr<EventHandler> eventHandler;
	data::Data data;

	bool running { false };
};

}


#endif //POCUSENGINE_H
