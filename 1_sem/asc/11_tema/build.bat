nasm -fobj main.asm
nasm -fobj mystrcat.asm
alink main.obj mystrcat.obj -oPE -subsys console -entry start
pause