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

#include "sdlsound.h"

using namespace pocus;

void SdlSound::release() {
	if (this->music) {
		Mix_FreeMusic(this->music);
		this->music = nullptr;
	}
	
	if (this->chunk) {
		Mix_FreeChunk(this->chunk);
		this->chunk = nullptr;
	}
}

bool SdlSound::loadFromStream(const char* stream, uint32_t length) {
	SDL_RWops* rw;
	
	rw = SDL_RWFromConstMem((const void*)stream, length);
	
	this->music = Mix_LoadMUS_RW(rw, 1);
	if (!this->music)	{
		rw = SDL_RWFromConstMem((const void*)stream, length);
		this->chunk = Mix_LoadWAV_RW(rw, 1);
		if (!this->chunk)	{
			return false;
		}
	}
	
	return true;
}

void SdlSound::play() {
	if (this->music) {
		Mix_PlayMusic(this->music, 0);
		return;
	}
	
	if (this->chunk) {
		Mix_PlayChannel(-1, this->chunk, 0);
		return;
	}
}

void SdlSound::stop() {
	if (this->music) {
		Mix_HaltMusic();
		return;
	}
	
	if (this->chunk) {
		Mix_HaltChannel(-1);
		return;
	}
}