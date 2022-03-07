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
    b resw 1
    c resd 1
    d dq 6103972242941433277
    
    e resd 1
    x dq -58696962789

; our code starts here
segment code use32 class=code
    start:
        ; jmp susta
        
        ; a - byte, b - word, c - doubleword, d - qword - Interpretare cu semn
        ; 26. (c-d-a)+(b+b)-(c+a)
        mov byte  [a], -54
        mov word  [b], 21653
        mov dword [c], -1516587723
        
        ; (b+b)
        mov ax, [b]
        cwde
        add eax, eax
        mov ebx, eax
        
        ; (c+a)
        mov al, [a]
        cbw
        cwde
        mov ecx, eax
        add eax, [c]
        
        ; (b+b)-(c+a)
        sub ebx, eax
        
        ; (c-d-a)
        mov eax, [c]
        cdq
        
        sub eax, [d+0]
        sbb edx, [d+4]
        
        sub eax, ecx
        sbb edx, 0
        
        ; (c-d-a)+(b+b)-(c+a)
        add eax, ebx
        adc edx, 0
        
        ; rezultatul este in EDX:EAX
        ; ((-1,516,587,723)-6,103,972,242,941,433,277-(-54))+(21,653+21,653)-((-1,516,587,723)+(-54)) = -6,103,972,242,941,389,863 = AB4A5595:D4A253D9
        
        ; a,b,c - byte, e - doubleword, x - qword
        ; 19. (a+a+b*c*100+x)/(a+10)+e*a
        
        mov byte [a], -107
        mov byte [b], 72
        mov byte [c], 85
        mov dword [e], 1421109589
        
        ; b*c*100
        mov al, [b]
        imul byte [c]
        mov bx, 100
        imul bx
        
        push dx
        push ax
        pop ebx
        
        ; a+a
        mov al, [a]
        cbw
        cwde
        mov ecx, eax ; salvez a-ul convertit pe 32 de biti, ca sa-l folosesc la (a+10) si e*a
        add eax, eax
        
        ; (a+a+b*c*100+x)
        cdq
        add eax, ebx
        adc edx, 0
        
        add eax, [x+0]
        adc edx, [x+4]
        
        ; (a+10)
        mov ebx, ecx
        add ebx, 10
        
        ; (a+a+b*c*100+x)/(a+10)
        idiv ebx
        mov ebx, eax
        
        ; e*a
        mov eax, ecx
        imul dword [e]
        
        ; (a+a+b*c*100+x)/(a+10)+e*a
        add eax, ebx
        adc edx, 0
        
        ; rezultatul este in EDX:EAX
        ; ((-107)+(-107)+72*85*100+(-58,696,962,789))/((-107)+10)+1,421,109,589*(-107) = -151,453,609,003 = FFFFFFDC:BCA953D5
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
