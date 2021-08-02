# pEngine

## Introduction

pEngine is 3D game engine using a component based structure, lua scripting, and a Dear Imgui editor.

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
Built for Windows 10 using MinGW and a MinGW makefile. OpenGL needs to be installed.

## Setup
To build and run this project download and in the main directory run the commands:

```
$ mingw32-make.exe
$ mingw32-make.exe run
```

## Features
* Dear Imgui editor inspired by Unity
* Lua scripting

## Lua Integration

### Required
Each lua file needs a Start() and FixedUpdate(float) function

### Global
#### Functions
* vec3 random_vec3(float low, float high)
    * Returns a 3 dimension vector with each index being between low and high
* float random_float(float low, float high)
    * Returns a float between low and high
* vec3 normalize(vec3 vector)
    * Returns a normalized vector in the same direction as given
* float distance(vec3 vector1, vec3 vector2)
    * Returns distance between two vectors
* vec3 get_direction(vec3 vector1, vec3 vector2)
    * Creates vector given two vectors
* vec3 zero_vec2()
    * Returns the zero vector
* float length(vec3 vector)
    * Returns the magnitude of the vector
* vec3 add_float(vec3 vector, float num)
    * Adds num to each index in vector
* vec3 add_vec3(vec3 vector1, vec3 vector2)
    * Adds the two vectors together
* Object FindObject(int id)
    * Finds object with the given id
### Vec3
3 dimension vector class
* x, y, z (float)
    * Indexes of the 3 dimensional vector

### Object
Object class
#### Variables
* name (string)
    * Name of the object
* id (int)
    * Id of the object
#### Functions
* Physics GetPhysics()
    * Returns Physics component
* Transform GetTransform()
    * Returns Transform component

### Physics
#### Variables
* acceleration (vec3)
    * Current acceleration acting on object
* forces (vec3)
    * forces acting on object
* velocity (vec3)
    * velocity of object
#### Functions
* void ApplyForce(vec3 direction, float power)
    * Applies force on object with given direction and power
* void UpdateGravity()
    * Determines the gravitational force acting on this object from other objects in scene

### Transform
### Variables
* position (vec3)
    * Position of the object
* rotation (vec3)
    * Rotation of the object
* scale (vec3)
    * Scale of the object
* startPosition (vec3)
    * The position the object starts from


## Inspiration
Parts of the OpenGL and shader code was based on [opengl-tutorials](https://github.com/opengl-tutorials/ogl)