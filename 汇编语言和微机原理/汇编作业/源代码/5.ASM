DATA SEGMENT
	STRING1 DB "Enter 3 numbers",0AH,'$'
	STRING2 DB "Please input X:",'$'
	STRING3 DB "Please input Y:",'$'
	STRING4 DB "Please input Z:",'$'
	STRING5 DB "3X-2|Y|+|Z|= ",'$'
	X   	DB 8 DUP(0)
	Y   	DB 8 DUP(0)
	Z   	DB 8 DUP(0)
	RESULT  DB 3 DUP(0)
	FLAG  	DB 0
DATA ENDS

STK SEGMENT
   	DB 16 DUP(0)
STK ENDS

CODE SEGMENT
	ASSUME CS:CODE,DS:DATA,SS:STK
MAIN PROC FAR
START: 
   	MOV AX,DATA
   	MOV DS,AX 
   	MOV AX,STK
   	MOV SS,AX
   	MOV SP,16
   
   	LEA BX,STRING5
   	PUSH BX 
   	LEA BX,STRING4
   	PUSH BX 
   	LEA BX,STRING3
   	PUSH BX
   	LEA BX,STRING2
   	PUSH BX
   	LEA BX,STRING1
   	PUSH BX     
   
   	MOV SI,0
   	MOV BP,10    
   
   	LEA BX,X
   	POP DX     ;获取STRING1偏移地址
   	MOV AH,09H
   	INT 21H    ;显示提示语
   	MOV CX,3

INPUT: 

	POP DX
   	MOV AH,09H
   	INT 21H    ;每次显示一个输入提示，循环3次
   	CALL INCHAR    ;读取字符
   	MOV AL,[BX]
   	MOV AH,0    ;AL存放首位字符，开始准备计算数值
   	PUSH BX
   	PUSH CX 
   	SUB SI,2
   	JZ SOLO    ;个位数直接算
   	MOV CX,SI
   	MOV SI,1  
   	CALL EXC   ;字符转化为数AL

S:   

	POP CX
   	POP BX
   	MOV BYTE PTR[BX],AL
   	ADD BX,8
   	MOV SI,0
   	LOOP INPUT    ;三个数据输入完毕,存储真正的值放在第一位 
   	POP DX     
   	MOV AH,09H
   	INT 21H  
   	MOV CX,0
   	SUB BX,24    
   	MOV AL,BYTE PTR[BX]
   	
	PUSH BX
   	MOV BL,3
   	XOR AH,AH
   	IMUL BL
   	POP BX
   	MOV BYTE PTR[BX+24],AL  ;将X的值存放于RESULT的第0位
   	MOV AL,[BX+8]
   	ADD AL,0
   	JS ABSY
 
INY: 

   	PUSH BX
   	MOV BL,02H
   	XOR AH,AH
   	MUL BL
   	POP BX
   	MOV [BX+25],AL      ;将|Y|的值存放于RESULT的第1位
   	MOV AL,BYTE PTR[BX+16]  
   	ADD AL,0         
   	JS ABSZ
	   
INZ:
 
	MOV [BX+26],AL      ;将|Z|的值存放于RESULT的第2位
   	ADD BX,24
   	MOV AH,0
   	MOV AL,[BX]
   	SUB AL,[BX+1]
   	ADD AL,[BX+2]      ;公式运算 
   	JS DISPLAYNEG;判断结果是否为负数

STO: 

	MOV DX,0
   	MOV AH,0
   	INC CX 
  	IDIV BP
   	PUSH DX         ;十进制数的每一位入栈
   	CMP AX,0   
   	JNZ STO         
   	MOV AH,2

DIS:

	POP DX
   	ADD DL,30H
   	INT 21H         ;十进制数的每一位出栈并输出
   	LOOP DIS
     
   	MOV AX,4C00H
	INT 21H
MAIN ENDP

SOLO: 
	SUB AL,30H        ;直接处理
   	JMP S
	   
INCHAR: 
	MOV AH,01H
   	INT 21H
   	MOV [BX+SI],AL      ;获取单个字符
   	INC SI 
   	CMP AL,2DH 
   	JZ GETF      ;若是负号则跳转

JUG:  
	CMP AL,0DH
   	JNZ INCHAR
   	RET       ;判断结束
     
EXC PROC NEAR

	SUB AL,30H
   	MUL BP
   	ADD AL,[BX+SI]
   	ADD SI,1       ;字符串每一位累加计算数值
   	LOOP EXC
   	SUB AL,30H 
   	MOV BX,109
   	CMP BYTE PTR[BX],1   
   	JZ NEGA        ;若符号位为1，则表明是负数，取补码
   	RET

EXC ENDP

GETF: 
	MOV BYTE PTR[BX],30H
   	PUSH BX
   	MOV BX,109   
   	MOV BYTE PTR[BX],1       
   	POP BX
   	JMP JUG

NEGA:  
	NEG AL
   	MOV BYTE PTR[BX],0   ;取补码，符号位置0
   	RET

ABSY: 
	NEG AL         ;取绝对值
   	JMP INY

ABSZ: 
	NEG AL         ;取绝对值
   	JMP INZ

DISPLAYNEG: 
	NEG AL
    PUSH AX
    MOV DL,'-'
    MOV AH,02H
    INT 21H        ;显示负数
    POP AX        
    JMP STO

CODE ENDS
	END START 
