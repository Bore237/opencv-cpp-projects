# OpenCV C++ Development Setup

This document explains how to configure a C++ development environment using OpenCV, CMake, and Visual Studio Code on Windows.

The goal is to provide a reproducible setup for building and running OpenCV-based C++ projects.

---

## Prerequisites

Before starting, install the following tools:

* Windows 10/11
* Visual Studio with C++ development tools
* Visual Studio Code
* CMake
* OpenCV library

Recommended VS Code extensions:

* C/C++ (Microsoft)
* CMake Tools
* CMake Language Support

---

# 1. Install OpenCV

Download OpenCV from:

https://sourceforge.net/projects/opencvlibrary/

Extract OpenCV to:

```
C:\opencv
```

After installation, verify that the following directories exist:

```
C:\opencv\build\x64\vc16\bin
C:\opencv\build\x64\vc16\lib
```

The `bin` directory contains the OpenCV runtime DLL files.

The `lib` directory contains the libraries required during linking.

Example:

```
C:\opencv
 └── build
     └── x64
         └── vc16
             ├── bin
             │   ├── opencv_worldxxx.dll
             │
             └── lib
                 ├── opencv_worldxxx.lib
```

---

# 2. VS Code CMake Configuration

Create or update your VS Code workspace settings:

`.vscode/settings.json`

```json
{
    "cmake.sourceDirectory": "D:/C_plus/projets/opencv/gui_interface",
    "cmake.buildDirectory": "${sourceDir}/build",
    "cmake.configureSettings": {
        "OpenCV_DIR": "C:/opencv/build/x64/vc16/lib"
    },
    "terminal.integrated.env.windows": {
        "PATH": "C:\\opencv\\build\\x64\\vc16\\bin;${env:PATH}"
    }
}
```

## Configuration details

### cmake.sourceDirectory

Defines the folder containing the `CMakeLists.txt` file.

Example:

```
D:/C_plus/projets/opencv/gui_interface
```

---

### cmake.buildDirectory

Defines where CMake generated files and build outputs are stored.

Example:

```
gui_interface/build
```

---

### OpenCV_DIR

Specifies the OpenCV library location used by CMake.

Example:

```
C:/opencv/build/x64/vc16/lib
```

This allows CMake to find OpenCV headers and libraries.

---

### PATH environment variable

Adds the OpenCV DLL directory to the Windows environment.

```
C:\opencv\build\x64\vc16\bin
```

Without this configuration, the executable may compile successfully but fail to start because Windows cannot find OpenCV runtime DLLs.

---

# 3. CMake Configuration

Example `CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.23)

project(gui_interface LANGUAGES CXX)

set(OpenCV_STATIC OFF)

find_package(OpenCV REQUIRED)

add_executable(gui_interface main.cpp)

target_link_libraries(gui_interface PRIVATE ${OpenCV_LIBS})

add_custom_command(TARGET gui_interface POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_RUNTIME_DLLS:gui_interface>
    $<TARGET_FILE_DIR:gui_interface>
    COMMAND_EXPAND_LISTS
)
```

---

## CMake explanation

### Find OpenCV

```cmake
find_package(OpenCV REQUIRED)
```

Searches for the installed OpenCV package and loads the required configuration.

The build will fail if OpenCV cannot be found.

---

### Static linking option

```cmake
set(OpenCV_STATIC OFF)
```

Uses dynamic OpenCV libraries (`.dll`).

This is the recommended configuration for normal Windows development.

---

### Link OpenCV libraries

```cmake
target_link_libraries(gui_interface PRIVATE ${OpenCV_LIBS})
```

Links the application with OpenCV libraries.

---

### Copy runtime DLLs automatically

```cmake
add_custom_command(...)
```

After compilation, required DLL files are copied next to the executable.

Example output:

```
build/
 └── Debug/
     ├── gui_interface.exe
     ├── opencv_worldxxx.dll
```

This avoids manually copying DLL files.

---

# 4. Build the Project

Open the project folder in VS Code.

Configure CMake:

```
Ctrl + Shift + P
```

Select:

```
CMake: Configure
```

Build the project:

```
CMake: Build
```

The executable will be generated in the build directory.

Example:

```
build/
 └── Debug/
     └── gui_interface.exe
```

---

# 5. Debug DLL Dependencies

If the application starts with a missing DLL error, check executable dependencies.

Open a Visual Studio Developer Command Prompt:

```cmd
dumpbin /dependents gui_interface.exe
```

Example output:

```
opencv_world4xx.dll
VCRUNTIME140.dll
MSVCP140.dll
```

This command shows all DLL dependencies required by the executable.

---

# Troubleshooting

## Error: OpenCV not found by CMake

Check:

```
OpenCV_DIR
```

must point to:

```
C:/opencv/build/x64/vc16/lib
```

Also verify that OpenCV is correctly installed.

---

## Error: Missing OpenCV DLL when running

Possible solutions:

### Option 1: Add OpenCV bin directory to PATH

Add:

```
C:\opencv\build\x64\vc16\bin
```

to your system PATH.

---

### Option 2: Copy DLL files next to the executable

Copy:

```
C:\opencv\build\x64\vc16\bin\opencv_worldxxx.dll
```

into:

```
build/Debug/
```

---

## Error: Compiler or linker problems

Check:

* Visual Studio C++ workload is installed
* Architecture matches OpenCV build

Recommended configuration:

```
Architecture: x64
Compiler: Visual Studio 2022
Generator: Visual Studio 17 2022
```

---

# Useful Commands

## Check OpenCV installation

```
dir C:\opencv\build\x64\vc16
```

---

## Check executable dependencies

```cmd
dumpbin /dependents gui_interface.exe
```

---

## Clean CMake build

Delete:

```
build/
```

Then run:

```
CMake: Configure
CMake: Build
```

---

# Project Structure Example

```
gui_interface
│
├── CMakeLists.txt
├── main.cpp
│
├── .vscode
│   └── settings.json
│
└── build
    └── Debug
        └── gui_interface.exe
```

---

# License

This configuration guide is provided for learning and development purposes.
