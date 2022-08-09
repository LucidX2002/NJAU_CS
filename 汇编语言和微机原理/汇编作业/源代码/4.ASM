DATA SEGMENT;定义数据段
      MKEY DB 0DH,0AH,'MATCH',0DH,0AH,'$';定义匹配时的输出字符
      NMKEY DB 0DH,0AH,'NOMATCH',0DH,0AH,'$';定义不匹配时的输出字符
      SUM DW ?
DATA  ENDS;数据段结束
CODE SEGMENT;定义代码段
      ASSUME CS:CODE;说明代码段和数据段的位置
START:
;初始化
      MOV AX,1000H
      MOV DS,AX;定义数据段地址
      MOV AX,1
      MOV CX,100;初始化AX和CX
      S:
      MOV [DI],AX
      INC AX
      INC DI
      LOOP S;将1~100循环存入DS
;转存部分
      MOV DI,0;清空目的指针
      MOV AX,2000H
      MOV ES,AX;定义附加段地址
      MOV CX,100;设置循环次数
      CLD;清空方向标志，从低地址向高地址移动
      REP MOVSB;当CX不为0时继续配对
;比较部分
      MOV CX,100;设置循环次数
      REPZ CMPSB;当CX不为0且字符串匹配时继续配对
      JNZ MATCH;ZF=1说明匹配成功
      JZ NOMATCH;ZF=0说明匹配失败
;输出标志信息部分
MATCH:
      MOV AX,DATA
      MOV DS,AX;重新定义数据段
      LEA DX,MKEY;取出MATCH的偏移地址
      MOV AH,09H;调用09H指令输出MATCH
      INT 21H
      JMP A;跳转到累加部分

NOMATCH:
      MOV AX,DATA
      MOV DS,AX;重新定义数据段
      LEA DX,NMKEY;取出NOMATCH的偏移地址
      MOV AH,09H;调用09H指令输出NOMATCH
      INT 21H
      JMP A;跳转到累加部分
;累加部分
A:    MOV AX,1000H
      MOV DS,AX;重新定义数据段
      MOV CX,100
      XOR AX,AX;清空AX
      XOR SI,SI;清空SI
      XOR DI,DI;清空DI

NEXT:
      XOR AX,AX;清空AX
      ADD AL,[SI];利用AL存放一个字节中的数据
      MOV AH,0;修正高地址
      INC SI;指针位移
      ADD DX,AX;保证字长匹配,相加
      LOOP NEXT;循环相加    
;输出部分
      MOV BX,DX;将结果转存入BX
      MOV SI,0AH
      XOR CX,CX;清空计数器
      MOV AX,BX;将结果转存入AX,准备除法

L:    XOR DX,DX
      DIV SI;取出AX的末位数      
      PUSH DX;余数入栈保护数据
      INC CX;计数加一,为输出做准备
      CMP AX,0
      JNZ L;直到商为0时停止循环

PRINT:POP DX;数据出栈，FILO顺序正确
      ADD DL,30h;转化成可以输出的ASCII
      MOV AH,2
      INT 21h;调用输出字符的02H指令
      LOOP PRINT

      MOV AX,4C00H
      INT 21H;返回程序

CODE ENDS;代码段结束

END START;结束程序