# SFML QuadTree
Collision detection by space partitioning using a Quad Tree data structure.

Written in C++ using the SFML graphics library

![QuadTree Circle Collision2](https://user-images.githubusercontent.com/117018553/230356184-5a31a253-b3ce-405f-8954-cba2953ef321.gif)

## Controls:
- *Left Mouse Click* to shuffle the particles position
- *Right Mouse Click* to toggle the visibility of the QuadTree borders
- *Spacebar* to toggle the movement of the particles
- *M* to toggle the visibility & function of the mouse's box query

## Prerequisites

- SFML 2.5.1 or above www.sfml-dev.org

#### Linux

- Cmake version 3.28 or above

- You can run this command on linux to install SFML

```
$ sudo apt-get install libsfml-dev
$ sudo pacman -S sfml
```

#### MS Build
 - Visual Studio 15 or above
 - VC++ 15 or above


## Building

### CMake build

- install CMake version 3.28 or above

- git clone this repository

- Open your terminal emulator and `cd` to the path of this project

- run `cmake . && make && ./bin/QuadTree-SFML` to generate the make files, build the make file, and run the final build

- - After running `cmake .` you can just run `make && ./bin/QuadTree-SFML` to run the app after changes

- - You can also just run the latest build with `./bin/QuadTree-SFML`

### MS Build 

 1. Add the `</path/to/sfml/>/include` to your **additional C++ include directories**.
 2. Add `</path/to/sfml/>/lib` to your **additional library directories**.
 3. Add the SFML libraries used to your **additional dependencies** 
 
    eg: 
     ``
     sfml-graphics.lib;sfml-system.lib;sfml-window.lib;
     ``
 
 4. Add the dlls in your SFML path/bin along with your executable
 

### To build SFML statically 
  Add the following libraries to your **additional dependencies**
  
  ``
  sfml-graphics-s-d.lib sfml-window-s-d.lib sfml-system-s-d.lib opengl32.lib winmm.lib gdi32.lib sfml-main-d.lib freetype.lib
  ``
  
  You can remove the ``-d`` if you do not need to debug
  
## Acknowledgements

This QuadTree is inspired by this tutorial series https://www.youtube.com/watch?v=OJxEcs0w_kE

## License

This project is licensed under the MIT license
