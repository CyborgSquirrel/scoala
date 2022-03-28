bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll

                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)

extern fopen, fread, fclose
import fopen msvcrt.dll
import fread msvcrt.dll
import fclose msvcrt.dll

extern printf
import printf msvcrt.dll

segment data use32 class=data
    nume_fisier db "nice.txt",0
    mod_access db "r",0
    descriptor dd 0
    len equ 100
    buffer resb len
    
    lenfrecventa equ 10
    frecventa times lenfrecventa dd 0
    
    format db "Cifra cu frecventa maxima este %d si apare de %d ori.",0

; our code starts here
segment code use32 class=code
    start:
        ; 6. Se da un fisier text. Sa se citeasca continutul fisierului, sa se determine cifra cu cea mai mare frecventa si sa se afiseze acea cifra impreuna cu frecventa acesteia. Numele fisierului text este definit in segmentul de date.
        
        ; FILE * fopen(const char* nume_fisier, const char * mod_acces)
        push mod_access
        push nume_fisier
        call [fopen]
        add esp, 2 * 4
        
        test eax, eax
        jz forfeit ; dam forfeit daca nu poate fi deschis fisierul
        mov [descriptor], eax
        
        cld
        citire:
            ; int fread(void * str, int size, int count, FILE * descriptor)
            push dword [descriptor]
            push dword len
            push dword 1
            push dword buffer
            call [fread]
            add esp, 4 * 4
            
            mov ecx, eax
            jecxz stop_citire
            
            mov esi, buffer
            calcul_frecventa:
                mov eax, 0
                lodsb
                sub eax, '0'
                
                cmp eax, 9
                ja nu_e_cifra
                    inc dword [frecventa+eax*4]
                nu_e_cifra:
            loop calcul_frecventa
        jmp citire
        stop_citire:
        
        ; int fclose(FILE * descriptor)
        push dword [descriptor]
        call [fclose]
        add esi, 1 * 4
        
        mov eax, 0
        mov ebx, [frecventa+0*4]
        mov ecx, 1
        cautare_frecventa_maxima:
            mov edx, [frecventa+ecx*4]
            cmp edx, ebx
            jbe frecventa_mai_mica
                mov ebx, edx
                mov eax, ecx
            frecventa_mai_mica:
            
            inc ecx
            cmp ecx, lenfrecventa
        jb cautare_frecventa_maxima
        
        ; int printf(const char * format, cifra, frecventa);
        push dword ebx    ; frecventa
        push dword eax    ; cifra
        push dword format
        call [printf]
        add esi, 3 * 4
        
    forfeit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
