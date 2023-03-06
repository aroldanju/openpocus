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

#include "provider.h"
#include "../sdl/sdlrenderer.h"
#include "../sdl/sdleventhandler.h"
#include "../sdl/sdltexture.h"

using namespace pocus;

std::unique_ptr<Renderer> Provider::provideRenderer(const RendererParameters &parameters) {
	return std::make_unique<SdlRenderer>(parameters);
}

std::unique_ptr<EventHandler> Provider::provideEventHandler() {
	return std::make_unique<SdlEventHandler>();
}

std::unique_ptr<Texture> Provider::provideTexture(uint32_t width, uint32_t height) {
	auto texture = std::make_unique<SdlTexture>();
	
	if (width != 0 && height != 0) {
		texture->createBlank(width, height);
	}
	
	return std::move(texture);
}
