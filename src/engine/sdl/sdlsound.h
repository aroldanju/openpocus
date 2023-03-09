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

#ifndef SDLSOUND_H
#define SDLSOUND_H

#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif

#include "../sound.h"

namespace pocus {

class SdlSound : public Sound {
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void play() override;
	void release() override;
	void stop() override;

private:
	Mix_Chunk* chunk { nullptr };
	Mix_Music* music { nullptr };
};

}

#endif // SDLSOUND_H
