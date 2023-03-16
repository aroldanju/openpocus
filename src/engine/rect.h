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

#ifndef RECT_H
#define RECT_H

#include "size.h"
#include "point.h"

namespace pocus {

class Rect {
public:
	Rect(const Point& position, const Size& size);
	Rect() = default;
	
	[[nodiscard]] const Point& getPosition() const;
	[[nodiscard]] const Size& getSize() const;
	void setPosition(const Point& position);
	void setSize(const Size& size);
	
private:
	Point position { .0f, .0f };
	Size size { .0f, .0f };
};

}

#endif // RECT_H
