nasm -fobj main.asm
nasm -fobj criptare.asm
nasm -fobj maxvocale.asm
nasm -fobj nrvocale.asm
alink main.obj criptare.obj maxvocale.obj nrvocale.obj -oPE -subsys console -entry start
pause