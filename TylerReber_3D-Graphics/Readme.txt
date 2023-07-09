3D Graphics - Lab 3 of Computer Graphics.

In this lab I needed to create a 3D graphics Renderer and mimic the functionality of shaders.

My Work for this project.

I chose the MVC(model view controller) design pattern to implement this solution.

- I started by drawing a box out of lines and created a view and projection matrix.
- I added the functionality to draw the box out of triangles and used barycentrix coordinates to map
a texture to the box with UV coodinates.

- One of my goals was to preserve the ability to draw lines and triangles simultaneously. That is why you can see the box lines and the texture, as they are seperate objects being drawn in the same place. It creates the illusion that my texture has transparency.

Critisism of my solution - What I could be done better.

This is the first time I wrote 3D math functions. I didn't consider that this could be implemented as an entire home built math library. I have vector and matrix functions packed into their own files which clutters up my solution. This could be done much cleaner than what I have.

I didn't understand how shaders were supposed to work when I was working on this. It wasn't until working with graphics in the Vulkan API that I realized that the view in my MVC pattern was the vertex shader. Had I realized this, my shader.h file would have been appropiatly thought of and treated as pixel shader, rather than a general use shader. This misunderstanding about shaders caused difficulty during Lab 4.



School Environment.

The school provided the code to create a window with win32, the timer class and a tool to convert images into header files containing 1D Arrays of the pixel data.

RasterSurface.h
RasterSurface.cpp
XTime.h
XTime.cpp