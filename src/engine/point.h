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

#ifndef POINT_H
#define POINT_H

namespace pocus {

class Point {
public:
	Point() = default;
	Point(float x, float y);
	
	[[nodiscard]] float getX() const;
	void setX(float x);
	[[nodiscard]] float getY() const;
	void setY(float y);
	
	void set(float x, float y);
	
	Point& operator+=(const Point& point);
	Point& operator+(const Point& point);
	Point& operator-(const Point& point);
	Point& operator-=(const Point& point);

private:
	float x { .0f };
	float y { .0f };
};

}

#endif //POINT_H
