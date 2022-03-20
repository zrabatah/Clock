#   Clock
Clock is a C program designed to show real-time events for the user via different interfaces.
Currently the program supports 4 interfaces.
1. Analog Clock
2. Digital Clock
3. Timer
4. Stopwatch

This program runs on Linux distributions and has been tested on Debian-like systems.

##  Compliation

Install the dependencies in order to compile. The program should be able to be compiled with either clang or gcc.

Debian-like systems:

Build essential should be installed, but if it is not the command below will install it.
This will install make and the gcc compiler.

sudo apt install build-essential

OR

sudo apt-get install build-essential

Clang can also be used to compile the program.

sudo apt install clang

OR

sudo apt-get install clang

In order to build/compile gtk install the below library.

sudo apt install libgtk-3-dev

OR

sudo apt-get install libgtk-3-dev

Once dependencies are installed, run the below compile command or use make with the provided Makefile.

make clean; make

OR

clang main.c clock.c -o clock -lasound -lm `pkg-config --cflags --libs gtk+-3.0`

OR

gcc main.c clock.c -o clock -lasound -lm `pkg-config --cflags --libs gtk+-3.0`

THEN

./clock

##  Desktop File
Edit the desktop file with the path to the binary and/or icon.
Example:
/home/{}/...

{}: Replace with your specific computer home name
...: Remaining path to the binary file

##  MIT License

Copyright (c) 2022 zrabatah

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
