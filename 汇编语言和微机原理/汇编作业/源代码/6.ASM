DATA SEGMENT 
    STRING1 DB 'Input your string:$';指示说明
    STRING2 DB 'Digit:$';指示说明
    STRING3 DB 'Letter:$';指示说明
    STRING4 DB 'Other:$';指示说明
    DIGIT DB 0;用于存放数字数量
    LETTER DB 0;用于存放字母数量
    OTHER DB 0;用于存放其他字符数量
DATA ENDS

STA SEGMENT;堆栈段
    DB 20 DUP(?)
STA ENDS

CODE SEGMENT 
    ASSUME DS:DATA,CS:CODE,SS:STA;段地址分配伪指令
MAIN PROC FAR;定义主函数
START:    
    MOV AX,DATA
    MOV DS,AX;数据段赋值
    LEA DX,STRING1
    MOV AH,9
    INT 21H;输出指示说明STRING1
    MOV CX,80;最大输入长度80
P1:
    MOV AH,1
    INT 21H;读取一个字符
    CMP AL,0DH;与回车(0DH)比较，结束输入
    JZ OVER;跳转至结束程序
    CMP AL,30H;与0(30H)比较
    JB OTHERS;比0(30H)小，OTHER+1
    CMP AL,39H;与9(39H)比较
    JA P2;进入P2，准备进行字母判断
    JMP DIGITS;若未跳转，说明字符在0-9，DIGIT+1

P2:
    CMP AL,41H;与A(41H)比较
    JB OTHERS;小于A(41H)，OTHER+1
    CMP AL,5AH;与Z(5AH)比较
    JA  P3;比Z(5AH)大，跳转至P3，进行小写字母判断
    JMP LETTERS;若未跳转，说明字符在A-Z,LETTER+1;

P3:
    CMP AL,61H;与a(61H)比较
    JB OTHERS;小于a(61H)，OTHER+1
    CMP AL,7AH;与z(7AH)比较
    JA OTHERS;比z(7AH)大，OTHER+1
    JMP LETTERS;若未跳转，说明字符在a-z，LETTER+1

DIGITS:
    INC DIGIT
    JMP L

OTHERS:
    INC OTHER
    JMP L

LETTERS:
    INC LETTER
    JMP L

L:
    LOOP P1;循环进行判断

OVER: 
    LEA DX,STRING2
    MOV AH,9
    INT 21H;输出指示信息
    XOR AX,AX;清空AX
    MOV AL,DIGIT
    CALL PRINT;打印DIGIT

    CALL RE;输出回车
    LEA DX,STRING3
    MOV AH,9
    INT 21H;输出指示信息
    XOR AX,AX
    MOV AL,LETTER
    CALL PRINT;打印LETTER
    
    CALL RE;输出回车
    LEA DX,STRING4
    MOV AH,9
    INT 21H;输出指示信息
    XOR AX,AX
    MOV AL,OTHER
    CALL PRINT;打印OTHER
    MOV AX,4C00H
    INT 21H
MAIN ENDP;主函数结束

RE PROC NEAR

    MOV AH,2
    MOV DL,0AH
    INT 21H;回车
    MOV AH,2
    MOV AL,0DH
    INT 21H;换行
    RET

RE ENDP

PRINT PROC NEAR;输出一个二位十进制数

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


