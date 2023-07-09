#include "BaseImages.h"

BaseImages::BaseImages(BaseImage _hfile)
{
	base_image = _hfile;
	
	InitializeImageReference();
}

void BaseImages::InitializeImageReference()
{


	switch(base_image)
	{
	case floor_tiles:
		
		size = tiles_12_numpixels;
		width = tiles_12_width;
		image_pointer = tiles_12_pixels;
		height = tiles_12_height;

		break;
	case fire:
		size = fire_01_numpixels;
		width = fire_01_width;
		image_pointer = fire_01_pixels;
		height = fire_01_height;
		break;
	case skull:
		size = spelk2_numpixels;
		width = spelk2_width;
		image_pointer = spelk2_pixels;
		height = spelk2_height;
		break;
	}

}

const unsigned int* BaseImages::GetBaseArray() {

	return image_pointer;
}

unsigned int BaseImages::GetBaseWidth() {
	return width;
}

unsigned int BaseImages::GetBaseHeight() {
	return height;
}