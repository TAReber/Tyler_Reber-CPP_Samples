#pragma once
//#include "ImageExtractor.h"
#include "Animator.h"

//Singleton that manages the interaction to the 2D Raster.

#define WIDTH 500
#define HEIGHT 500

class Globals
{
	static Globals* instance;
	unsigned int* rasterPixels;
	//constructor
	Globals();
	~Globals();


public:
	static Globals* GetGlobalsInstance();
	unsigned int* GetRasterPixels();
	/// <summary>
	/// Tiles Background with 1D Array image.
	/// </summary>
	/// <param name="_blit"></param>
	void TileBackground(ImageExtractor* _blit);
	/// <summary>
	/// Transfers Image data to the starting pixel location in the Raster display
	/// </summary>
	/// <param name="_blit"></param>
	/// <param name="_offset"></param>
	void TransferBlock(ImageExtractor* _blit, int _rasterlocation);
	/// <summary>
	/// Updates the the starting pixel of the next frame in animation image before Transfering to the RasterDisplay
	/// </summary>
	/// <param name="_blit"></param>
	/// <param name="_offset"></param>
	void AnimateBlock(Animator* _blit, int _rasterlocation);

	/// <summary>
	/// Checks the pixel for alpha value and converts from BGRA to ARGB
	/// </summary>
	/// <param name="_index"></param>
	/// <param name="_color"></param>
	void PlotPixel(int _index, unsigned int _color);

	unsigned int BlendColors(float _alpha, unsigned int _animationColor, unsigned int RasterColor);
};

