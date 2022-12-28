/*
 * Test.cpp
 *
 *  Created on: Dec 12, 2022
 *      Author: Nathan
 */
#include <iostream>

#include "../BMPIO.h"

using namespace priori;

int main(){
	Image img = readbmp("priori/BMPLibrary/tests/TestIn.bmp");
	writebmp("priori/BMPLibrary/tests/TestOut.bmp", img);
}
