#include<iostream>
#include"huffman_code.h"
#include"read.h"


using namespace std;
int main(void)
{
	int weights[] = { 10,8,3,4,5 };
	const int LENGTH = 5;
	HuffmanTree HT;
	CreateHuffmanTree(HT, weights, LENGTH);
	HuffmanCodeTable HCT;
	CreateHuffmanCode(HT, HCT, LENGTH);
	cout << "Huffman_Tree" << endl;
	for (int i = 1; i <= LENGTH * 2 - 1; i++)
	{
		HTNode node = HT[i];
		cout << "\t|"
			<<i << "\t|"
			<< node.weight << "\t|"
			<< node.parent << "\t|"
			<< node.lchild << "\t|"
			<< node.rchild << "\t|" << endl;
	}
	cout << "Huffman_Code:" << endl;
	for (int i = 1; i <= LENGTH; i++)
	{
		cout << "\t|"<< i << "\t|" << weights[i - 1] << "\t|" << HCT[i] << "\t|" << endl;
	}
	return 0;
}