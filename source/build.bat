@echo off

set CommonCompilerFlags=-Od -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -WX -W4 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Z7
set CommonLinkerFlags= user32.lib gdi32.lib opengl32.lib

IF NOT EXIST ..\build mkdir ..\build
pushd ..\build

del *.pdb > NUL 2> NUL

cl %CommonCompilerFlags%  -Fegame.dll ..\source\hoki.c -LD /link -incremental:no -PDB:game_%random%.pdb -opt:ref -EXPORT:game_init -EXPORT:game_render
cl %CommonCompilerFlags%  -Fewin32.exe ..\source\win32_main.c %CommonLinkerFlags%

popd
