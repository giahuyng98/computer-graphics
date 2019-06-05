# computer-graphics

![Image](https://raw.githubusercontent.com/giahuyng98/computer-graphics/master/wev.PNG)

## This is a school project that implement some basic drawing algorithm:
  * 2D drawing: line (bresenham), recangle, circle, ellipse,
  * 3D convert cavalier + cabinet, cube, sphere, cylinder.
  * Animation creator & player.
  
  Usage under (L)GPL v3 license

## Using
You can [**download application here**](https://github.com/giahuyng98/computer-graphics/releases/download/v1.1/Computer-graphics-winx64.zip) 
(unzip & double click on CG2.exe to run it) or build it yourself

## Building
#### Requirements:
QT 5.12,
QT Creator,
MinGW or whatever C++ compiler you have

Once you successful install Qt, clone this repository, open file CG2.pro with QT creator -> build. Enjoy!

## Features & instructions
  * Visual 2d, 3d coordinate system
  * Draw line, recangle, circle, ellipse with mouse (just like mspaint).
  * Draw 3D cube, sphere, cylinder with keyboard input
  * Mutiple select objects
  * Remove objects, change border color or fill color with dfs algorithm
  * Choose pixel thickness (zoom in out)
  * Animation creator: when you done with drawing one frame click **add frame** to add another frame, you can use affine transformation (translation, rotation, scaling or reflection) to create animation or just clear all and draw another frame, finally click **to text file** to save your animation.
  * Animation editor: open your animation file by click **read text file** and then click **next frame** to view and edit (travel) frame one  by one, you can remove, add objects... and remember to save.
  * Animation player: On tab **Player** click **open** to open file, check **stop at each frame** to see your drawing process or uncheck to just see animation, you can adjust time by change **delay value**
