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

#ifndef MIDI_H
#define MIDI_H

#include <vector>
#include <memory>
#include <cstdint>
#include "../../sound.h"
#include "asset.h"

namespace pocus::data::asset {

class Midi : public Asset {
public:
	bool loadFromStream(const char* stream, uint32_t length) override;
	void release() override;
	
	std::unique_ptr<Sound> createAsSound();

private:
	std::vector<uint8_t> data;
};

}

#endif // MIDI_H