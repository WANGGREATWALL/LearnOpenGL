@echo off
set build_dir=build

if exist %build_dir% (
    echo Clearing %build_dir%...
    rmdir /q /s %build_dir%
)

echo Creating %build_dir%...
mkdir %build_dir%

@echo off
cd %build_dir%

cmake -G "Visual Studio 16 2019" ${COMMON_CMAKE_CONFIG_PARAMS} ../
cmake --build . --config Release

