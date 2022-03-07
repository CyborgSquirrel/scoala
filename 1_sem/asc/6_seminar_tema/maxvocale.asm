bits 32 
global maxvocale 
Extern nrvocale 

segment data use32 class=data public 
	Maxim dd 0 

segment code use32 class=code public 

;[esp] – adresa de revenire 
;[esp + 4] – adresa numarului maxim de vocale curent 
;[esp + 8] - sirul curent pentru care verificam daca are numar maxim de vocale 
maxvocale: 
	Mov ecx, [esp+4] 
	Mov edx,0         
	Mov esi, [esp + 8] 

	push ecx
	Push dword esi 
	Call nrvocale 
	pop ecx
	Add esp, 4*1 

	Cmp [ecx], eax 
	Ja sari_si_peste_astaa 
	Mov [ecx], eax 
	Mov edx,1 
	sari_si_peste_astaa: 
	
	Mov eax,edx 
	; returneaza 1 daca a setat maxim pentru sirul testat si 0 altfel 
	ret 