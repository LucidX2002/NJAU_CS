#include"final.h"
using namespace std;
int main(void)
{

	/* ---------------------------- COUNT_CHARACTER ----------------------- */
	clock_t start_time = clock();
	Count_Character();
	clock_t end_time = clock();
	double time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	cout << "Count_Character Accomplished." << time << "ms" << endl;
	/* ----------------------------- HUFFMANTREE -------------------------- */
	start_time = clock();
	SetHuffmanTree();
	end_time = clock();
	time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	cout << "SetHuffmanTree Accomplished." << time << "ms" << endl;
	/* --------------------------------- ENCODE ---------------------------- */
	start_time = clock();
	Encode();
	end_time = clock();
	time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	cout << "Encode Accomplished." << time << "ms" << endl;

	return 0;
}