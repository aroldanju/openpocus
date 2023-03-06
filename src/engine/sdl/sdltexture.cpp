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

#include "sdltexture.h"

using namespace pocus;

SdlTexture::SdlTexture() :
	surface(nullptr),
	texture(nullptr)
{
}

SdlTexture::~SdlTexture() {
	if (this->surface) {
		SDL_FreeSurface(this->surface);
		this->surface = nullptr;
	}
	
	if (this->texture) {
		SDL_DestroyTexture(this->texture);
		this->texture = nullptr;
	}
}

bool SdlTexture::createBlank(uint32_t width, uint32_t height) {
	this->surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
	if (!this->surface )	{
		return false;
	}
	
	return true;
}

void SdlTexture::setPixel(uint32_t index, uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	Uint32* pixels = (Uint32*)this->surface->pixels;
	pixels[index] = SDL_MapRGB(this->surface->format,red,green,blue);
}

uint32_t SdlTexture::getWidth() const {
	return this->surface->w;
}

uint32_t SdlTexture::getHeight() const {
	return this->surface->h;
}

bool SdlTexture::isReady() const {
	return this->texture != nullptr;
}