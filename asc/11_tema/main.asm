bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern printf, gets
import printf msvcrt.dll
import gets msvcrt.dll

extern mystrcat

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    print_format db "%s",13,10,0
    
    s resb 255
    
    d db 0
    resb 254

; our code starts here
segment code use32 class=code
    start:
        ; 6. Se citesc trei siruri de caractere. Sa se determine si sa se afiseze rezultatul concatenarii lor.
        
        ; citim si concatenam primul string
        push s
        call [gets]
        add esp, 4
        
        push s
        push d
        call mystrcat
        add esp, 4*2
        
        ; citim si concatenam al doilea string
        push s
        call [gets]
        add esp, 4
        
        push s
        push d
        call mystrcat
        add esp, 4*2
        
        ; citim si concatenam al treilea string
        push s
        call [gets]
        add esp, 4
        
        push s
        push d
        call mystrcat
        add esp, 4*2
        
        ; afisam
        push d
        push print_format
        call [printf]
        add esp, 4*2
        
        ; mai citim inca odata, ca programul sa nu se inchida
        push s
        call [gets]
        add esp, 4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
