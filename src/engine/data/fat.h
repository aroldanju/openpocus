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

#ifndef FAT_H
#define FAT_H

#include <vector>
#include <cstdint>
#include <string>

namespace pocus::data {

struct FatEntry {
	uint32_t offset;
	uint32_t length;
};

class Fat {
public:
	bool loadFromFile(const std::string& filename);

	void addEntry(const FatEntry& entry);

	uint32_t getNumberEntries() const;

	const FatEntry& getEntry(uint32_t index) const;
	
private:
	std::vector<FatEntry> entries;
};

}

#endif //FAT_H
