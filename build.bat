@echo off 
echo:

if /I [%1]==[release] (
	echo Building release executable files with CMake...
	cd build/release
) else (
	echo Building debug executable files with CMake...
	cd build/debug
)
cmake --build .
cd ../..