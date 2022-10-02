# M_Engine 
![M_Engine current state](./engine/resources/img/ref-current/current.gif)

M_Engine is a cross-platform game engine written in C++ and OpenGL, with an emphasis on performance.

## Table of Contents
1. [Introduction](#introduction)
2. [Setup](#setup)

## Introduction <a name="introduction"></a>
The best way to introduce this engine is to explain its purpose. It is a demonstation of what can be achieved with Modern C++ and OpenGL, using little overhead to achieve peak performace and maximal compatibility. Of course the sudden thought of compromised performance due to looser integration with platform specifics may cross one's mind, however, with the ideas of opensource and inclusivity being predominant development factors, minimizing performance costs where they count and rigorously testing many configurations, ensures a high performaning application.

## Setup <a name="setup"></a>
### Code Editor
As far as code editors go, any that supports building with CMake is fine. The one chosen for development was Visual Studio Code as it is a cross-platform code editor alongside a few extensions - **C/C++**, **C/C++ Extension Pack**, **CMake**, **Cmake Tools** and **CMake Language Support**.

### macOS
WiP

### Windows
WiP

### Linux
WiP

## Build Toolchain (CMake)
Although originally, compilation was handled partially by vscode task files and otherwise by hand, now it is fully automated through CMake.

To build the project without opening an IDE/Editor:

```shell
mkdir build
cd build
cmake ..
make
```