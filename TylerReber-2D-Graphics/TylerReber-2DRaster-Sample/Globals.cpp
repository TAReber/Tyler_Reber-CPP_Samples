#include "Globals.h"
#include <iostream>
Globals* Globals::GetGlobalsInstance()
{
    if (!instance)
        instance = new Globals();
    return instance;
}

Globals::Globals() {
	rasterPixels = new unsigned int[WIDTH * HEIGHT];
	
}

Globals::~Globals()
{
	delete rasterPixels;
	delete instance;
}

unsigned int* Globals::GetRasterPixels()
{
    return rasterPixels;
}

void Globals::TileBackground(ImageExtractor* _blit)
{
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			int _topleft_pix = (y * 32 * WIDTH) + (x * 32);
			TransferBlock(_blit, _topleft_pix);
			//groundTile->printImage(test, (y * 32 * WIDTH) + (x * 32));
			//std::cout << _topleft_pix << std::endl;
		}
		
	}

}



void Globals::TransferBlock(ImageExtractor* _blit, int _rasterLocation)
{
	int basewidth = _blit->GetBase()->GetBaseWidth();
	const unsigned int* arr = _blit->GetBase()->GetBaseArray();

	for (int y = 0; y < _blit->GetHeight(); y++) {

		for (int x = 0; x < _blit->GetWidth(); x++) {
			//Get Pixel from Header File
			//unsigned int pixel = arr[image_initial_index + (y * basewidth + x)];
			unsigned int color = _blit->GetBlockPixel(y * basewidth + x);
			
			//Break Out if tile expands beyond the Window Width
			if ((_rasterLocation % WIDTH) + x >= WIDTH) {
				break;
			}

			//rasterPixels[_start_pixel + (y * WIDTH + x)] = color;
			PlotPixel(_rasterLocation + (y * WIDTH + x), color);
		}

		if ((_rasterLocation + (WIDTH * y) > WIDTH * HEIGHT)) {
			break;
		}
		
	}

}

void Globals::AnimateBlock(Animator* _blit, int _rasterLocation)
{

	_blit->Animate_Next_Frame();
	TransferBlock(_blit, _rasterLocation);

}


void Globals::PlotPixel(int _index, unsigned int _color)
{
	int color = 0;


	if ((0x000000ff & _color) != 0) {

		//color = (0x000000ff & _color) << 24;
		color += (0x0000ff00 & _color) << 8;
		color += (0x00ff0000 & _color) >> 8;
		color += (0xff000000 & _color) >> 24;


		if ((0x000000ff & _color) < 255) {
			
			float alpha = (0x000000ff & _color) / (float)255;
			color = BlendColors(alpha, (color & 0x00ffffff), (rasterPixels[_index] & 0x00ffffff));

		}
		
		rasterPixels[_index] = color;
		
	}

}

unsigned int Globals::BlendColors(float _alpha, unsigned int _animationColor, unsigned int RasterColor)
{
	

	unsigned int r_back = (RasterColor & 0x00ff0000) >> 16;
	unsigned int g_back = (RasterColor & 0x0000ff00) >> 8;
	unsigned int b_back = RasterColor & 0x000000ff;

	unsigned int r_ani = (_animationColor & 0x00ff0000) >> 16;
	unsigned int g_ani = (_animationColor & 0x0000ff00) >> 8;
	unsigned int b_ani = _animationColor & 0x000000ff;

	unsigned int blendedColor = 0xff000000;
	unsigned int r = static_cast<unsigned int>(r_ani * _alpha) + (r_back * (1 - _alpha));
	unsigned int g = static_cast<unsigned int>(g_ani * _alpha) + (g_back * (1 - _alpha));
	unsigned int b = static_cast<unsigned int>(b_ani * _alpha) + (b_back * (1 - _alpha));

	blendedColor = (r << 16) + (g << 8) + b;

	return blendedColor;
}


