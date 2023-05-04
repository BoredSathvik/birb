echo off

@REM git submodule update --init --recursive

@REM cd client/Lib/PolyHook_2_0
@REM cmake -B"./_build" -DCMAKE_INSTALL_PREFIX="./_install/" -DPOLYHOOK_BUILD_SHARED_LIB=OFF
@REM cmake --build "./_build" --config Debug --target INSTALL
@REM cd ../../../

cmake .
cmake --build . --config Debug

mkdir build\debug
copy client\Debug\Birb.dll build\debug\birb.dll
copy Injector\Debug\Injector.exe build\debug\Injector.exe