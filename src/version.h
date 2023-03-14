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
#define FAT_FILE			"../data/shareware.fat"
#define EXE_FAT_FILE		"../data/shareware_exe.fat"
#define EPISODES 			1
#define STAGES				9
enum DatFile {
	DATFILE_FONT_MAIN = 0,
	DATFILE_SPLASH_APOGEE = 1,
	DATFILE_SPLASH_INTRO = 2,
	DATFILE_PALETTE_GAME = 6,
	DATFILE_PALETTE_MENU = 7,
	DATFILE_IMAGE_BOTTOM = 8,
	DATFILE_IMAGE_TOP = 9,
	DATFILE_IMAGE_STUFF = 10,
	DATFILE_IMAGE_HUD = 11,
	DATFILE_IMAGE_MENU_SELECTION = 13,
	DATFILE_PALETTE_BACKGROUND_01 = 62,
	DATFILE_IMAGE_BACKGROUND_01 = 66,
	DATFILE_TILESET_01 = 70,
	DATFILE_SPRITE_SET = 83,
	DATFILE_LEVELS_START = 84,
	DATFILE_MUSIC_APOGEE = 201,
	DATFILE_MUSIC_01 = 202,
	DATFILE_MUSIC_02 = 203,
	DATFILE_MUSIC_INTRO = 204,
	DATFILE_MUSIC_03 = 205,
	DATFILE_MUSIC_04 = 206,
	DATFILE_MUSIC_05 = 207,
	DATFILE_VOC_LAUGH = 212
};
enum ExeFile {
	EXEFILE_LIMIT_TIME = 0,
	EXEFILE_ITEMS = 1,
	EXEFILE_TILESETS = 2,
	EXEFILE_BACKGROUNDS = 3,
	EXEFILE_MUSIC = 4,
	EXEFILE_ELEVATORS = 5
};
enum Sprite_t {
	SPRITE_HOCUS = 0,
};
#elif(VERSION == REGISTERED)
#define FAT_FILE			"registered.fat"
#define EXE_FAT_FILE		"regeistered_exe.fat"
#define EPISODES 			4
#define STAGES				9
enum DatFile {
	DATFILE_FONT_MAIN = 0,
	DATFILE_SPLASH_APOGEE = 1,
	DATFILE_SPLASH_INTRO = 2,
	DATFILE_PALETTE_GAME = 7,
	DATFILE_PALETTE_MENU = 8,,
	DATFILE_IMAGE_BOTTOM = 9,
	DATFILE_IMAGE_TOP = 10,
	DATFILE_IMAGE_STUFF = 11,
	DATFILE_IMAGE_HUD = 12,
	DATFILE_IMAGE_MENU_SELECTION = 14,
	DATFILE_PALETTE_BACKGROUND_01 = 73,
	DATFILE_IMAGE_BACKGROUND_01 = 89,
	DATFILE_TILESET_01 = 105,
	DATFILE_SPRITE_SET = 130,
	DATFILE_LEVELS_START = 131,
	DATFILE_MUSIC_APOGEE = 599,
	DATFILE_MUSIC_01 = 600,
	DATFILE_MUSIC_02 = 601,
	DATFILE_MUSIC_INTRO = 602,
	DATFILE_MUSIC_03 = 603,
	DATFILE_MUSIC_04 = 604,
	DATFILE_MUSIC_05 = 605,
	DATFILE_VOC_LAUGH = 611,
};
enum ExeFile {
	EXEFILE_LIMIT_TIME = 0,
	EXEFILE_ITEMS = 1,
	EXEFILE_TILESETS = 2,
	EXEFILE_BACKGROUNDS = 3,
	EXEFILE_MUSIC = 4,
	EXEFILE_ELEVATORS = 5
};
enum Sprite_t {
	SPRITE_HOCUS = 0,
};
#endif

#endif //_VERSION_H
