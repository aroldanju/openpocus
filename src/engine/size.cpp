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

#include "size.h"

using namespace pocus;

Size::Size(float width, float height):
	width(width), height(height)
{
}

float Size::getWidth() const {
	return this->width;
}

void Size::setWidth(float width) {
	this->width = width;
}

float Size::getHeight() const {
	return this->height;
}

void Size::setHeight(float height) {
	this->height = height;
}

