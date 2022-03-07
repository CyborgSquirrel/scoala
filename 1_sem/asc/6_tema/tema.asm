bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dw -22, 145, -48, 127
    t equ $
    
    d resb (t-s) / 2

; our code starts here
segment code use32 class=code
    start:
        ; 6. Se da un sir de cuvinte s. Sa se construiasca sirul de octeti d, astfel incat d sa contina pentru fiecare pozitie din s:
        ; - numarul de biti de 0, daca numarul este negativ
        ; - numarul de biti de 1, daca numarul este pozitiv
        
        cld
        mov esi, s
        mov edi, d
        
        loop_1:
            lodsw
            mov bx, ax
            
            test bx, bx
            js negative
            positive:
                mov al, 0
                jmp finish
            negative:
                mov al, -8
                jmp finish
            finish:
            
            mov ecx, 8
            loop_2:
                ; am gasit folos pt. rcr :)))
                rcr bx, 1
                adc al, 0
                clc
            loop loop_2
            
            test al, al
            jns already_positive
                neg al
            already_positive:
            
            stosb
            cmp esi, t
        jne loop_1
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
