bits 32
global start

extern exit
import exit msvcrt.dll

extern maxvocale, criptare

extern printf, scanf, gets
import printf msvcrt.dll
import scanf msvcrt.dll
import gets msvcrt.dll

segment data use32 class=data public
    format db '%d',0
    N dd 0
    
    print_format db '%s',0
    forman db '%s',0
    Sir times 101 db 0
    SirCuNrMaximVocale times 101 db 0
    NrMaximVocale dd 0

; retinem doar sirul curent si sirul “maxim” curent 

segment code use32 class=code public 
    start: 
        ; citim N 
        push dword N
        push dword format
        call [scanf]
        add esp, 4*2
        
        cld
        
        ; citim pe rand sirul de caractere
        mov ecx, [N]
        jecxz forfeit
        lupus:
            push ecx
                push dword Sir
                push dword forman
                call [scanf]
                add esp, 4*2
                
                ; pentru fiecare sir citit apelez maxvocale 
                
                push dword Sir
                push dword NrMaximVocale
                call maxvocale
                add esp, 4*2
            pop ecx
            
            ; daca eax = 1 (returnat de maxvocale) atunci modific sircunrmaximvocale altfel nu fac nimic 
            test eax, eax
            jz nope
                mov edi, SirCuNrMaximVocale
                mov esi, Sir
                inner_lupus:
                    lodsb
                    stosb
                    test al, al
                jnz inner_lupus
            nope:
        loop lupus
        
        ; la finalul parcurgerii apelez criptare pentru sircunrmaximvocale 
        push Sir
        push SirCuNrMaximVocale
        call criptare
        
        push Sir
        push print_format
        call [printf]
        add esp, 4*2
        
        forfeit:
            push  dword 0 
            call [exit] 