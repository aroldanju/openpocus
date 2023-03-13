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

#ifndef STATE_H
#define STATE_H

#include <vector>
#include "renderer.h"
#include "eventhandler.h"
#include "data/datamanager.h"

namespace pocus {

class State {
public:
	friend class PocusEngine;

public:
	enum Message_t {
		MESSAGE_NONE,
		MESSAGE_QUIT,
		MESSAGE_CHANGE
	};
	
public:
	virtual void onCreate(data::DataManager& dataManager) = 0;
	virtual void onDetach() = 0;
	virtual void onAttach() = 0;
	virtual void release() = 0;
	virtual void handleEvents(EventHandler &eventHandler) = 0;
	virtual void render(Renderer &renderer) = 0;
	virtual void update(float dt) = 0;

protected:
	void setMessage(const Message_t& type, void* parameter = nullptr) {
		this->message = std::make_pair(type, parameter);
	}

	std::pair<Message_t, void*> message { std::make_pair(MESSAGE_NONE, nullptr) };
};

}

#endif //STATE_H
