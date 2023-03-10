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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

const uint16_t paletteSize = 384;

struct color {
	uint8_t r, g, b;
};

int main(int argc, char* argv[]) {
    FILE *file;
    struct color colors[128];
    int i;
	
    file = fopen(argv[1], "rb");
    if (!file) {
    	printf("Error opening palette file %s\n", argv[1]);
    	return 1;
    }
    fread((void*)colors, paletteSize, 1, file);
    fclose(file);

	for (i = 0; i < 128; i++)	{
		colors[i].r = colors[i].r << 2;
		colors[i].g = colors[i].g << 2;
		colors[i].b = colors[i].b << 2;
	}
	
	SDL_Surface* surface = SDL_CreateRGBSurface(0, 16, 8, 32, 0, 0, 0, 0);
	Uint32* pixels = (Uint32*)surface->pixels;
	
	for (i = 0; i < 128; i++) {
		pixels[i] = SDL_MapRGB(surface->format, colors[i].r, colors[i].g, colors[i].b);
	}
	
	SDL_SaveBMP(surface, "palette.bmp");
	SDL_FreeSurface(surface);

    return 0;
}
