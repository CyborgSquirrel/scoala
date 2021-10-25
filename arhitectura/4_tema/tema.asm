bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A db 0b10101010
    ;      76543210
    B db 0b11100011
    ;      76543210
    C resd 1

; our code starts here
segment code use32 class=code
    start:
        ; 5. Se dau octetii A si B. Sa se obtina dublucuvantul C:
        mov dword [C], 0
        
        ; bitii 16-31 ai lui C sunt 1
        or dword [C], 0xFFFF0000
        
        ; bitii 0-3 ai lui C coincid cu bitii 3-6 ai lui B
        mov eax, 0
        mov al, [B]
        shr al, 3
        and al, 0x0F
        or dword [C], eax
        
        ; bitii 4-7 ai lui C au valoarea 0
        ; deja au valoarea 0
        
        ; bitii 8-10 ai lui C au valoarea 110
        mov eax, 0b110
        shl eax, 8
        or dword [C], eax
        
        ; bitii 11-15 ai lui C coincid cu bitii 0-4 ai lui A
        mov eax, 0
        mov al, [A]
        and al, 0b00011111
        shl eax, 11
        or dword [C], eax
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
