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

#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

namespace pocus {

class Player {
public:
	[[nodiscard]] uint8_t getCrystals() const;
	void setCrystals(uint8_t crystals);
	[[nodiscard]] uint32_t getScore() const;
	void setScore(uint32_t score);
	[[nodiscard]] uint8_t getHealth() const;
	void setHealth(uint8_t health);
	[[nodiscard]] uint8_t getLevel() const;
	void setLevel(uint8_t level);
	[[nodiscard]] uint8_t getEpisode() const;
	void setEpisode(uint8_t episode);
	[[nodiscard]] bool hasSilverKey() const;
	void setSilverKey(bool silverKey);
	[[nodiscard]] bool hasGoldenKey() const;
	void setGoldKey(bool goldKey);

private:
	uint8_t crystals;
	uint32_t score;
	uint8_t health;
	uint8_t level;
	uint8_t episode;
	bool silverKey, goldKey;
};

}

#endif //PLAYER_H
