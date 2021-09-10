@echo off
echo run this in the developer command line if you havent already and install cmake thanks, ill fix this later maybe
REM make client

./Client/build.bat

REM make injector
msbuild CLInjector/CLInjector.csproj

REM copy it all to an output directory
mkdir build
copy client\Release\Birb.dll build\birb.dll
copy CLInjector\build\CLInjector.exe build\CLInjector.exe