bits 32 
global nrvocale 

segment data use32 class=data public 
    Vocale2 db 'AEIOUaeiou',0 

segment code use32 class=code public 

;eax=nrvocale(sirAsciiZ) 
;[esp] – adresa de revenire 
;[esp + 4] – sirul 
nrvocale: 
    Mov esi, [esp+4] 
    Mov edx, 0 
    Cld 
    Again: 
        Lodsb 
        Cmp al,0 
        Je afara 
        Mov bl,al ; caracter actual 

        Mov ecx, 10 ; nr vocale 

        Push esi 
        Mov esi, Vocale2 
        Cauta: 
            Lodsb 
            Cmp al,bl 
            Jne sari_peste 
            Mov ecx, 1 
            inc edx 

            sari_peste: 
        Loop Cauta 

        Pop esi 
        Jmp Again 
    
    afara: 
        Mov eax,edx 
        
        ret