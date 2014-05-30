P_STACKBASE	equ	0
GSREG		equ	P_STACKBASE
FSREG		equ	GSREG		+ 4
ESREG		equ	FSREG		+ 4
DSREG		equ	ESREG		+ 4
EDIREG		equ	DSREG		+ 4
ESIREG		equ	EDIREG		+ 4
EBPREG		equ	ESIREG		+ 4
KERNELESPREG	equ	EBPREG		+ 4
EBXREG		equ	KERNELESPREG	+ 4
EDXREG		equ	EBXREG		+ 4
ECXREG		equ	EDXREG		+ 4
EAXREG		equ	ECXREG		+ 4
RETADR		equ	EAXREG		+ 4
EIPREG		equ	RETADR		+ 4
CSREG		equ	EIPREG		+ 4
EFLAGSREG	equ	CSREG		+ 4
ESPREG		equ	EFLAGSREG	+ 4
SSREG		equ	ESPREG		+ 4
P_STACKTOP	equ	SSREG		+ 4
P_LDT_SEL	equ	P_STACKTOP
P_LDT		equ	P_LDT_SEL	+ 2
TSS3_S_SP0	equ	4

extern _KeTSS
extern _PStartProcess


global __asm_KeLoadTSS;
global __asm_Restart;

__asm_KeLoadTSS:
push ebp
mov ebp,esp
push eax
;mov eax,dword [ss:ebp+8]
mov eax,56
ltr ax
pop eax
mov esp,ebp
pop ebp
ret


__asm_Restart:
mov esp,[_PStartProcess]
lea eax,[esp+P_STACKTOP]
mov dword [_KeTSS+TSS3_S_SP0],eax

pop gs
pop fs
pop es
pop ds
popad 
add esp,4
iretd
