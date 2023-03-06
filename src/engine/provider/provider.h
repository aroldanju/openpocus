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

#ifndef PROVIDER_H
#define PROVIDER_H

#include <memory>
#include "../renderer.h"
#include "../eventhandler.h"
#include "../texture.h"

namespace pocus {

class Provider {
public:
	static std::unique_ptr<Renderer> provideRenderer(const RendererParameters &parameters);
	static std::unique_ptr<EventHandler> provideEventHandler();
	static std::unique_ptr<Texture> provideTexture(uint32_t width = 0, uint32_t height = 0);
};

}

#endif //PROVIDER_H
