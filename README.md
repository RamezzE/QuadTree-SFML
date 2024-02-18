# SFML QuadTree
Collision detection by space partitioning using a Quad Tree data structure.

Written in C++ using the SFML graphics library

![QuadTree Circle Collision2](https://user-images.githubusercontent.com/117018553/230356184-5a31a253-b3ce-405f-8954-cba2953ef321.gif)

## Controls:
- *Spacebar* to toggle the movement of the particles
- *M* to toggle the visibility & function of the mouse's box query

## Prerequisites
- g++ 4.8 or above
- GNU Make
- SFML 2.5.1 or above [[www.sfml-dev.org](https://www.sfml-dev.org/download/sfml/2.5.1/)]

#### Linux
- You can run these commands on linux to install g++, Make and SFML

```
$ sudo apt-get install g++
$ sudo apt-get install make
$ sudo apt-get install libsfml-dev
```

### Windows
- Install the proper SFML version from the website (MinGW version for GNU Make build or Visual C++ for MS Build)
- Unzip the SFML downloaded folder ( You can run `choco install 7zip` to be able to unzip )

#### MS Build
- Visual Studio 15 or above
- VC++ 15 or above


## Building

### GNU Make (Method used)

- Install GNU Make by installing [chocolatey](https://chocolatey.org/install#individual) package manager  and running this command from an elevated Command Prompt:
```
$ choco install make
```
- Install MinGW g++ [MinGW 32-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win32/Personal%20Builds/mingw-builds/7.3.0/threads-posix/dwarf/i686-7.3.0-release-posix-dwarf-rt_v5-rev0.7z/download) or [MinGW 64-bit](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/7.3.0/threads-posix/seh/x86_64-7.3.0-release-posix-seh-rt_v5-rev0.7z/download) (The SFML version and the MinGW version have to match)

- After unzipping the MinGW file, add your path to mingw32/bin or mingw64/bin to PATH in the system environmental variables

- Download source code

- (Windows Only) Edit the Makefile in the project directory to to add your SFML/include & SFML/lib paths

- Copy all the dlls in `</path/to/sfml/>/bin` to the project directory where the Makefile exists

- Open your terminal in your project directory where the Makefile exists

- Run Make in your terminal:

```
$ make
```
- You can clean the files by running:
```
$ make clean
```
- You can run the latest compiled build using:
```
$ make run
```

### MS Build

1. Add the `</path/to/sfml/>/include` to your **additional C++ include directories**.
2. Add `</path/to/sfml/>/lib` to your **additional library directories**.
3. Add the SFML libraries used to your **additional dependencies**

   eg:
   ``
   sfml-graphics.lib;sfml-system.lib;sfml-window.lib;
   ``

4. Add the dlls in your SFML path/bin along with your executable

## Acknowledgements

This QuadTree is inspired by this tutorial series https://www.youtube.com/watch?v=OJxEcs0w_kE

## License

This project is licensed under the MIT license
