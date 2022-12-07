/*
 * BMP.h
 *
 *  Created on: Dec 6, 2022
 *      Author: Nathan
 */
#include <string>

#ifndef BMP_H_
#define BMP_H_


namespace bmp{
	void writeFile(std::string fileName, uint32_t* pixels, uint16_t width, uint16_t height);
}


#endif /* BMP_H_ */
