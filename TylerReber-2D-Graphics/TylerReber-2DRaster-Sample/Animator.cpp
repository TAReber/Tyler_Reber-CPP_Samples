#include "Animator.h"
#include <iostream>


Animator::Animator(int _initialIndex, int _width, int height, BaseImage _header_Image_Source) : ImageExtractor(_initialIndex, _width, height, _header_Image_Source)
{
	current_image = _initialIndex;
	columns = GetBase()->GetBaseWidth() / _width;
	rows = GetBase()->GetBaseHeight() / height;

	//max_image_num assumes the 1d array was made form a sprite with no missing slots.
	max_image_num = GetBase()->GetBaseWidth() / _width * GetBase()->GetBaseHeight() / height;
}

Animator::~Animator()
{
	
}

int Animator::GetCurrentImage()
{
	return current_image;
}

int Animator::GetMaxImage()
{
	return max_image_num;
}

void Animator::Animate_Next_Frame()
{
	//Increments the starting the array block
	current_image++;
	if (current_image >= max_image_num)
		current_image = 0;

	//Use the current image value to find where the x and y position of the pixel
	int slide_x = (current_image % columns) * GetWidth();
	int slide_y = (current_image / rows) * GetHeight();

	//Use the X nd Y positions to find the initial pixel index in the 1D array.
	int index = (slide_y * GetBase()->GetBaseWidth() + slide_x);

	Set_Initial_Index(index);

	
}
