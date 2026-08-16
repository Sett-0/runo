@echo off 
echo:

if /I [%1]==[release] (
	echo Generating release build files with CMake...
	cd build/release
	cmake ../.. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
) else (
	echo Generating debug build files with CMake...
	cd build/debug
	cmake ../.. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
)
cd ../..