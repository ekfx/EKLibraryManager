# EKLibraryManager
This is a project that handles a library manager to Windows (with support to Linux and Mac in the future) as a Conclusion Course Work to my high school.
Planned to beginners who have difficulties to start in the programming world, I want to give more opportunities to peoples who don't know how big is this world.

## Features
- C++ 23
- CURL
- Miniz

## Progress
Still not complete, I am in the stage of descompress the libraries.

## How to Compile
1. You will need: CURL and GNU Make already installed in your machine.
2. You can use 
```
if not exist build mkdir build
x86_64-w64-mingw32-g++ -Iinclude -MMD -MP -O0 -g0 -pipe -ID:/vcpkg/packages/curl_x64-windows/include -c src/LD_Portable.cpp -o build/LD_Portable.o
x86_64-w64-mingw32-g++ build/CMD.o build/EKLibraryManager.o build/EKR.o build/LD.o build/LD_Portable.o build/LD_Windows.o build/UZIP.o -Llib-mingw-w64 -lwinmm -mconsole -LD:/vcpkg/packages/curl_x64-windows/lib -lz -lcurl -o build/EKLibraryManager.exe
```
or use `make` to compile and `make run` to run.
3. Enjoy my program and don't forget to do a feedback!
