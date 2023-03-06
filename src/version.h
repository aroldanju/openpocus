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

#ifndef _VERSION_H
#define _VERSION_H

#define VERSION SHAREWARE

#if(VERSION == SHAREWARE)
#define FAT_FILE			"shareware.fat"
enum DatFile {
	DATFILE_PALETTE_GAME = 6,
	DATFILE_IMAGE_HUD = 11
};
#elif(VERSION == REGISTERED)
#define FAT_FILE			"registered.fat"
enum DatFile {
	DATFILE_PALETTE_GAME = 7,
	DATFILE_IMAGE_HUD = 12
};
#endif

#endif //_VERSION_H
