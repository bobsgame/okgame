# Compiling bob's game

> :warning: The latest commit is currently broken since Bob is working on wrapping everything in `shared_ptr`, if you want a buildable commit, please change the project to the last working commit by running `git reset --hard bd12292e037de0babb79b4106125df95d4d5436f` in the project root directory.

This guide is for compiling straight from the bob's game repo. All of the modified files are in this repo.

Join the [discussion Discord](https://discord.gg/FfDxFc4JuS)!

## Installing VS 2017
> Bob claimed Visual Studio 2022 works with compiling bob's game, you may want to try that if you cannot find the download for Visual Studio 2017 Community.
1. Download Visual Studio 2017 from <https://visualstudio.microsoft.com/vs/older-downloads/> *(You may need a Microsoft account)*
2. Download "Visual Studio Community 2017 (version 15.9)."
3. In the Visual Studio Installer make sure to install these:

Workloads:
- Desktop development with C++

Individual components:
- VC++ 2017 version 15.9 v14.16 latest v141 tools
- Windows 10 SDK (10.0.15063.0) for Desktop C++ (x86 and x64)

## Building bob's game for Windows
1. Create a folder called `workspace` in `C:\Users\Administrator`.
2. Clone bob's game using `git clone https://github.com/bobsgamed/ok.git` and rename it to `bobsgame`.
3. Launch Visual Studio 2017 and login to your Microsoft account.
4. Open the project with File > Open > Project/Solution.
5. Open `bobsgame.sln` in `C:\Users\Administrator\workspace\bobsgame`.
6. Set the release type from Debug to Release.
7. Download boost from <https://boostorg.jfrog.io/artifactory/main/release/1.64.0/source/boost_1_64_0.zip>.
8. Extract the `boost_1_64_0` folder to `C:\Users\Administrator\workspace`.
9. Head to Project > Properties > C/C++ > General > Additional Include Directories.
10. Replace `F:\boost_1_64_0` with `..\boost_1_64_0`.
It should look like this:
```
.;.\lib;.\lib\glew-2.0.0\include;.\lib\SDL2-devel-2.0.5-VC\SDL2-2.0.5\include;.\lib\SDL2_ttf-devel-2.0.14-VC\SDL2_ttf-2.0.14\include;.\lib\SDL2_mixer-devel-2.0.1-VC\SDL2_mixer-2.0.1\include;.\lib\SDL2_image-devel-2.0.1-VC\SDL2_image-2.0.1\include;.\lib\SDL2_net-devel-2.0.1-VC\SDL2_net-2.0.1\include;.\lib\SDL2_gfx-1.0.3;.\lib\soloud_20160109\include;.\lib\hyperic-sigar-1.6.4\sigar-bin\include;.\lib\poco-1.7.8p3-all\Foundation\include;.\lib\poco-1.7.8p3-all\JSON\include;.\lib\poco-1.7.8p3-all\Net\include;.\lib\poco-1.7.8p3-all\Util\include;.\lib\poco-1.7.8p3-all\XML\include;.\lib\poco-1.7.8p3-all\Zip\include;.\lib\enet-1.3.13\include;.\lib\zlib-1.2.8\include;.\lib\libzip-1.1.3\lib;.\lib\libzip-1.1.3\src;.\lib\zlib-1.2.8\contrib\minizip;.\lib\minilzo-2.09;.\lib\miniz-master;.\lib\cereal-master\include;..\boost_1_64_0;..\boost_1_64_0\stage\lib;.\lib\GWEN-master\gwen\include;%(AdditionalIncludeDirectories)
```
11. Click Apply then go to Linker.
12. Go to Additional Library Directories and Replace `F:\boost_1_64_0\stage\lib` with `..\boost_1_64_0\stage\lib`.
It should look like this:
```
.\lib\glew-2.0.0\lib;.\lib\SDL2-devel-2.0.5-VC\SDL2-2.0.5\lib\x86;.\lib\SDL2_ttf-devel-2.0.14-VC\SDL2_ttf-2.0.14\lib\x86;.\lib\SDL2_mixer-devel-2.0.1-VC\SDL2_mixer-2.0.1\lib\x86;.\lib\SDL2_image-devel-2.0.1-VC\SDL2_image-2.0.1\lib\x86;.\lib\SDL2_net-devel-2.0.1-VC\SDL2_net-2.0.1\lib\x86;.\lib\soloud_20160109\lib;.\lib\hyperic-sigar-1.6.4\sigar-bin\lib;.\lib\poco-1.7.8p3-all\_lib;.\lib\zlib-1.2.8\lib;.\lib\libzip-1.1.3\Release;..\boost_1_64_0\stage\lib;.\lib\GWEN-master\gwen\lib\windows\vs2010;%(AdditionalLibraryDirectories)
```
13. Click Apply then OK.
14. You need to compile GWEN and boost, follow the instructions below to compile them.
15. Right click bobsgame in the Solution Explorer and click Build.
16. Copy the `_copy.bat` in this repo to the `bobsgame` folder. It will make a `bob's game` folder on your desktop with all the files required.

### Compiling GWEN

#### GWEN-Static
*Skip over this section if you copied from this repository, but follow steps 4, 6, 7, 11 and 12.*
1. Head over to `C:\Users\Administrator\workspace\bobsgame\lib\GWEN-master\gwen\Projects` and open a terminal there.
2. Edit the `Build.bat` file and remove `rem` on the line where it says `rem premake4 vs2010`.
3. A Visual Studio 2010 project should be created in `C:\Users\Administrator\workspace\bobsgame\lib\GWEN-master\gwen\Projects\windows\vs2010`.
4. Open the solution in Visual Studio 2017, it will ask you to retarget projects, make sure your Windows SDK version is `10.0.19041.0` and the Platform Toolset is `Upgrade to v141`. Click OK.
5. Edit `C:\Users\Administrator\workspace\bobsgame\lib\GWEN-master\gwen\src\Platforms\gwen_platform_base.cpp` and add `#include <chrono>`.
6. Right click the `GWEN-Static` project and click "Properties".
7. Go to General (or Advanced) > Character Set and select "Not Set". Apply and click OK.

**TODO: Some way to do this without modifying file names and source.**

8. Rename `src/Bootil/Base.cpp` to `src/Bootil/BBase.cpp` and `src/Bootil/Threads/Utility.cpp` to `src/Bootil/Threads/TUtility.cpp`.
9. Rename all references to these functions to these:
```
IsKeyDown -> LIsKeyDown
IsLeftMouseDown -> LIsLeftMouseDown
IsRightMouseDown -> LIsRightMouseDown
OnMouseMoved -> LOnMouseMoved
OnMouseClicked -> LOnMouseClicked
OnKeyEvent -> LOnKeyEvent
OnCanvasThink -> LOnCanvasThink
```
10. Create a `version.txt` file and add a version number, it could be something like `3389`. However, this is not required to run the game.
11. Go to the release type and change it from Debug to Release.
12. Right click the GWEN-Static project and click Build.
13. The build should succeed and you should have a `gwen_static.lib` file in `C:\Users\User\Administrator\workspace\bobsgame\lib\GWEN-master\gwen\lib\windows\vs2010`.

####  GWEN-Renderer-OPENGL_TruetypeFont
*Skip this step if you copied from this repository, but build it still.*
1. Delete your `GWEN.sln` file in `C:\Users\User\Administrator\workspace\bobsgame\lib\GWEN-master\gwen\lib\windows\vs2010` and replace it with the one in the `gwen` folder with this guide.
2. Copy the files `Renderer-OpenGL_TruetypeFont.vcxproj`, `Renderer-OpenGL_TruetypeFont.vcxproj.filters`, and `Renderer-OpenGL_TruetypeFont.vcxproj.user` from the `gwen` folder with this guide to `C:\Users\User\Administrator\workspace\bobsgame\lib\GWEN-master\gwen\lib\windows\vs2010`.
3. Reload Visual Studio and build Renderer-OPENGL_TruetypeFont.

### Compiling Boost
1. Head to `C:\Users\User\Administrator\workspace\boost_1_64_0`.
2. Open a terminal and run `.\bootstrap.bat`.
3. Run `.\b2 runtime-link=static` until bootstrapping finishes. *This may take a while, like it says, ...patience...*

## Building bob's game for Linux
## Building bob's game for Mac OS <!-- i dont have a macbook so probably never -->

# Resources Used
- [ok on github](https://github.com/bobsgame/ok)
- [bob's game development live stream](https://www.youtube.com/watch?v=NVcExvl5AyU)
- [Bobs Game Archive](https://gitlab.com/RahimAli/bobs-game-archive)
