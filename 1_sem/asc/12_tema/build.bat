set vs="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"
call %vs%

nasm mystrcat.asm -fwin32 -o mystrcat.obj
cl main.c /link mystrcat.obj

pause