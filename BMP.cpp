/*
 * BMP.cpp
 *
 *  Created on: Dec 6, 2022
 *      Author: Nathan
 */

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cmath>

#include "BMP.h"

using namespace std;

uint16_t bitsPerPixel = 24;

void writeBITMAPCOREHEADER(ofstream &file, uint16_t width, uint16_t height){
	uint32_t headerSize = 12;
	uint16_t colorPlanes = 1;

	file.write((char*)&headerSize, 4);
	file.write((char*)&width, 2);
	file.write((char*)&height, 2);
	file.write((char*)&colorPlanes, 2);
	file.write((char*)&bitsPerPixel, 2);
}

void write24BitArray(ofstream &file, uint32_t* pixels, uint16_t width, uint16_t height){
	int pad = (width*3)%4;
	uint32_t buffer = 0;
	for(int i = height-1; i >= 0; i--){
		for(int j = 0; j < width; j++){
			file.write(((char*)&pixels[j+width*i]), 1);
			file.write(((char*)&pixels[j+width*i])+1, 1);
			file.write(((char*)&pixels[j+width*i])+2, 1);
		}
		if(pad > 0)
			file.write((char*)&buffer, pad);
	}
}

namespace bmp{
	void writeFile(string fileName, uint32_t* pixels, uint16_t width, uint16_t height){
		uint32_t offset = 26;
		uint32_t size = offset + width*height*3;

		ofstream file;
		file.open(fileName);
		file << "BM";
		file.write((char*)&size, 4);
		file.write("NATD", 4);
		file.write((char*)&offset, 4);
		writeBITMAPCOREHEADER(file, width, height);
		write24BitArray(file, pixels, width, height);
		file.close();
	}
}
