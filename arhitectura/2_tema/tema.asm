bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a resb 1
    b resb 1
    c resb 1
    d resb 1
    e resw 1
    f resw 1
    g resw 1
    h resw 1

; our code starts here
segment code use32 class=code
    start:
        ; Exerciții simple
        ; 15. 6*3
        mov al, 6
        mov cl, 3
        mul cl
        ; rezultatul e in AX
        
        ; Adunări, scăderi
        ; a,b,c,d - byte
        ; 22. (a+b+b)-(c+d)
        mov byte [a], 3
        mov byte [b], 4
        mov byte [c], 5
        mov byte [d], 6
        
        ; (a+b+b)
        mov al, [a]
        add al, [b]
        add al, [b]
        
        ; (c+d)
        mov dl, [c]
        add dl, [d]
        
        ; (a+b+b)-(c+d)
        sub al, dl
        
        ; (3+4+4)-(5+6)=0
        ; rezultatul este in AL
        
        ; Înmulțiri, împărțiri
        ; a,b,c,d-byte, e,f,g,h-word
        ; 21. (f*g-a*b*e)/(h+c*d)
        mov byte [a], 7
        mov byte [b], 3
        mov byte [c], 11
        mov byte [d], 4
        mov word [e], 5
        mov word [f], 8
        mov word [g], 21
        mov word [h], 6
        
        ; c*d
        mov al, [c]
        mul byte [d]
        
        ; (h+c*d)
        add ax, [h]
        mov cx, ax
        
        ; a*b*e
        mov al, [a]
        mul byte [b]
        mul word [e]
        mov bx, ax
        
        ; f*g
        mov ax, [f]
        mul word [g]
        
        ; (f*g-a*b*e)
        sub ax, bx
        
        ; (f*g-a*b*e)/(h+c*d)
        div cx
        
        ; (8*21-7*3*5)/(6+11*4)=1
        ; rezultatul este in AX
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
