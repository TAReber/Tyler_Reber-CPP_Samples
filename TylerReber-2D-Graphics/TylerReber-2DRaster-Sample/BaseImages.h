#pragma once

#include "tiles_12.h"
#include "fire_01.h"
#include "spelk2.h"

enum BaseImage
{
	floor_tiles = 0,
	fire = 1,
	skull = 2

};

class BaseImages
{
	BaseImage base_image;
	const unsigned int* image_pointer;
	unsigned int size;
	unsigned int width;
	unsigned int height;

public:

	BaseImages(BaseImage _hfile);
	void InitializeImageReference();


	const unsigned int* GetBaseArray();
	unsigned int GetBaseWidth();
	unsigned int GetBaseHeight();
};




