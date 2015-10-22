[TOC]

About {#about}
======

OpenLF is a graph based library for light field processing with focus on EPIs.

# Documentation {#doc}

doc/tutorial.md

# Installation {#install}

## Build (generic) {#build}

Generic instructions, specific platforms see [manual windows build](#win_man), [quick windows build](#win_quick), [linux](#linux).

### Dependencies {#deps}

Required dependencies (most will already be required for the installation of CLIF). For windows you can also use the installer with precompiled libraries, see [quick windows build](#win_quick).

- CLIF (https://github.com/hendriksiedelmann/clif)
- OpenCV
- Vigra
- Boost (filesystem, system)
- QT5

You only need to build CLIF (no need to install), cmake will link the build result into the users cmake package cache, which is searched by OpenLF.

### Source {#src}

Use your favorite git client and clone:
https://github.com/svenwanner/openlf

### compile {#compile}

- run cmake to generate the makefile for your favorite makesystem
- build

## Build (specific) {#build_specific}

<a name="win_man"></a>
### Manual Windows Build {#build_win_man}

- Install all dependencies from above. You only need to build CLIF (no need to install), cmake will link the build result into the users cmake package cache which will be found by OpenLF.
- Download OpenLF source from: https://github.com/svenwanner/openlf
- Open cmake-gui and run configure/generate to get a Visual Studio project. If you have problems finding any dependencies make sure that you supply the right paths to cmake (via cmake-gui or user/global %PATH%). The correct paths are those which contain the respective SomepackageConfig.cmake. Make sure you download the exact correct dependencies for your compiler and release version!
- Open the resultant *OpenLF.sln* in Visual Studio, and execute build.

<a name="win_quick"></a> 
### Quick Windows build using installer {#build_win_quick}

This method will work only for Microsoft Visual Studio 12 2013 (VC12) 64-bit in Relase mode.
- Run the dependency installer: *Install_Dependencies_LF_Toolbox_msvc12_x64.exe*, 
This will install all required dependencies (including clif) and add them to the user PATH.
- Download OpenLF source from: https://github.com/svenwanner/openlf
- execute cmake-gui and run configure/generate
- Open the resultant *OpenLF.sln* in Visual Studio, **change configuration to Release** and execute build.

<a name="linux"></a>
### Linux {#build_linux}

install dependencies

```
git clone https://github.com/svenwanner/openlf.git openlf
mkdir openlf/build
cd openlf/build
cmake ..
make
```
