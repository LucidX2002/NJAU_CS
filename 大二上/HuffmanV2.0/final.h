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
const int MAXSIZE = 1000000; //�ļ���ȡ�������
static int WPL = 0;
/* ---------------------------- NAMESPACE ----------------------------- */
using namespace std;
/* ----------------------------- STRUCTS ------------------------------ */
typedef struct HuffmanTreeNode
{
    int Ascii;//��¼ASCII
    int Index;//��¼λ�ã�-1��ʾ��
    int Weight;//��¼Ȩֵ
    HuffmanTreeNode* Parent;//��¼���ڵ�
    HuffmanTreeNode* Left;//��¼���ӽڵ�
    HuffmanTreeNode* Right;//��¼���ӽڵ�
} HuffmanTree;
//����HuffmanTree,HuffmanTreeNode
typedef HuffmanTree* ElementType;
//����ΪElementType������ڸ���
typedef struct HeapStruct {
    ElementType* Elements;//�Ѵ洢Ԫ�ص����飬��Ԫ������Ϊ���������Ľ��ָ�� 
    int Size;//�ѵĵ�ǰԪ�ظ��� 
    int Capacity;//�ѵ�������� 
}MinHeap;
//������С��
typedef struct Code
{
    int Ascii;//��¼ASCII
    int Weight;//��¼Ȩֵ
    char *hc;//���ڴ��Huffman����
}*Codeset;
//�������뼯
/* ----------------------------- MINHEAP ------------------------------ */
MinHeap* Create(int MaxSize);
//��������ʼ����
void Insert(MinHeap* H, ElementType item);
//�������
ElementType DeleteMin(MinHeap* H);
//ɾ����С�ڵ㣬������
void Adjust(MinHeap* H, int p);
//�����ѣ����˲���
void BuilMinHeap(MinHeap* H);
//������С��
/* ----------------------------- HUFFMANTREE -------------------------- */
HuffmanTree* CreateHuffman(MinHeap* H);
//���ѵ�����Huffman��
void SetHuffmanTree();
//������Ƶ���Huffman��
/* ---------------------------- COUNT_CHARACTER ----------------------- */
void Count_Character();
//�����ַ�Ƶ��ͳ��
/* --------------------------------- CODE ----------------------------- */
void HuffmanCode(HuffmanTree* T, int depth,Codeset c);
//������Ӧ�ַ���Huffman����
void Encode();
//���ı����б���
void Decode();
//���ı����б���
/* --------------------------------- EXTREA ----------------------------- */
void Analysis();
//���ı����жԱȷ����������ȷ��
void Compresibility();
//�������ƽ��ѹ����
void BitCompress(FILE*& fb,char* s);
#endif

