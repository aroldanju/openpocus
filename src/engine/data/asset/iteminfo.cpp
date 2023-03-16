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
#include "iteminfo.h"

using namespace pocus::data::asset;

bool ItemInfo::loadFromStream(const char *stream, uint32_t length) {
	for (int i = 0; i < ITEMS; i++) {
		memcpy(&this->items[i], stream + (i * sizeof(Entry)), sizeof(Entry));
	}
	
	return true;
}

void ItemInfo::release() {
}

const ItemInfo::Entry* ItemInfo::getItems() const {
	return this->items;
}
