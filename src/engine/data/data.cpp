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

#include "data.h"
#include "../log.h"

#include <fstream>
#include <iostream>

using namespace pocus::data;

void Data::release() {
    for (auto& file : this->files) {
        file->release();
    }

    this->files.erase(this->files.begin(), this->files.end());
}

bool Data::loadFromFile(const std::string& path, const Fat& fat) {
    std::string filename = path + "/hocus.dat";

    if (fat.getNumberEntries() == 0) {
    	return false;
    }

    std::ifstream file(filename.c_str(), std::ios_base::binary | std::ios_base::in);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < fat.getNumberEntries(); i++) {
        const FatEntry& fatFileEntry = fat.getEntry(i);
        char *content = new char[fatFileEntry.length];

        file.seekg(fatFileEntry.offset, std::ios_base::beg);
        file.read(content, fatFileEntry.length);

        this->files.push_back(std::make_unique<DataFile>(content, fatFileEntry.length));

        delete[] content;
    }

    file.close();

    LOGD << "Data: " << this->files.size() << " files.";

    return true;
}

DataFile& Data::fetchFile(uint32_t index) {
    if (index < this->files.size()) {
    	return *this->files[index];
    }
	
	throw std::exception();
}
