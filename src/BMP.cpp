/*
 * BMP.cpp
 *
 *  Created on: Dec 6, 2022
 *      Author: Nathan
 */

#include <fstream>
#include <cmath>

#include "BMP.h"

using namespace std;

uint16_t bitsPerPixel = 24;
//test
void writeBITMAPCOREHEADER(ofstream &file, int16_t width, int16_t height){
	uint32_t headerSize = 12;
	uint16_t colorPlanes = 1;

	file.write((char*)&headerSize, 4);
	file.write((char*)&width, 2);
	file.write((char*)&height, 2);
	file.write((char*)&colorPlanes, 2);
	file.write((char*)&bitsPerPixel, 2);
}

void write24BitArray(ofstream &file, Image &image){
	int pad = (4-(image.width*3)%4)%4;
	uint32_t buffer = 0;
	for(int i = image.height-1; i >= 0; i--){
		for(int j = 0; j < image.width; j++){
			file.write(((char*)&image.pixels[j][i].c), 1);
			file.write(((char*)&image.pixels[j][i].c)+1, 1);
			file.write(((char*)&image.pixels[j][i].c)+2, 1);
		}
		if(pad > 0)
			file.write((char*)&buffer, pad);
	}
}

namespace bmp{
	void writeFile(string fileName, Image &image){
		uint32_t offset = 26;
		uint32_t size = offset + image.width*image.height*3 + image.height*((4-(image.width*3)%4)%4);

		ofstream file(fileName);
		file << "BM";
		file.write((char*)&size, 4);
		file.write("APRI", 4);
		file.write((char*)&offset, 4);
		writeBITMAPCOREHEADER(file, image.width, image.height);
		write24BitArray(file, image);
		file.close();
	}

	Image readFile(string fileName){
		ifstream file(fileName, ios::binary);

		file.seekg(10);
		uint32_t offset, headerSize;
		file.read((char*)&offset, 4);
		file.read((char*)&headerSize, 4);

		int width, height;
		uint16_t bpp;
		int readWidth = headerSize == 12 ? 2 : 4;

		file.read((char*)&width, readWidth);
		file.read((char*)&height, readWidth);
		file.ignore(2);

		file.read((char*)&bpp, 2);
		if(bpp != 24)
			throw (uint32_t)bpp;

		if(headerSize > 30){
			file.seekg(30);
			uint32_t compression;
			file.read((char*)&compression, 4);
			if(compression != 0)
				throw "compressed";
		}

		Image image(width, height);

		file.seekg(offset);
		int pad = (4-(width*3)%4)%4;
		for(int i = height-1; i >= 0; i--){
			for(int j = 0; j < width; j++){
				uint32_t c;
				file.read((char*)&c, 3);
				image.pixels[j][i] = Color(c);
			}
			file.ignore(pad);
		}
		return image;
	}
}
