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

#ifndef ITEMINFO_H
#define ITEMINFO_H

#include <cstdint>
#include "asset.h"

namespace pocus::data::asset {

class ItemInfo : public Asset {
public:
	enum { ITEMS = 23 };
	
	struct Entry {
		char name[36];
		uint16_t score;
		uint8_t heal;
		uint8_t firePower;
		uint8_t type;
		uint8_t padding;
	};
	
	enum Type_t {
		ITEM = 0x00,
		CRYSTAL = 0x01,
		WIZARD = 0x0a,
		SPAWN = 0xff
	};
	
public:
	bool loadFromStream(const char *stream, uint32_t length) override;
	void release() override;
	
	[[nodiscard]] const Entry *getItems() const;

private:
	Entry items[ITEMS];
};

}

#endif // ITEMINFO_H
