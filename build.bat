echo off
echo run this in the developer command line if you havent already and install cmake thanks, ill fix this later maybe
REM make client
cmake .
cmake --build . --config Release

REM copy it all to an output directory
mkdir build
copy client\Release\Birb.dll build\birb.dll
copy Injector\Release\Injector.exe build\Injector.exe

del /q /s "*.vcxproj"
del /q /s "*.csproj"
del /q /s "*.vcxproj.*"
del /q "*.sln"
del /q /s "cmake_install.cmake"
del /q /s "CMakeCache.txt"
rmdir /s /q "Birb.dir"
rmdir /s /q "CMakeFiles"