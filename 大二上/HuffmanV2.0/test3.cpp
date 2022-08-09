#include<iostream>
#include"read.h"
#include"huffman_code.h"
#include<fstream>

using namespace std;
int main(void)
{
	fstream inFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Huffman Code.txt", ios::in);//
	if (!inFile)
		cout << "Huffman Code.txt" << endl;
	string s, codeList[256];
	int ch, w;
	while (true)
	{
		inFile >> ch >> w >> s;
		if (!inFile)
			break;
		codeList[ch] = s;
	}
	inFile.close();
	inFile.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\source.txt", ios::in);
	if (!inFile)
		cout << "source.txt open failed" << endl;
	fstream outFile("code.dat", ios::out | ios::binary);
	if (!outFile)
		cout << "code.dat open failed" << endl;
	string s2;
	while(true)
}