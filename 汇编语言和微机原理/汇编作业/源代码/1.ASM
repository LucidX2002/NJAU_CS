DATA SEGMENT
    SCORE DB 89,76,4,93,58,64,83,81,45,72,84
    NUM   DB 01,02,03,04,05,06,07,08,09,10,11
    SUM   DW 0
    AVE   DB 0
    CRLF  DB 0AH,0DH,'$'
    SC    DB '100~90',09H,'89~80',09H,'79~70',09H,'69~60',09H,'59~0',0DH,0AH,'$'
    MAXS  DB 0AH,0DH,'MAX=','$'
    MINS  DB 0AH,0DH,'MIN=','$'
    AVES  DB 0AH,0DH,'AVE=','$'
DATA ENDS

STK SEGMENT;堆栈段
    DB 20 DUP(?)
STK ENDS

CODE SEGMENT
    ASSUME DS:DATA,CS:CODE,SS:STK

MAIN PROC FAR

START:
    ;初始化
    MOV AX,DATA
    MOV DS,AX
    MOV AX,STK
    MOV SS,AX

    CALL SORT
    CALL PRINTTAB


    ;输出最高分
    LEA DX,MAXS
    MOV AH,09H
    INT 21H

    XOR AX,AX
    XOR BX,BX
    LEA SI,SCORE
    MOV AL,[SI]
    CALL PRINT

    ;输出最低分
    LEA DX,MINS
    MOV AH,09H
    INT 21H

    XOR AX,AX
    XOR BX,BX
    LEA SI,SCORE
    MOV AL,[SI+10]
    CALL PRINT

    ;输出平均成绩
    LEA DX,AVES
    MOV AH,09H
    INT 21H
    ;求和
    XOR AX,AX
    XOR BX,BX
    XOR DX,DX
    LEA SI,SCORE
    MOV CX,11
LP: 
    MOV BL,[SI]
    ADD AX,BX
    INC SI
    LOOP LP
    LEA DI,SUM
    MOV [DI],AX;和存储到SUM中

    MOV CX,0BH
    DIV CX
    LEA DI,AVE
    MOV [DI],AX

    CALL PRINT

    LEA DX,CRLF;换行
    MOV AH,09H
    INT 21H
    
    ;输出成绩排序结果
    LEA DI,SCORE
    MOV SI,DI
    MOV CX,11
LP1: 

    XOR AX,AX
    XOR BX,BX
    XOR DX,DX
    MOV AL,[SI]
    CALL PRINT

    MOV DL,20H;空格
    MOV AH,2
    INT 21H

    INC SI
    LOOP LP1
    ;输出成绩排序结果结束

    LEA DX,CRLF;换行
    MOV AH,9
    INT 21H

    MOV CX,11
    LEA SI,NUM

LP2:
    XOR AX,AX
    MOV AL,[SI]
    CALL PRINT

    MOV DL,20H;空格
    MOV AH,2
    INT 21H

    INC SI
    LOOP LP2
    ;输出成绩排序后对应的学号

    MOV AH,4CH
    INT 21H
MAIN ENDP

SORT PROC NEAR

    MOV BL,10;BL为外循环计数器
    LEA DI,SCORE;DI存放成绩初始地址

    ;外循环
NEXT1:
    MOV SI,DI
    MOV CL,BL;CL为内循环计数器

    ;内循环
NEXT2:
    MOV AL,[SI]
    INC SI
    CMP AL,[SI]
    JNC NEXT3;如果前>后跳过交换
    ;交换成绩
    MOV AH,[SI]
    MOV [SI-1],AH
    MOV [SI],AL
    ;交换编号
    MOV AX,SI
    SUB AX,DI
    ADD AX,OFFSET NUM
    PUSH SI;保护SI数据
    MOV SI,AX
    MOV AH,[SI]
    MOV AL,[SI-1]
    MOV [SI],AL
    MOV [SI-1],AH

    POP SI;返回SI之前的位置

    NEXT3:
    DEC CL
    JNZ NEXT2
    ;内循环结束

    DEC BL
    JNZ NEXT1
    ;外循环结束
    RET

SORT ENDP

PRINTTAB PROC NEAR

        ;输出区间人数
    LEA DX,SC;输出分数段字符串
    MOV AH,09H
    INT 21H

    LEA DI,SCORE
    MOV SI,DI
    MOV CX,4;循环4次
    XOR AX,AX
    XOR DX,DX
    MOV DH,90;DH存储区间下界

CP: 
    CMP [SI],DH
    JC PUT
    INC SI;指针右移
    INC DL;DL存储区间人数
    JMP CP
PUT:;小于DH 输出人数
    XOR AX,AX
    MOV AL,DL    
    MOV DL,0AH
    DIV DL
    MOV BX,AX
    MOV DL,BL
    ADD DL,30H
    MOV AH,02H
    INT 21H
    MOV DL,BH
    ADD DL,30H
    INT 21H

    MOV DL,09H;制表符号
    MOV AH,02H
    INT 21H
    XOR DL,DL
    SUB DH,10
    LOOP CP

    MOV AX,SI
    SUB AX,OFFSET SCORE
    MOV BX,11
    SUB BX,AX
    MOV AL,BL    
    MOV DL,0AH
    DIV DL
    MOV BX,AX
    MOV DL,BL
    ADD DL,30H
    MOV AH,02H
    INT 21H
    MOV DL,BH
    ADD DL,30H
    INT 21H
    RET

PRINTTAB ENDP

PRINT PROC NEAR

    MOV DL,0AH
    DIV DL
    MOV BX,AX
    MOV DL,BL
    ADD DL,30H
    MOV AH,02H
    INT 21H
    MOV DL,BH
    ADD DL,30H
    INT 21H
    RET

PRINT ENDP

CODE ENDS
    END START