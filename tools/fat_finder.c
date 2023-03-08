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
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    FILE *file;
    int i = 0;
    uint32_t files;
    char fat[32];
    uint32_t offset;
    uint32_t length;
    
    if (argc < 3) {
    	printf("usage: %s fatfile length\n", argv[0]);
    	return 1;
    }

    printf("Hocus Pocus FAT file finder\n\n");
    
    strcpy(fat, argv[1]);
    length = atoi(argv[2]);

    file = fopen(argv[1], "rb");
    if (!file) {
    	printf("Error opening file %s\n", fat);
    	return 1;
    }
    fread((char*)&files, sizeof(uint32_t), 1, file);
    
    for (i = 0; i < files; i++) {
    	uint32_t fileOffset, fileLength;
    	
    	fread((char*)&fileOffset, sizeof(uint32_t), 1, file);
    	fread((char*)&fileLength, sizeof(uint32_t), 1, file);
    	
    	if (fileLength == length) {
    		printf(" - File found index #%d at %d (%d bytes)\n", i, fileOffset, fileLength);
    	}
    }

    fclose(file);

    return 0;
}
