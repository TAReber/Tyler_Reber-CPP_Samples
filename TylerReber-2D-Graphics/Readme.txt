2D Blit Raster at Full Sail University

Lab 1 of Computer Graphics.


School Environment.

The school provided the code to create a window with win32, the timer class and a tool to convert images into header files containing 1D Arrays of the pixel data.
RasterSurface.h - Created the window with win32
RasterSurface.cpp
XTime.h
XTime.cpp

Header Files created from Image Conversion Tool
fire_01.h
tiles_12.h
spelk2.h

My Lab Work

This lab I had to work with pixel data stored in a 1D array and map the data to a 2D raster display created
with RasterSurface.h.

 - I created a singleton class that handled the communication to the 2D Raster.

 - I created a baseimage class that was responible for identifying the image an object should be looking at and storing data for it.

 - I created the ImageExtractor class, this class was responible for targeting 2D group of pixels
by targeting the initial pixel at the x and y position in the base image, the x and y span of the image
and handling the 1D to 2D conversions. This allowed me to pull a tile out of a sprite sheet.

- I created Animation class that derived from the ImageExtractor. The Animation class is responsible for
calculating the next starting pixel of an animation frame, which allowed me it iterate over a BaseImage
in blocks.

As observed in main.cpp, this allowed me to make simple calls in the main update loop to both draw and animate.


Conclusion
I'm happy with the structure of the program. In main it allows me to use objects and easily pick
where it should be drawn in the Raster Display. If I needed to handle input to move a character object,
it would be easy to do so with this setup as I just need to update one location.

I would like a more intuitive way to target a tile in a baseimage.

Files that I created.
main.cpp
Globals.h/cpp
BaseImage.h/cpp
ImageExtractor.h/cpp
Animator.h/cpp