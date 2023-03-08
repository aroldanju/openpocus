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

#include "voc.h"
#include "../../provider/provider.h"

using namespace pocus::data::asset;

bool Voc::loadFromStream(const char *stream, uint32_t length) {
	this->data.resize(length);
	for (uint32_t i = 0; i < length; i++) {
		this->data[i] = stream[i];
	}
	
	return true;
}

void Voc::release() {
	this->data.erase(this->data.begin(), this->data.end());
}

std::unique_ptr<pocus::Sound> Voc::createAsSound() {
	std::unique_ptr<Sound> sound = Provider::provideSound();
	sound->loadFromStream(reinterpret_cast<char*>(this->data.data()), data.size());
	return std::move(sound);
}
