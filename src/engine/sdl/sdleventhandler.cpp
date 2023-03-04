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

#include "sdleventhandler.h"

using namespace pocus;

SdlEventHandler::SdlEventHandler() {
    // Mapping
    this->buttonMapping[BUTTON_FIRE] = SDLK_LALT;
    this->buttonMapping[BUTTON_JUMP] = SDLK_LCTRL;
    this->buttonMapping[BUTTON_LEFT] = SDLK_LEFT;
    this->buttonMapping[BUTTON_RIGHT] = SDLK_RIGHT;
    this->buttonMapping[BUTTON_UP] = SDLK_UP;
    this->buttonMapping[BUTTON_DOWN] = SDLK_DOWN;
    this->buttonMapping[BUTTON_PAUSE] = SDLK_p;
}

bool SdlEventHandler::isButtonDown(const Button_t &button) {
    if (this->event.type == SDL_KEYDOWN) {
        auto iterator = buttonMapping.find(button);
        if (iterator != this->buttonMapping.end()) {
            if (this->event.key.keysym.sym == iterator->second) {
                return true;
            }
        }
    }

    return false;
}

bool SdlEventHandler::isButtonUp(const Button_t &button)   {
    if (this->event.type == SDL_KEYUP) {
        auto iterator = buttonMapping.find(button);
        if (iterator != this->buttonMapping.end()) {
            if (this->event.key.keysym.sym == iterator->second) {
                return true;
            }
        }
    }

    return false;
}


int SdlEventHandler::poll() {
    return SDL_PollEvent(&this->event);
}

bool SdlEventHandler::isQuit() {
    return this->event.type == SDL_QUIT;
}

bool SdlEventHandler::isAnyButtonDown() const {
    return (this->event.type == SDL_KEYDOWN);
}