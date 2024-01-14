@echo off
set dir_debug=build/Debug

if exist %dir_debug% (
    @echo off
    cd %dir_debug%
    LearnOpenGL.exe
) else (
    @echo off
    cd build/Release
    LearnOpenGL.exe
)

@echo off
cd ../../