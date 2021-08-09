# pEngine

## Table of Contents
* [Introduction](#introduction)
* [Technology Used](#technology-used)
* [Requirements](#requirements)
* [Setup](#setup)
* [Features](#features)
* [Documentation](#documentation)
* [Plans](#plans)
* [Sources](#sources)
* [License](#license)

## Introduction

pEngine is 3D game engine built in C++ using a component based structure, lua scripting, and a Dear Imgui editor.

The purpose of this engine was to get more practice with C++ and game engine architecture.

## Technology Used
* C++ 17
* GLEW 2.1.0
* GLFW 3.3.4
* GLM
* Dear ImGui
* LuaDist 0.9.8
* RapidJSON
* Sol2

## Requirements
Built for Windows 10 using MinGW and a MinGW makefile.

MinGW compiler path:
```
C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe
```

## Setup
To build and run this project download and in the main directory run the commands:

```
$ mingw32-make.exe
$ mingw32-make.exe run
```

## Features
* Dear Imgui editor inspired by Unity
* Lua scripting

## Documentation
[Doxygen documentation for engine](documentation.pdf)

[Documentation for Lua integration](LuaDocumentation.md)

## Plans
* More shaders
* Collision detection

## Sources
Parts of the OpenGL and shader code was based on [opengl-tutorials](https://github.com/opengl-tutorials/ogl)

## License
This project is licensed under the terms of the MIT license.

Full license [here](LICENSE.txt)
