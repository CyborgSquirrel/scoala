bits 32                         
segment code use32 public code

global mystrcat

; void mystrcat(char *destination, char *source)
mystrcat:
    cld

    mov edi, [esp + 4  ]
    mov esi, [esp + 4*2]
    
    mov ecx, -1
    mov al, 0
    repne scasb
    dec edi
    
    .loop:
        mov al, [esi]
        test al, al
        jz .return
        
        movsb
    jmp .loop
    
    .return:
        movsb
        ret