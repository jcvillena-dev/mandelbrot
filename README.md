# CPPND: Capstone Mandelbrot Set Repo

* This is a Mandelbrot Set repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).
* It is a light viewer for the Mandelbrot Set. 
* The fractal is rendered in a static window created with SDL. 
* It is possible to screenshot a rendered image. When key "S" is pressed, a generated BMP is saved in images directory.
* Used parameters are passed to the program as arguments. 
* If the arguments are not supplied, the fractal is calculated with default values.
* The arguments are described below: 
  * Max and Min for X-axis.
  * Max and Min for Y-axis
  * Max number of iterations 
  * Number of threads to be used
  * Height of the window
  * Width of the window

## Example

The next image is generated with the arguments:

```
* ./Mandelbrot --minx=-2.0 --maxx=1.0 --miny=-1.0 --maxy=1.0 --maxiter=100 --threads=4 --height=800 --width=1000
```
<IMG src="images/screenshotTueFeb11651102022.bmp">

## Files and Classes
* The project is divided into the following files:
  * main./cpp: reads the input arguments, creates the Mandelbrot object and passes the Mandelbrot object to an instance of Window class.
  * Mandelbrot.h/cpp: it is the class that computes the Mandelbrot Set. Provides a matrix of RGB values.
  * Window.h/cpp: this is the class that generates a SDL Window and renders the RGB matrix provided by Mandelbrot class.
* Header files are in include directory.
* CPP files are in src directory. 

#Rubric Points:
* Common:
 * The project code is clearly organized into functions.
 * The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
 * All class data members are explicitly specified as public, protected, or private.
 * All class members that are set to argument values are initialized through member initialization lists.
 * The project follows the Resource Acquisition Is Initialization pattern where appropriate, by allocating objects at compile-time, initializing objects when they are declared, and utilizing scope to ensure their automatic destruction.

* main.cpp:
 * The project accepts input from a user as part of the necessary operation of the program.
 * The project uses at least one smart pointer: unique_ptr, shared_ptr, or weak_ptr. The project does not use raw pointers.

* Mandelbrot class:
 * The project uses multiple threads in the execution.
 * A mutex or lock (e.g. std::lock_guard or `std::unique_lock) is used to protect data that is shared across multiple threads in the project code.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL 2.0
  * https://wiki.libsdl.org/Installation

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Mandelbrot`.