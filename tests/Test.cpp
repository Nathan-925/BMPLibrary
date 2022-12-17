/*
 * Test.cpp
 *
 *  Created on: Dec 12, 2022
 *      Author: Nathan
 */
#include <iostream>

#include "../BMPIO.h"

using namespace std;

int main(){
	Image img = bmp::readFile("tests/TestIn.bmp");
	bmp::writeFile("tests/TestOut.bmp", img);
}
