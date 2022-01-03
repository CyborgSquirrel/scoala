bits 32 ; assembling for the 32 bits architecture

global _mystrcat

; our code starts here
segment code use32 class=code public

; void mystrcat(char *dest, char *src)
_mystrcat:
    push ebp
    mov ebp, esp
    
    pushfd
    push edi
    push esi
        mov edi, [ebp+8]
        mov esi, [ebp+12]
        
        cld
        
        mov ecx, -1
        mov al, 0
        repne scasb
        dec edi
        
        .loop:
            lodsb
            stosb
            test al, al
        jnz .loop
    pop esi
    pop edi
    popfd
    
    mov esp, ebp
    pop ebp
    
    ret