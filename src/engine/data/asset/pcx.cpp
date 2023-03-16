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

#include <memory>
#include "pcx.h"
#include "../../provider/provider.h"

using namespace pocus::data::asset;

bool Pcx::loadFromStream(const char *stream, uint32_t length) {
	this->data.resize(length);
	for (uint32_t i = 0; i < length; i++) {
		this->data[i] = stream[i];
	}
}

void Pcx::release() {

}

std::unique_ptr<pocus::Texture> Pcx::createTexture() {
	std::unique_ptr<Texture> texture = Provider::provideTexture();
	texture->loadFromStream(reinterpret_cast<char*>(this->data.data()), data.size());
	return std::move(texture);
}