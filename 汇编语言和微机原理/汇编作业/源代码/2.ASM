DATA SEGMENT
    SCORE   DB  11 DUP(?)
    S       DB  'The score between ','$'
    S1      DB  'The score between 0 and 59 :','$'
    AD      DB  ' and ','$'
    CO      DB  ' :','$'
    M1      DB  'Min is ','$'
    M2      DB  'Max is ','$'
    M3      DB  'Mid is ','$'
    WT      DB  'Please input 11 scores separated by space:',0AH,0DH,'$'
    RANK    DB  'Rank order : ','$'
    CRLF    DB  0AH,0DH,'$'
DATA ENDS

STK SEGMENT
    DB 20 DUP(?)
STK ENDS

CODE SEGMENT
    ASSUME DS:DATA,SS:STK,CS:CODE

MAIN PROC FAR

START:
    ;初始化
    MOV AX,DATA
    MOV DS,AX
    MOV AX,STK
    MOV SS,AX

    ;输入11名学生成绩
    LEA DX,WT
    MOV AH,09H
    INT 21H

    MOV CX,11;输入11个字符
LP: MOV AH,1;1号功能 输入一个字符
    INT 21H
    CMP AL,' ';和空格比较
    JZ  LP;如果空格重新输入
    
    ;分析两个空格中的数字大小
    SUB AL,30H
    MOV DH,AL;把第一位数放到DH中 
    MOV BL,0AH

CUL:
    MOV AH,1
    INT 21H
    CMP AL,' '
    JZ PUT
    SUB AL,30H
    MOV DL,AL
    MOV AH,0
    MOV AL,DH
    MUL BL
    ADD AL,DL
    MOV DH,AL
    JMP CUL

PUT:
    MOV [SI],DH
    INC SI
    LOOP LP
    ;输入成绩结束

    LEA DX,CRLF
    MOV AH,09H
    INT 21H

    CALL SORT
;输出区间人数
    ;初始化
    LEA DI,SCORE;DI存储分数段首地址
    MOV SI,DI
    XOR AX,AX
    XOR BX,BX
    MOV BL,90;区间下界
    MOV CX,4;先输出前四个区间人数
    XOR DX,DX
    
JUD:
    PUSH CX;保护CX之前的数据
    CMP [SI],BL
    JC SC;如果小于当前区间下界跳转到SC输出区间人数
    INC BH;BH存储当前区间人数
    ADD SI,1
    JMP JUD
    ;输出当前区间人数
SC: LEA DX,S
    MOV AH,09H
    INT 21H

    ;输出区间下界
    XOR CX,CX
    MOV AL,BL
    CALL DCM;调用

    LEA DX,AD
    MOV AH,09H
    INT 21H

    ;输出区间上界
    XOR CX,CX
    MOV AL,BL
    ADD AL,9
    CMP AL,99
    JNZ OT;不是99直接输出
    ADD AL,1;如果是99那就再加一

OT: CALL DCM

    LEA DX,CO
    MOV AH,09H
    INT 21H

    XOR CX,CX
    MOV AL,BH
    CALL DCM

    LEA DX,CRLF
    MOV AH,09H
    INT 21H

    SUB BL,10;区间下界减10
    XOR BH,BH
    POP CX
    DEC CX
    JNZ JUD;返回继续判断之后的区间数据个数

    ;输出0~59区间
    LEA DX,S1
    MOV AH,09H
    INT 21H

    MOV BX,SI
    SUB BX,OFFSET SCORE;大于59的数的个数
    MOV AX,11
    SUB AX,BX;0-59区间的个数
    CALL DCM;以十进制输出
    
;输出最大、最小、中间值
    LEA DX,CRLF;换行
    MOV AH,09H
    INT 21H
    ;输出最小值
    LEA DX,M1
    MOV AH,09H
    INT 21H

    LEA SI,SCORE
    MOV AL,[SI+10]
    CALL DCM

    LEA DX,CRLF;换行
    MOV AH,09H
    INT 21H
    
    ;输出最大值
    LEA DX,M2
    MOV AH,09H
    INT 21H

    LEA SI,SCORE
    MOV AL,[SI]
    CALL DCM
    
    LEA DX,CRLF;换行
    MOV AH,09H
    INT 21H

    ;输出中间值
    LEA DX,M3
    MOV AH,09H
    INT 21H

    LEA SI,SCORE
    MOV AL,[SI+5]
    CALL DCM
    
    LEA DX,CRLF;换行
    MOV AH,09H
    INT 21H
    
    ;输出成绩排序结果
    LEA DX,RANK;提示语
    MOV AH,09H
    INT 21H

    LEA DI,SCORE;把成绩偏移地址给DI
    MOV SI,DI;DI把成绩偏移地址给SI
    MOV CX,11
LPP: 
    PUSH CX
    XOR CX,CX
    XOR DX,DX
    MOV AL,[SI]
    ;以十进制输出
    CALL DCM

    MOV DL,20H;空格
    MOV AH,2
    INT 21H

    INC SI
    POP CX
    LOOP LPP
    ;输出成绩排序结果结束

    MOV AH,4CH;程序结束
    INT 21H
MAIN ENDP
    
SORT PROC NEAR

    ;开始排序
    MOV BL,10;BL为外循环计数器
    LEA DI,SCORE;DI存放成绩初始地址

    ;外循环
NEXT1:
    MOV SI,DI;把成绩初始地址给SI
    MOV CL,BL;CL为内循环计数器

    ;内循环
NEXT2:
    MOV AL,[SI];把SI指向的成绩赋值给AL
    INC SI;指针右移
    CMP AL,[SI];后一个成绩和前一个成绩比较
    JNC NEXT3;如果前>后跳过交换
    ;交换成绩
    MOV AH,[SI]
    MOV [SI-1],AH
    MOV [SI],AL
    
NEXT3:
    DEC CL
    JNZ NEXT2
    ;内循环结束

    DEC BL
    JNZ NEXT1
    ;外循环结束
    RET

SORT ENDP


DCM PROC NEAR

    PUSH CX
T1: MOV AH,0
    MOV DL,0AH
    DIV DL
    PUSH AX
    INC CX
    CMP AL,0
    JNZ T1

T2: POP DX
    MOV DL,DH
    ADD DL,30H
    MOV AH,02H
    INT 21H
    LOOP T2

    POP CX
    RET
DCM ENDP

CODE ENDS
    END START