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

#include <iostream>
#include "image.h"
#include "../../provider/provider.h"
#include "../../log.h"

using namespace pocus::data::asset;

bool Image::loadFromStream(const char *stream, uint32_t length) {
	const char *p = stream;
	
	this->width = *(uint16_t*)(p);
	this->width *= 4;
	p += sizeof(uint16_t);
	
	this->height = *(uint16_t*)(p);
	p += sizeof(uint16_t);
	
	if (this->width * this->height + 4 != length) {
		LOGE << "Image: error loading image (width * height + 4) != length; width = " << width << "; height = " << height << "; length = " << length;
		return false;
	}
	
	this->blocks.resize(this->width * this->height);
	for (int i = 0; i < Image::BLOCKS; i++ )	{
		for (int y = 0; y < this->height; y++)	{
			for (int x = 0; x < this->width; x += 4)	{
				this->blocks[(y * this->width) + (x+i)] = (*(p++));
			}
		}
	}
	
	return true;
}

void Image::release() {

}

std::unique_ptr<pocus::Texture> Image::createTexture(const Palette& palette, uint32_t paletteIndexOffset)	{
	std::unique_ptr<Texture> texture = Provider::provideTexture(this->width, this->height);
	
	for (int i = 0; i < Image::BLOCKS; i++)	{
		for (int y = 0; y < this->height; y++)	{
			for (int x = 0; x < this->width; x++)	{
				const int index = ((y * this->width) + x);
				if (this->blocks[index] != 0) {
					const PaletteColor &color = palette.colors[this->blocks[index] - paletteIndexOffset];
					texture->setPixel(index, color.r, color.g, color.b, 255);
				}
				else {
					texture->setPixel(index, 255, 0, 255, 0);
				}
			}
		}
	}
	
	texture->setColorKey(255, 0, 255);
	
	return std::move(texture);
}