/*
 * BMP.h
 *
 *  Created on: Dec 6, 2022
 *      Author: Nathan
 */
#include <string>

#include "priori/Graphical/Image.h"

#ifndef BMP_H_
#define BMP_H_

namespace priori{
	void writebmp(std::string fileName, Image &image);
	Image readbmp(std::string fileName);
}

#endif /* BMP_H_ */
