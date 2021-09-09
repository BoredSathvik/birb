echo run this in the developer command line if you havent already
REM make client

cmake client/ 
cmake --build client/ --config Release

REM make injector
msbuild CLInjector/CLInjector.csproj

REM copy it all to an output directory
mkdir build
copy client/Release/Birb.dll build
copy CLInjector/build/CLInjector.exe build