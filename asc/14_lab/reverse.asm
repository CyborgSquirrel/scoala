bits 32

global start

extern exit
import exit msvcrt.dll

extern malloc
import malloc msvcrt.dll

extern fopen, fread, fseek, ftell, fputs, fclose
import fread msvcrt.dll
import fopen msvcrt.dll
import fseek msvcrt.dll
import ftell msvcrt.dll
import fputs msvcrt.dll
import fclose msvcrt.dll

SEEK_SET equ 0
SEEK_END equ 2

segment data use32 class=data
    buf_size dd 0
    buf dd 0
    in_name db "file.txt",0
    in_mode db "r",0
    in_file dd 0
    out_name db "reverse.txt",0
    out_mode db "a",0
    out_file dd 0

segment code use32 class=code
    start:
        ; reverse la un fisier text
        push dword in_mode
        push dword in_name
        call [fopen]
        mov [in_file], eax
        add esp, 4*2
        
        push dword SEEK_END
        push dword 0
        push dword [in_file]
        call [fseek]
        add esp, 4*3
        
        test eax, eax
        jnz fin
        
        push dword [in_file]
        call [ftell]
        mov [buf_size], eax
        add esp, 4*1
        
        test eax, eax
        jb fin
        
        push dword [buf_size]
        call [malloc]
        add esp, 4*1
        
        test eax, eax
        jz fin
        mov [buf], eax
        
        push dword SEEK_SET
        push dword 0
        push dword [in_file]
        call [fseek]
        add esp, 4*3
        
        push dword [in_file]
        push dword [buf_size]
        push dword 1
        push  buf
        call [fread]
        add esp, 4*4
        
        push dword [in_file]
        call [fclose]
        add esp, 4*1
        
        mov ecx, [buf_size]
        shr ecx, 1
        jecxz fin
        reversing:
            mov al, [buf+ecx]
            mov edx, [buf_size]
            sub edx, ecx
            mov ah, [buf+edx]
            
            mov [buf+ecx], ah
            mov [buf+edx], al
        loop reversing
        
        push dword out_mode
        push dword out_name
        call [fopen]
        add esp, 4*2
        mov [out_file], eax
        
        push dword [out_file]
        push dword buf
        call [fputs]
        add esp, 4*2
        
        fin:
            push    dword 0
            call    [exit]