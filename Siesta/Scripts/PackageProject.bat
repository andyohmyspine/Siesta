@echo off
set Macros

cmake .. -B.DevFiles --fresh %Macros%
cmake --build ../.DevFiles --config MinSizeRel --target Editor
rmdir /s /q .\.DevFiles