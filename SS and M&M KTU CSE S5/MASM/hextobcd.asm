ASSUME CS:CODE,DS:DATA
DATA SEGMENT
HEX DW 0FFEFH
DATA ENDS
CODE SEGMENT
START:	MOV AX,DATA
	MOV DS,AX
	MOV AX,HEX
	MOV SI,1600H
	MOV WORD PTR[SI],0000H
	MOV CX,0AH
CONV:	MOV DX,00H
	DIV CX
	MOV [SI],DL
	INC SI
	CMP AX,CX
	JAE CONV
	MOV [SI],AL
	MOV AH,4CH
	INT 21H
CODE ENDS
	END START
