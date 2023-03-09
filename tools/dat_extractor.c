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

int main(int argc, char* argv[]) {
    FILE *file;
    uint32_t offset, length;
    char* data;

	offset = atoi(argv[1]);
	length = atoi(argv[2]);
	
	data = (char*)malloc(sizeof(char) * length);

    file = fopen("hocus.dat", "rb");
    fseek(file, offset, SEEK_SET);
    fread((void*)data, length, 1, file);
    
    fclose(file);

    file = fopen("output.dat", "wb");
    fwrite((void*)data, length, 1, file);
    fclose(file);
    
    free(data);

    return 0;
}
