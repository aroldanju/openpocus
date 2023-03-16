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

#include "point.h"

using namespace pocus;

Point::Point(float x, float y):
	x(x), y(y)
{
}

float Point::getX() const {
	return x;
}

void Point::setX(float x) {
	Point::x = x;
}

float Point::getY() const {
	return y;
}

void Point::setY(float y) {
	Point::y = y;
}

void Point::set(float x, float y) {
	this->x = x;
	this->y = y;
}

Point& Point::operator+=(const Point& point) {
	this->x += point.x;
	this->y += point.y;
	
	return *this;
}

Point& Point::operator+(const Point &point) {
	this->x += point.x;
	this->y += point.y;
	
	return *this;
}

Point& Point::operator-=(const Point& point) {
	this->x -= point.x;
	this->y -= point.y;
	
	return *this;
}

Point& Point::operator-(const Point &point) {
	this->x -= point.x;
	this->y -= point.y;
	
	return *this;
}
