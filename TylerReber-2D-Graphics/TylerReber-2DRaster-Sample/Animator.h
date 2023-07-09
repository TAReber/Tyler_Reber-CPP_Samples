#pragma once
#include "ImageExtractor.h"

//

class Animator :
    public ImageExtractor
{

    int columns;
    int rows;

    int current_image;
    int max_image_num;
    
public:
    Animator(int _initialIndex, int _width, int height, BaseImage _header_Image_Source);
    ~Animator();
    int GetCurrentImage();
    int GetMaxImage();

    /// <summary>
    /// Tracks and Caluclates the index from the current animation frame.
    /// </summary>
    void Animate_Next_Frame();


};

