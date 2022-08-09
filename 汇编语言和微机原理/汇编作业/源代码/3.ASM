DATA SEGMENT
    NUM1 DB 0,0
    NUM2 DB 0,0
    SUM DW 0,0
    STR1 DB 'Please input two numbers in DEC:',0AH,0DH,'$'
    SUM1 DB 'Sum in HEX is:',0AH,0DH,'$'
    STR2 DB 'Please input two numbers In HEX:',0AH,0DH,'$'
    SUM2 DB 'Sum in DEC is:',0AH,0DH,'$'
    CRLF DB 0AH,0DH,'$'
DATA ENDS

STK SEGMENT
    DB 128 DUP(0)
STK ENDS

CODE SEGMENT
    ASSUME CS:CODE, DS:DATA, SS:STK
START:
    MOV AX,DATA
    MOV DS,AX
    MOV AX,STK
    MOV SS,AX
    LEA DX,STR1
    MOV AH,09
    INT 21H
IN1:
    MOV AH,01H
    INT 21H
    MOV NUM1[0],AL
    SUB NUM1[0],30H

    MOV AH,01H
    INT 21H
    MOV NUM1[1],AL
    SUB NUM1[1],30H

    LEA DX,CRLF
    MOV AH,9
    INT 21H

AD1:
    MOV BL,NUM1[0]
    ADD BL,NUM1[1]
    MOV SUM[0],BX

RESHEX:
    LEA DX,SUM1
    MOV AH,9
    INT 21H

    MOV AX,SUM[0]
    CMP AX,16
    JG OUTNUM
    CMP AX,10
    JB OUTNUM
    JMP OUTCHAR

OUTNUM:
    MOV BX,16
    MOV CX,0
    MOV DX,0
S1:
    DIV BX
    PUSH DX
    INC CX
    CWD
    CMP AX,0
    JNE S1
S2:
    POP DX
    ADD DL,30H
    MOV AH,02H
    INT 21H
    LOOP S2
    JMP OUTHEX

OUTCHAR:
    MOV DX,0
    SUB AX,10
    MOV DL,AL
    ADD DL,65
    MOV AH,02H
    INT 21H
    JMP OUTHEX

OUTHEX:
    LEA DX,CRLF
    MOV AH,09
    INT 21H
    LEA DX,STR2
    MOV AH,9
    INT 21H
    MOV AH,01H
    INT 21H
    MOV NUM2[0],AL
    MOV AH,01H
    INT 21H
    MOV NUM2[1],AL

    LEA DX,CRLF
    MOV AH,9
    INT 21H
    LEA DX,SUM2
    MOV AH,9
    INT 21H

JUD PROC NEAR
  
    MOV CX,2
    MOV SI,0
    MOV BX,0
ADD2:
    MOV AL,NUM2[SI]
    CMP AL,57
    JG TO_DEC

ADD_AGAIN:

    SUB NUM2[SI],30H
AD: INC SI
    LOOP ADD2
    JMP RESULT_DEC
  
TO_DEC:
    SUB AL,65
    ADD AL,48
    SUB AL,38
    SUB AL,32
    MOV NUM2[SI],AL
    JMP AD
    RET
JUD ENDP

RESULT_DEC:

    MOV BL,NUM2[0]
    ADD BL,NUM2[1]
    MOV SUM[2],BX
    JMP OUTNUM2

OUTNUM2 PROC NEAR

    MOV AX,BX
    MOV BX,10
    MOV CX,0
    MOV DX,0

T1:

    DIV BX
    PUSH DX
    INC CX
    CWD
    CMP AX,0
    JNE T1

T2:

    POP DX
    ADD DL,30H
    MOV AH,02H
    INT 21H
    LOOP T2
    JMP EXIT
    RET

OUTNUM2 ENDP

EXIT:
    MOV AX,4C00H
    INT 21H

CODE ENDS
    END START

