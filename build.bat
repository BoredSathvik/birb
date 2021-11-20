echo off

git submodule update --init --recursive

cd client/Lib/PolyHook_2_0
cmake -B"./_build" -DCMAKE_INSTALL_PREFIX="./_install/" -DPOLYHOOK_BUILD_SHARED_LIB=OFF
cmake --build "./_build" --config Release --target INSTALL
cd ../../../

cmake .
cmake --build . --config Release

mkdir build
copy client\Release\Birb.dll build\birb.dll
copy Injector\Release\Injector.exe build\Injector.exe