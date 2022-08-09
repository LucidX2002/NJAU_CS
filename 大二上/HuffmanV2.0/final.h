#ifndef HUFFMAN_H
#define HUFFMAN_H
/* ------------------------------ INCLUDE ----------------------------- */
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <io.h>
#include <stack>
#include <queue>
#include <string>
#include <bitset>
/* ------------------------------ CONST ------------------------------- */
const int MAXSIZE = 1000000; //文件读取最大容量
static int WPL = 0;
/* ---------------------------- NAMESPACE ----------------------------- */
using namespace std;
/* ----------------------------- STRUCTS ------------------------------ */
typedef struct HuffmanTreeNode
{
    int Ascii;//记录ASCII
    int Index;//记录位置，-1表示空
    int Weight;//记录权值
    HuffmanTreeNode* Parent;//记录父节点
    HuffmanTreeNode* Left;//记录左子节点
    HuffmanTreeNode* Right;//记录右子节点
} HuffmanTree;
//创建HuffmanTree,HuffmanTreeNode
typedef HuffmanTree* ElementType;
//变名为ElementType方便后期更改
typedef struct HeapStruct {
    ElementType* Elements;//堆存储元素的数组，而元素类型为哈夫曼树的结点指针 
    int Size;//堆的当前元素个数 
    int Capacity;//堆的最大容量 
}MinHeap;
//创建最小堆
typedef struct Code
{
    int Ascii;//记录ASCII
    int Weight;//记录权值
    char *hc;//用于存放Huffman编码
}*Codeset;
//创建编码集
/* ----------------------------- MINHEAP ------------------------------ */
MinHeap* Create(int MaxSize);
//创建并初始化堆
void Insert(MinHeap* H, ElementType item);
//插入操作
ElementType DeleteMin(MinHeap* H);
//删除最小节点，并返回
void Adjust(MinHeap* H, int p);
//调整堆，上滤操作
void BuilMinHeap(MinHeap* H);
//建立最小堆
/* ----------------------------- HUFFMANTREE -------------------------- */
HuffmanTree* CreateHuffman(MinHeap* H);
//将堆调整成Huffman树
void SetHuffmanTree();
//生成字频表的Huffman树
/* ---------------------------- COUNT_CHARACTER ----------------------- */
void Count_Character();
//进行字符频率统计
/* --------------------------------- CODE ----------------------------- */
void HuffmanCode(HuffmanTree* T, int depth,Codeset c);
//建立对应字符的Huffman编码
void Encode();
//对文本进行编码
void Decode();
//对文本进行编码
/* --------------------------------- EXTREA ----------------------------- */
void Analysis();
//对文本进行对比分析，输出正确率
void Compresibility();
//计算编码平均压缩率
void BitCompress(FILE*& fb,char* s);
#endif

