@echo off 
echo:

if /I [%1]==[] (
	echo Specify the run target. Example usage: "run main".
	exit /b 1
) 
if /I [%2]==[release] (
	echo Running bin/release/%1...
	"bin/release/%1"
) else (
	echo Running bin/debug/%1...
	"bin/debug/%1"
)