bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A db 2, 1, -3, 0
    LA equ $-A
    B db 4, 5, 7, 6, 2, 1
    LB equ $-B
    
    LR equ LA+LB
    R times LR db 0

; our code starts here
segment code use32 class=code
    start:
        ; 24. Se dau 2 siruri de octeti A si B. Sa se construiasca sirul R care sa contina elementele lui B in ordine inversa urmate de elementele in ordine inversa ale lui A.
        
        mov ebx, R
        
        mov ecx, B+LB
    loop_1:
        dec ecx
        
        mov al, [ecx]
        mov [ebx], al
        
        inc ebx
        
        cmp ecx, B
    jne loop_1
    ; sfarsit loop_1
        
        mov ecx, A+LA
    loop_2:
        dec ecx
        
        mov al, [ecx]
        mov [ebx], al
        
        inc ebx
        
        cmp ecx, A
    jne loop_2
    ; sfarsit loop_2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
