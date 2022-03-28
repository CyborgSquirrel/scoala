bits 32 
global criptare 

segment data use32 class=data public 
    Vocale db 'AEIOUaeiou',0 

segment code use32 class=code public 

;criptare(sirAsciiZ,dest) 
; [ESP] <- adresa de revenire 
; [ESP+4] <- adresa unui sirAsciiZ 
; [ESP+8] <- adresa sirului destinatie 
criptare: 
    MOV ESI, [ESP+4] 
    MOV EDI, [ESP+8] 
    cld 
    bucla: 
        LODSB 
        CMP AL,0 
        JZ  final 
        MOV EBX, Vocale 
        ParcurgeVocale:
            MOV DL,[EBX] 
            CMP DL,0 
            JZ poateCaEConsoana 
            CMP AL,DL 
            JE  criptarevocala 
            INC EBX 
        JMP ParcurgeVocale 
    JMP poateCaEConsoana 

criptarevocala:
    STOSB 
    MOV AL, 'p'
    STOSB 
    MOV AL, DL 
    STOSB         
    JMP urmatorul    

poateCaEConsoana: 
    ; a<= … <=z sau A<= … <=Z 
    CMP AL, 'A' 
    JB altceva 
    CMP AL, 'Z' 
    JBE criptareconsoana 
    CMP AL, 'a' 
    JB altceva 
    CMP AL, 'z' 
    JBE criptareconsoana 

altceva:
    STOSB  

JMP urmatorul 

criptareconsoana: 
    ADD AL,20 
    STOSB 

urmatorul: 
    JMP bucla 

final: 
    ret 

 