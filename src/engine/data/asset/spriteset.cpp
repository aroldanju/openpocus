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

#include <cstring>
#include "spriteset.h"
#include "../../provider/provider.h"

using namespace pocus::data::asset;

bool SpriteSet::loadFromStream(const char *stream, uint32_t length) {
	const char* buffer = stream;
	const uint32_t offset = *(uint32_t*)stream;
	const uint32_t numSprites = offset / sizeof(Sprite::Header);
	
	for (int i = 0; i < numSprites; i++) {
		Sprite sprite = loadSprite(stream);
		sprite.data = buffer;
		this->sprites.push_back(sprite);
		stream += sizeof(Sprite::Header);
	}
	
	return true;
}

Sprite SpriteSet::loadSprite(const char *buffer) {
	Sprite sprite {};
	Sprite::Header& header = sprite.header;
	
	header.offset = *(uint32_t*)buffer;
	buffer += sizeof(uint32_t);
	
	memcpy(header.name, buffer, 22);
	buffer += 22;
	
	header.width4 = *(uint16_t *) buffer;
	header.width4 *= 4;
	buffer += sizeof(uint16_t);
	
	header.height = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.standFrame = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.standFrame2 = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.walkFrameBegin = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.walkFrameEnd = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.jumpFrame = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.fallFrame = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.shootDashFrameBegin = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.shootDashFrameEnd = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.projectileWidth4 = *(uint16_t *) buffer;
	header.projectileWidth4 *= 4;
	buffer += sizeof(uint16_t);
	
	header.projectileHeight = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.projectileY = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.projectileFrame = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.projectileUnknown = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.pixelsOffset = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	header.pixelsSize = *(uint16_t *) buffer;
	buffer += sizeof(uint16_t);
	
	for (unsigned short & i : header.layoutStartE) {
		i = *(uint16_t *) buffer;
		buffer += sizeof(uint16_t);
	}
	
	for (unsigned short & i : header.layoutStartW) {
		i = *(uint16_t *) buffer;
		buffer += sizeof(uint16_t);
	}
	
	for (unsigned short & i : header.pixelStartsE) {
		i = *(uint16_t *) buffer;
		buffer += sizeof(uint16_t);
	}
	for (unsigned short & i : header.pixelStartsW) {
		i = *(uint16_t *) buffer;
		buffer += sizeof(uint16_t);
	}
	
	return sprite;
}

void SpriteSet::release() {

}

Sprite& SpriteSet::getSprite(uint32_t index) {
	return this->sprites[index];
}

std::unique_ptr<pocus::Texture> Sprite::createAsTexture(const Palette &palette) {
	const uint32_t spriteSetWidth = 320;
	
	std::unique_ptr<Texture> texture = Provider::provideTexture(spriteSetWidth, this->header.height * 2);
	texture->fill(255, 0, 255);
	
	for (int row = 0; row < Sprite::ROWS; row++) {
		for (int spriteNumber = 0; spriteNumber < Sprite::COLUMNS; spriteNumber++) {
			const char *buffer = this->data;
			
			uint32_t layoutOff, pixelOff;
			uint8_t* layoutData, *pixelData;
			int layoutDataPtr, pixelDataPtr, imagePtr;
			uint8_t layoutFlag, transparencyType;
			uint32_t moveBy;
			
			auto tempTexture = Provider::provideTexture(spriteSetWidth, this->header.height);
			tempTexture->fill(255, 0, 255);
			
			if (row == 0) {
				layoutOff = this->header.layoutStartE[spriteNumber];
				pixelOff = this->header.pixelStartsE[spriteNumber] * 4;
			}
			else {
				layoutOff = this->header.layoutStartW[spriteNumber];
				pixelOff = this->header.pixelStartsW[spriteNumber] * 4;
			}
			
			// Max frames
			if (pixelOff >= this->header.pixelsSize || layoutOff >= this->header.pixelsOffset) {
				break;
			}
			
			layoutData = (uint8_t*)(buffer + this->header.offset + layoutOff);
			pixelData = (uint8_t*)(buffer + this->header.offset + this->header.pixelsOffset + pixelOff);
			layoutDataPtr = pixelDataPtr = imagePtr = transparencyType = 0;
			
			for (int i = 0; i < this->header.pixelsOffset; i++) {
				layoutFlag = layoutData[layoutDataPtr++];
				
				switch (layoutFlag) {
					case 0:
						transparencyType = layoutData[layoutDataPtr++];
						imagePtr = 0;
						break;
						
					case 1:
						moveBy = layoutData[layoutDataPtr] + layoutData[layoutDataPtr + 1] * 256;
						layoutDataPtr += 2;
						imagePtr += moveBy * 4;
						break;
						
					case 2:
						for (int j = 0; j < 4; j++) {
							if (((transparencyType >> j) & 1) == 1) {
								const PaletteColor& color = palette.colors[pixelData[pixelDataPtr + j]];
								tempTexture->setPixel(imagePtr + j, color.r, color.g, color.b, 255);
							}
						}
						
						imagePtr += 4;
						pixelDataPtr += 4;
						break;
						
					case 3:
						i = this->header.pixelsOffset;
						break;
				}
			}
			
			texture->paste(*tempTexture, 0, 0, spriteNumber * this->header.width4, row * this->header.height);
		}
	}
	
	texture->setColorKey(255, 0, 255);
	
	return std::move(texture);
}
