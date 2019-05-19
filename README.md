# Innocence Engine
![Screen capture](https://github.com/zhangdoa/InnocenceEngine/blob/master/ScreenCapture.jpg)
[![Trello website](https://img.shields.io/badge/Trello-Roadmap-00bfff.svg)](https://trello.com/b/iEYu58hu/innocence-engine)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/3c0ea60f7c46491d87236822f6de35a6)](https://www.codacy.com/app/zhangdoa/InnocenceEngine?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=zhangdoa/InnocenceEngine&amp;utm_campaign=Badge_Grade)
[![CodeFactor](https://www.codefactor.io/repository/github/zhangdoa/innocenceengine/badge)](https://www.codefactor.io/repository/github/zhangdoa/innocenceengine)
[![Build status](https://ci.appveyor.com/api/projects/status/hl31o0q6nbmlf83i?svg=true)](https://ci.appveyor.com/project/zhangdoa/innocenceengine)
[![GPL-3.0 licensed](https://img.shields.io/badge/license-GPL--3.0-brightgreen.svg)](LICENSE.md)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fzhangdoa%2FInnocenceEngine.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Fzhangdoa%2FInnocenceEngine?ref=badge_shield)
[![Blog](https://img.shields.io/badge/My-Blog-ff884d.svg)](http://zhangdoa.com/)
[![Twitter Follow](https://img.shields.io/twitter/follow/espadrine.svg?style=social&label=Follow)](https://twitter.com/zhangdoa)
> "A poet once said, 'The whole universe is in a glass of wine.'"
> -- Richard Feynman, 1963

## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fzhangdoa%2FInnocenceEngine.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2Fzhangdoa%2FInnocenceEngine?ref=badge_large)

## How to build

### Windows

#### Build Engine
Tested under Windows 10 version 1903

Prerequisites: MSVC 19.00 + CMake 3.10 or higher + Vulkan pre-compiled library (Optional)

Run following scripts in a sequence
*Will build Debug and Release configurations in parallel*

``` cmd
@echo | setupWin.bat
```
```powershell
buildAssimpWin-VS15.ps1
buildPhysXWin-VS15.ps1
buildEngineWin-VS15.ps1
postBuildWin.ps1
```

#### Build Editor
Tested under Windows 10 version 1903

Prerequisites: Qt Creator 5.13 or higher

- Open `source\editor\InnocenceEditor\InnocenceEditor.pro` with Qt Creator
- Change "Projects - Build Settings - General - Build directory" to `..\..\..\bin` for Debug, Profile and Release build configurations
- Change "Projects - Run Settings - Run - Working directory" to `..\..\..\bin`
- Build the project

### Linux

Tested under Ubuntu 18.04 LTS

Prerequisites: GCC 8.0 or Clang 7.0 or higher + CMake 3.10 or higher + OpenGL library(lGL)

Run following scripts in a sequence:

``` shell
echo | setupLinux.sh
echo | buildAssimpLinux.sh
echo | buildLinux.sh # or buildLinux-Clang.sh or buildLinux-CodeBlocks.sh
echo | postBuildLinux.sh
```

### macOS

Tested under version 10.13.6

Prerequisites: CMake 3.10 or higher + Clang 7.0 or higher

Run following scripts in a sequence:

``` shell
echo | setupMac.sh
echo | buildAssimpMac-Xcode.sh
echo | buildMac.sh
echo | postBuildMac.sh
```

## How to use

### Windows

#### Launch game build
Run following script

``` powershell
startEngineWin.ps1
```

#### Launch editor build
Launch through Qt Creator

### Linux

Run following script

``` shell
echo | startEngineLinux.sh
```

### macOS

Run following script

``` shell
echo | startEngineMac.sh
```

## How to debug

### Windows

1. Open build/InnocenceEngine.sln
2. Set debug launch arguments and default launch project to InnoMain
3. Start debug with "Launch" button (default F5)

### Linux

1. Use Atom to load the repo folder
2. Install gcc-compiler package
3. Select build/makefile and hit "Compile and Debug" button default F6)
4. (Optional) Change launch arguments in source/engine/platform/Linux/CMakeLists.txt

### macOS

1. Use Atom to load the repo folder
2. Open source/engine/platform/macOS/InnoMain.InnoMain.xcodeproj
3. Select "Product" - "Run" (⌘ + R)

## Available launch arguments

```
-renderer [value]
```
| Value |Notes |
| --- | --- |
| 0 | OpenGL rendering backend |
| 1 | DirectX 11 rendering backend |
| 2 | DirectX 12 rendering backend (WIP) |
| 3 | Vulkan rendering backend (WIP) |
| 4 | Metal rendering backend (WIP) |

```
-mode [value]
```
| Value |Notes |
| --- | --- |
| 0 | game mode |
| 1 | reserved for editor |

## Features

[Entity–component–system architecture](https://en.wikipedia.org/wiki/Entity%E2%80%93component%E2%80%93system)

Task-based concurrency model

[Object memory pool model](https://en.wikipedia.org/wiki/Object_pool_pattern)

[Tiled deferred rendering pipeline](https://en.wikipedia.org/wiki/Deferred_shading)

[Physically based shading](https://en.wikipedia.org/wiki/Physically_based_rendering)

[Scene graph](https://en.wikipedia.org/wiki/Scene_graph)

## References & Dependencies

### Third-party libraries

[assimp](https://github.com/assimp)

[GLAD](https://github.com/Dav1dde/glad)

[dear imgui](https://github.com/ocornut/imgui)

[stb](https://github.com/nothings/stb)

[JSON for Modern C++](https://github.com/nlohmann/json)

[PhysX](https://github.com/NVIDIAGameWorks/PhysX)

### Assets

[Free3D]( https://thefree3dmodels.com)

[Musopen](https://musopen.org)

[Free PBR Materials](https://freepbr.com/)

[HDR Labs](http://www.hdrlabs.com/)

## Inspirations

### Books

[C++ Primer (4th Edition)](https://www.amazon.com/Primer-4th-Stanley-B-Lippman/dp/0201721481)

[A Tour of C++](https://www.amazon.com/Tour-C-Depth/dp/0321958314)

[Effective C++: 55 Specific Ways to Improve Your Programs and Designs (3rd Edition)](https://www.amazon.com/Effective-Specific-Improve-Programs-Designs/dp/0321334876)

[Inside the C++ Object Model (1st Edition)](https://www.amazon.com/Inside-Object-Model-Stanley-Lippman/dp/0201834545)

[Effective Modern C++: 42 Specific Ways to Improve Your Use of C++11 and C++14](https://www.amazon.com/Effective-Modern-Specific-Ways-Improve/dp/1491903996)

[API Design for C++ (1st Edition)](https://www.amazon.com/API-Design-C-Martin-Reddy/dp/0123850037)

[Advanced C and C++ Compiling (1st Edition)](https://www.amazon.com/Advanced-C-Compiling-Milan-Stevanovic/dp/1430266678)

[Data Structures and Algorithms in C++ (4th Edition)](https://www.amazon.com/Data-Structures-Algorithms-Adam-Drozdek-ebook/dp/B00B6F0F5S)

[Game Engine Architecture (1st Edition)](https://www.amazon.com/Game-Engine-Architecture-Jason-Gregory/dp/1568814135)

[Game Programming Patterns](https://www.amazon.com/Game-Programming-Patterns-Robert-Nystrom/dp/0990582906)

[Game Coding Complete (4th Edition)](https://www.amazon.com/Game-Coding-Complete-Fourth-McShaffry/dp/1133776574)

[Real-Time Rendering (4th Edition)](https://www.amazon.com/Real-Time-Rendering-Fourth-Tomas-Akenine-Mo-ebook/dp/B07FSKB982)

[Physically Based Rendering : From Theory to Implementation(2nd Edition)](https://www.amazon.com/Physically-Based-Rendering-Second-Implementation/dp/0123750792)

[Computer Graphics with Open GL (4th Edition)](https://www.amazon.com/Computer-Graphics-Open-GL-4th/dp/0136053580)

[OpenGL Programming Guide: The Official Guide to Learning OpenGL, Version 4.5 with SPIR-V (9th Edition)](https://www.amazon.com/OpenGL-Programming-Guide-Official-Learning/dp/0134495497)

[Calculus (6th Edition)](https://www.amazon.com/CALCULUS-Sixth-James-Stewart/dp/B00722RNC2)

[Linear Algebra and Its Applications (3rd Edition)](https://www.amazon.com/Linear-Algebra-Its-Applications-3rd/dp/0201709708)

And more...

### Online tutorials & resources

[Mathematics - Martin Baker](http://www.euclideanspace.com/maths)

[Wolfram MathWorld: The Web's Most Extensive Mathematics Resource](http://mathworld.wolfram.com)

[cppreference.com](https://en.cppreference.com)

[Standard C++](https://isocpp.org)

[Gamasutra](http://www.gamasutra.com)

[Scratchapixel](https://www.scratchapixel.com)

[Advances in Real-Time Rendering in 3D Graphics and Games](http://advances.realtimerendering.com)

[Learn OpenGL](https://learnopengl.com)

[OpenGL Step by Step](http://ogldev.atspace.co.uk)

[RasterTek - DirectX 10, DirectX 11, and DirectX 12 tutorials](http://www.rastertek.com/)

[thebennybox's YouTube channel](https://www.youtube.com/user/thebennybox)

[Randy Gaul's Game Programming Blog](http://www.randygaul.net)

[Sébastien Lagarde's blog](https://seblagarde.wordpress.com)

[Stephen Hill's blog](http://blog.selfshadow.com)

And more...