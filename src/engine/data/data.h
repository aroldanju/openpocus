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

#ifndef DATA_H
#define DATA_H

#include "datafile.h"
#include "fat.h"

#include <string>
#include <vector>

namespace pocus::data {

class Data {
public:
	void release();

	bool loadFromFile(const std::string &path, const Fat& fat);

	DataFile& fetchFile(uint32_t index);

private:
	std::vector<std::unique_ptr<DataFile>> files;
};

}

#endif //DATA_H
