bits 32

global start        

extern exit
import exit msvcrt.dll

extern gets, printf
import gets msvcrt.dll
import printf msvcrt.dll

extern fopen, fclose, fread
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll

segment data use32 class=data
    path_format db "Introduceti numele fisierului: ",0
    path resb 256
    
    fail_format db "Fisierul '%s' nu a putut fi deschis",0
    access_mode db "r",0
    file resd 1
    
    bufferlen equ 256
    buffer resb bufferlen
    
    answer_format db "Numarul de biti din fisierul '%s' este: %d",0

segment code use32 class=code
    start:
        ; numaram cati biti de 1 sunt in fisier
        
        push dword path_format
        call [printf]
        add esp, 4
        
        push dword path
        call [gets]
        add esp, 4
        
        push dword access_mode
        push dword path
        call [fopen]
        add esp, 4*2
        
        mov [file], eax
        test eax, eax
        jz fail
        
        mov edx, 0
        
        reading:
            push edx
                push dword [file]
                push dword bufferlen
                push dword 1
                push dword buffer
                call [fread]
                add esp, 4*4
            pop edx
            
            test eax, eax
            jz answer
            
            mov ecx, eax
            mov esi, buffer
            cld
            iterating_bytes:
                lodsb
                iterating_bits:
                    shr al, 1
                    adc edx, 0
                    test al, al
                jnz iterating_bits
            loop iterating_bytes
        jmp reading
        
        fail:
            push dword path
            push dword fail_format
            call [printf]
            add esp, 4*2
        jmp fin
        
        answer:
            push edx
                push dword [file]
                call [fclose]
                add esp, 4
            pop edx
            
            push dword edx
            push dword path
            push dword answer_format
            call [printf]
            add esp, 4*3
        jmp fin
            
        fin:
            push    dword 0
            call    [exit]
