#include "ImageExtractor.h"
#include <iostream>
ImageExtractor::ImageExtractor(int _initialIndex, int _width, int _height, BaseImage _header_Image_Source) {

	image_initial_index = _initialIndex;
	image_width = _width;
	image_height = _height;

	imageFile = new BaseImages(_header_Image_Source);
	
}

ImageExtractor::~ImageExtractor()
{
	delete imageFile;
}

int ImageExtractor::GetWidth() {
	return image_width;
}

int ImageExtractor::GetHeight() {
	return image_height;
}

BaseImages* ImageExtractor::GetBase()
{
	return imageFile;
}

unsigned int ImageExtractor::GetBlockPixel(int _offset)
{
	unsigned int color = imageFile->GetBaseArray()[image_initial_index + _offset];
	return color;
}

void ImageExtractor::Set_Initial_Index(unsigned int _newIndex)
{
	image_initial_index = _newIndex;
}
