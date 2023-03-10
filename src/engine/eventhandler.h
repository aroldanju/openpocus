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

#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

namespace pocus {

enum Button_t {
	BUTTON_RIGHT = 0,
	BUTTON_LEFT = 1,
	BUTTON_DOWN = 2,
	BUTTON_UP = 3,
	BUTTON_FIRE = 4,
	BUTTON_JUMP = 5,
    BUTTON_PAUSE = 6,
	BUTTON_SELECTION = 7
};

class EventHandler {
public:
	virtual int poll() = 0;

	virtual bool isButtonDown(const Button_t &button) = 0;
	virtual bool isButtonUp(const Button_t &button) = 0;
	virtual bool isQuit() = 0;

	virtual bool isAnyButtonDown() const = 0;

};

}

#endif //EVENTHANDLER_H
