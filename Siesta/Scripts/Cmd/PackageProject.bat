@echo off
set Macros

cmake .. -B.DevFiles --fresh %Macros%
cmake --build ../.DevFiles --config MinSizeRel --target Siesta.Editor
rmdir /s /q .\.DevFiles