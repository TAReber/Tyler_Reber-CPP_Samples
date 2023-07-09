#pragma once

#include "BaseImages.h"


//The goal of this class is to calculate and store simple values required to target a group of pixels in a 1D array.
//The beginning index of a pixel, the number of pixels to iterate to the right, and the number of pixels to iterate down.

// I would like to create an object with these values, but also have a variable to tell it what file, or array it should look into.
// I think a variable to store a pointer to the referenced file should suffice. But I see no point referencing the same pointers every time I need to draw a block,
// So I will make a class to do that reference for me.

//Thus, I am able to easily target a block of pixel values(image) from the whole array(spritesheet). I will call the single Large image BaseImage and create a variable pointer to it.

class ImageExtractor
{	
	/// <summary>
	/// Initial index is the index which I begin to reference a block of pixels from.
	/// Every Array Image is unique and I suspect I will have to calculate hardcoded values because the target image could start at any point in the array.
	/// </summary>
	unsigned int image_initial_index;

	int image_width;
	int image_height;

	BaseImages* imageFile;

public:

	//Constructor
	ImageExtractor(int _initialIndex, int _width, int height, BaseImage _header_Image_Source);// : image_initial_index(_initialIndex), image_width(_width), image_height(height);
	~ImageExtractor();
	/// <summary>
	/// I need to Reference the draw area of the window.
	/// </summary>
	/// <param name="_window"></param>
	//void printImage(unsigned int* _window, int _initial_draw_index);

	int GetWidth();
	int GetHeight();
	BaseImages* GetBase();

	unsigned int GetBlockPixel(int _offset);

	/// <summary>
	/// Used by Animator to set the index and iterate to the next image.
	/// </summary>
	/// <param name="_newIndex"></param>
	void Set_Initial_Index(unsigned int _newIndex);

};

