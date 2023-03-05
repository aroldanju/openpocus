/*  
 *  Copyright (c) 2021, Amador Roldán. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstring>
#include "datafile.h"

using namespace pocus::data;

DataFile::DataFile(const char *content, uint32_t length) :
    content(nullptr),
    length(length)
{
    this->content = new char[length];
    memcpy(this->content, content, length);
}

DataFile::~DataFile() {
    release();
}

void DataFile::release() {
    if (this->content) {
        delete[] this->content;
        this->content = nullptr;
    }
}

char *DataFile::getContent() const {
    return this->content;
}

uint32_t DataFile::getLength() const {
    return this->length;
}