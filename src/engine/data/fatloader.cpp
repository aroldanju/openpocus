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

#include "fatloader.h"

#include <fstream>

using namespace pocus::data;

Fat FatLoader::loadFromFile(const std::string &filename) {
	Fat fat;
	uint32_t files;

	std::ifstream file(filename.c_str(), std::ios_base::binary | std::ios_base::in);
	if (file) {
		file.read((char*)&files, sizeof(uint32_t));

		for (uint32_t i = 0; i < files; i++) {
			FatEntry entry { 0, 0 };
			file.read((char*)&entry.offset, sizeof(uint32_t));
			file.read((char*)&entry.length, sizeof(uint32_t));
			fat.addEntry(entry);
		}

		file.close();
	}

	return fat;
}