bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

extern scanf, printf
import scanf msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    scanf_format db "%d",0
    printf_format db "%d/%d = %d",0
    
    a dd 0
    b dw 0

; our code starts here
segment code use32 class=code
    start:
        ; 6. Se dau doua numere naturale a si b (a: dword, b: word, definite in segmentul de date). Sa se calculeze a/b si sa se afiseze catul impartirii in urmatorul format: "<a>/<b> = <cat>"
        ; Exemplu: pentru a = 200 si b = 5 se va afisa: "200/5 = 40"
        ; Valorile vor fi afisate in format decimal (baza 10) cu semn.
        
        ; int scanf ( const char * format, &a )
        push a            ; &a
        push scanf_format ; format
        call [scanf]
        add esi, 4*2
        
        ; int scanf ( const char * format, &b )
        push b            ; &b
        push scanf_format ; format
        call [scanf]
        add esi, 4*2
        
        ; a/b
        mov ax, [a]
        mov dx, [a+2]
        mov bx, [b]
        idiv bx
        
        ; int printf ( const char * format, a, b, ax )
        cwde
        push eax           ; ax
        mov ax, [b]
        cwde
        push eax           ; b
        push dword [a]     ; a
        push printf_format ; format
        call [printf]
        add esi, 4*4
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
