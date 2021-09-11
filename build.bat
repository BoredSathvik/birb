echo off
echo run this in the developer command line if you havent already and install cmake thanks, ill fix this later maybe
REM make client
cmake .
cmake --build . --config Release

REM copy it all to an output directory
mkdir build
copy client\Release\Birb.dll build\birb.dll
copy Injector\Release\Injector.exe build\Injector.exe

@REM del /q /s "*.vcxproj"
@REM del /q /s "*.csproj"
@REM del /q /s "*.vcxproj.*"
@REM del /q "*.sln"
@REM del /q /s "cmake_install.cmake"
@REM del /q /s "CMakeCache.txt"
@REM rmdir /s /q "Birb.dir"
@REM rmdir /s /q "CMakeFiles"