[TOC]

About {#about}
======

%OpenLF is a graph based library for light field processing with focus on EPIs.

# Documentation {#doc}

Compile documention with doxygen by executing *doxygen* in the source dir.
This should create html/index.html which is the starting point for the documentation (which is actually this file). 

Habe a look at the [Tutorial 1 - A First Component](@ref tutorial) and [Tutorial 2 - Image Processing Components](@ref timg).

See [tools](doc/tools.md) and [advanced component programing](doc/advanced.md) for further information or have a look at the [architecture overview](doc/architecture.md).

# Installation {#install}

## Generic Build Instructions  {#build}

Generic instructions, specific platforms see [manual windows build](#win_man), [quick windows build](#win_quick), [linux](#linux).

### Dependencies {#deps}

Required dependencies (most will already be required for the installation of CLIF). For windows you can also use the installer with precompiled libraries, see [quick windows build](#win_quick).

- CLIF (https://github.com/hendriksiedelmann/clif)
- OpenCV
- Vigra
- Boost (filesystem, system)
- QT5

You only need to build CLIF (no need to install), cmake will link the build result into the users cmake package cache, which is searched by %OpenLF.

### checkout {#src}

Use your favorite git client and clone:
https://github.com/svenwanner/openlf

### compile {#compile}

- run cmake to generate the makefile for your favorite makesystem
- build

### install {#intall}

you do not need to run the install target, but whether you do or not you need to setup your environmont so OPENLF_COMPONENT_PATH points to the path where components were compiled into (e.g. \a <builddir>/components under *NIX).
Also if you want to launch the dataset viewer (clifview) the clifview executable from clif needs to be in your path.

## System Specific Build Instructions {#build_specific}

<a name="win_man"></a>
### Manual Windows Build {#build_win_man}

- Install all dependencies from above. You only need to build CLIF (no need to install), cmake will link the build result into the users cmake package cache which will be found by %OpenLF.
- Download %OpenLF source from: https://github.com/svenwanner/openlf
- Open cmake-gui and run configure/generate to get a Visual Studio project. If you have problems finding any dependencies make sure that you supply the right paths to cmake (via cmake-gui or user/global \%PATH\%). The correct paths are those which contain the respective SomepackageConfig.cmake. Make sure you download the exact correct dependencies for your compiler and release version!
- Open the resultant *OpenLF.sln* in Visual Studio, and execute build.
- at last step put component library into user PATH, see \ref win_path

<a name="win_quick"></a> 
### Quick Windows build using installer {#build_win_quick}

This method will work only for Microsoft Visual Studio 12 2013 (VC12) 64-bit in Relase mode.
- Run the dependency installer: *Install_Dependencies_LF_Toolbox_msvc12_x64.exe*, 
This will install all required dependencies (including clif) and add them to the user PATH.
- if you want to use your self-compiled clif (recommended) simplfy remove the clif dir from the install directory
- Download %OpenLF source from: https://github.com/svenwanner/openlf
- execute cmake-gui and run configure/generate
- Open the resultant *OpenLF.sln* in Visual Studio, and execute build.
- at last step put component library into user PATH, see \ref win_path

### Setup Components Path {#win_path}

Add the OPENLF_COMPONENT_PATH Environment Variable to the environment of your user to point at the folder where the components where compiled into. For a Debug build this is \a <builddir>\\components\\Debug.

<a name="linux"></a>
### Linux {#build_linux}

install dependencies, afterwards, compile openlf:

```
git clone https://github.com/svenwanner/openlf.git openlf
mkdir openlf/build
cd openlf/build
cmake ..
make
```

setup an env variable OPENLF_COMPONENT_PATH which points at the component dir, e.g \a <builddir>/components .