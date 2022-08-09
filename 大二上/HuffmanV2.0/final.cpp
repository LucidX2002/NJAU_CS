#include "final.h"
/* ----------------------------- MINHEAP ------------------------------ */
MinHeap* Create(int MaxSize) {
	MinHeap* H = new MinHeap;//申请空间
	H->Elements = new ElementType[MaxSize + 1];//申请空间，用于存放树，指针数组，每个元素的指针类型为HuffmanTree
	for (int i = 0; i < MaxSize + 1; i++) {
		H->Elements[i] = new HuffmanTree;//申请空间
		H->Elements[i]->Left = NULL;
		H->Elements[i]->Right = NULL;
		//左右子树初始化置空
	}
	H->Size = 0;//堆大小初始化为0
	H->Capacity = MaxSize;//堆容量初始化为最大容量
	return H;//返回初始化完成的堆
}
//创建并初始化堆
void Adjust(MinHeap* H, int p) {
	int Parent, Child;		//用于指示位置
	ElementType temp;		//用于暂存当前位置节点
	temp = H->Elements[p];	//取出当前位置节点
	for (Parent = p; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;	//完全二叉树性质，左子节点为2*Parent
		if (Child != H->Size && H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight)//判断权值大小
			Child++;		//Child指向左右子结点的权值较小者，指向右孩子
		if (temp->Weight <= H->Elements[Child]->Weight) 
			break;
		//当前节点权值小于孩子节点权值，满足最小堆
		else 
			H->Elements[Parent] = H->Elements[Child];
		//交换父子使满足堆排序
	}
	H->Elements[Parent] = temp;//将合法的树存入Parent位置
}
//调整堆，上滤操作
ElementType DeleteMin(MinHeap* H) {
	ElementType Min, temp;
	int Parent, Child;
	if (H->Size == 0) {
		cout << "IsEmpty" << endl;
		return NULL;
	}//当前堆大小为空返回
	Min = H->Elements[1];//从第一个元素找最小元素
	temp = H->Elements[H->Size--];//指向最后节点
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child) {
		Child = Parent * 2;//左孩子节点为Parent*2
		if (H->Size != Child && H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight)//判断权值大小
			Child++;//Child指向左右子结点的权值较小者，指向右孩子
		if (temp->Weight <= H->Elements[Child]->Weight) 
			break;//当前节点权值小于孩子节点权值，满足最小堆
		else 
			H->Elements[Parent] = H->Elements[Child];//交换父子使满足堆排序
	}
	H->Elements[Parent] = temp;//修正当前父节点
	return Min;//返回最小节点
}
//删除最小节点，并返回
void Insert(MinHeap* H, ElementType item) {
	int i;
	if (H->Size == H->Capacity) {
		cout << "IsFull" << endl;
		return;
	}//堆满输出错误信息
	for (i = ++H->Size; item->Weight < H->Elements[i / 2]->Weight; i = i / 2)//与父节点进行比较，判断是否需要调整
		H->Elements[i] = H->Elements[i / 2];//父节点大于子节点，不满足最小堆，调整堆
	H->Elements[i] = item;//找到合适位置，存放新树
}
//插入新节点
void BuilMinHeap(MinHeap* H) {
	int i;
	i = H->Size / 2;//找到父节点
	for (i; i >= 1; i--) {
		Adjust(H, i);//调整堆
	}
}
//建立最小堆
/* ----------------------------- HUFFMANTREE -------------------------- */
void SetHuffmanTree()
{
	fstream inFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Frequency of Characters.txt", ios::in);
	if (!inFile)
		cout << "Frequency of Characters.txt open failed" << endl;
	int n;
	inFile >> n;//用于读入不同的字符个数
	if (n <= 1)
	{
		return;
	}//不同字符数小于1，读取错误，返回
	MinHeap* H;//建立堆变量
	HuffmanTree* T;//建立HuffmanTree变量
	H = Create(2*n);//以最大容量初始化堆，注意0号单元不使用
	for (int i = 1; i <= n; i++) {
		H->Elements[i]->Index = i;//初始化Index
		inFile >> H->Elements[i]->Ascii >> H->Elements[i]->Weight;//从文件读入Ascii和Weight
		H->Size++;//堆容量+1
	}
	inFile.close();//读入文件关闭
	T = CreateHuffman(H);//将生成的树传入T
	fstream outFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Huffman_Tree.txt", ios::out);//打开输出文件
	if (!outFile)
		cout << "Huffman_Tree.txt open failed" << endl;//文件打开失败，输出失败信息
	outFile << n << endl;//输出不同字符的数目
	HuffmanTree* temp;//生成temp用于后续便利
	queue<HuffmanTree*> S;//创建队列S，其中存放HuffmanTree*，指针队列
	S.push(T);//将树入栈，此时T为根节点
	while (!S.empty()) {//当队列为空时，说明所有节点都已经处理完毕
		temp = S.front();//取出指针结点，做输出处理 
		S.pop();//首节点弹出队列
		outFile << temp->Ascii << ' ' <<temp->Weight;//输出对应位置的Ascii和Weight
		if (temp->Left)
		{
			S.push(temp->Left);//左子树入栈
			outFile << ' ' << temp->Left->Index;//输出左子树的Index
		}
		else
			outFile << ' ' << -1;//左子树为空，输出Index=-1，表示空节点
		if (temp->Right)//判断右子树是否为空
		{
			S.push(temp->Right);//右子树入栈
			outFile << ' ' << temp->Right->Index;//输出右子树的Index
		}
		else
			outFile << ' ' << -1;//右子树为空，输出Index=-1，表示空节点
		outFile << endl;//节点信息输出完毕
	}
	outFile.close();//输出文件关闭
	Codeset c=new Code[256];//创建编码集
	for (int i = 0; i < 256; i++)
	{
		c[i].Ascii = 0;
		c[i].Weight = 0;
	}
	//初始化编码集合
	HuffmanCode(T, 0, c);
	cout << "WPL Calculation Accomplished." << WPL << endl;
	outFile.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Huffman_Code.txt", ios::out);//读入输出文件
	if (!outFile)
		cout << "C:\\Users\\Lucid-X\\Desktop\\DS Design\\Huffman_Code.txt open failed." << endl;//读入失败，输出失败信息
	for (int i = 1; i < 255; i++)
	{
		if (c[i].Ascii == 0)//如果Ascii为0，说明只进行了初始化，为后续的生成节点，无需输出
			break;
		outFile << " " << c[i].Ascii << " " << c[i].Weight <<" ";//输出对应字符的Ascii和Weight
		outFile << c[i].hc << endl;//输出对应字符的HuffmanCode
	}
	outFile.close();//关闭输出文件
}
//生成字频表的Huffman树
HuffmanTree* CreateHuffman(MinHeap* H) {
	int i;
	HuffmanTree* T;
	BuilMinHeap(H);//建立最小堆
	for (i = 1; i < H->Size; i) {
		T = new HuffmanTree;//生成树节点
		T->Index = 0;//初始化Index
		T->Ascii = 0;//初始化Ascii
		T->Left = T->Right = NULL;//左右子树初始化为空指针
		T->Left = DeleteMin(H);//取出当前权值最小的节点给左子树
		T->Right = DeleteMin(H);//取出当前权值次小的节点给右子树
		T->Weight = T->Left->Weight + T->Right->Weight;//计算当前节点的权值 
		Insert(H, T);//插回最小堆 
	}
	T = DeleteMin(H);
	return T;//返回树
}
//将堆调整成Huffman树
/* ---------------------------- COUNT_CHARACTER ----------------------- */
void Count_Character()
{
	int count[256];//根据ASCII码进行存放
	memset(count, 0, sizeof(count));//把count中所有所有单元全部置为0
	clock_t start_time = clock();//记录程序开始时间
	fstream inFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\source.txt", ios::in);//读入文件打开
	if (!inFile)
		cout << "source.txt open failed." << endl;//打开失败，输出失败信息
	clock_t end_time = clock();//记录程序结束时间
	double time = (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000;
	cout << "Read accomplished." << time << "ms" << endl;//读取完毕，输出时间
	int sum = 0;//用于记录换行符数目
	string s;//用于进行行读取
	while (true)
	{
		getline(inFile, s);//按行读取到到字符串s中进行处理
		if (!inFile)//文件读取结束，退出循环
			break;
		sum++;//读取结束，换行符增加
		for (int i = 0; i < s.size(); i++)
		{
			int a = s[i];//读取字符的ASCII编码
			count[a]++;//对应字符计数+1
		}
	}
	inFile.close();//读取文件关闭
	int a = '\n';//统计换行符，读取换行符的ASCII
	count[a] = sum;//存入计数
	int n = 0;//用于统计字符个数
	for (int i = 0; i < 256; i++)
	{
		if (count[i] != 0)//存在计数，说明该字符出现
			n++;//字符个数+1
	}
	fstream outFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Frequency of Characters.txt", ios::out);//打开输出文件
	if (!outFile)
		cout << "Frequency of Characters.txt open failed!" << endl;//打开失败，输出错误信息
	outFile << n << endl;//输出不同的字符个数
	for (int i = 0; i < 256; i++)
	{
		if (count[i] != 0)
			outFile << i << " " << count[i] << endl;//输出ASCII和相应字符数目
	}
	outFile.close();//输出文件关闭
}
//建立对应字符的Huffman编码
/* --------------------------------- CODE ----------------------------- */
void HuffmanCode(HuffmanTree* T, int depth, Codeset c)//depth为目前编码到哈夫曼树的深度 
{
	static char cd[20];  //静态变量作为编码空间
	static int i = 1;	//静态变量
	if (T)
	{
		if ((T->Left == NULL) && (T->Right == NULL)) {  //找到了叶结点
			c[i].Ascii = T->Ascii;	//将对应Ascii存入编码集合
			c[i].Weight = T->Weight;//将对应Weight存入编码集合
			c[i].hc = new char[depth];//初始化hc用于存放HuffmanCode
			for (int j = 0; j < depth; j++) {
				c[i].hc[j] = cd[j];//将对应0/1存入
			}
			c[i].hc[depth] = '\0';//串尾存入结束符
			WPL += c[i].Weight * depth;
			i++;//对下一个字符进行编码
		}
		else //非叶子节点继续进行遍历
		{
			cd[depth] = '0';  //往左子树方向编码为0
			HuffmanCode(T->Left, depth + 1, c);//此时深度+1
			cd[depth] = '1';  //往右子树方向编码为1 
			HuffmanCode(T->Right, depth + 1, c);//此时深度+1
		}
	}
}
//建立对应字符的Huffman编码
void Encode()
{
	char code[24]{};//用于存储编码
	fstream inFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Huffman_Code.txt", ios::in);//读取文件
	if (!inFile)
		cout << "Huffman_Code.txt open failed" << endl;//读取失败，输出失败信息
	string s, codeList[256];//s用于读入编码，codeList用于存放对应字符编码
	int ch, w;//用于读入字符和权值
	while (true)
	{
		inFile >> ch >> w >> s;//按序读入
		if (!inFile)//读取结束出循环
			break;
		codeList[ch] = s;//将对应字符编码存入数组
	}
	inFile.close();//读取文件关闭
	FILE* fout;
	fout = fopen("C:\\Users\\Lucid-X\\Desktop\\DS Design\\code.dat","wb");//以二进制形式输出
	inFile.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\source.txt", ios::in);//打开源文件
	if (!inFile)
		cout << "source.txt open failed" << endl;//打开失败，输出错误信息
	while (true)
	{
		getline(inFile, s);//读取一行数据

		if (!inFile)//读取完毕，出循环
			break;
		int a;//用于读取ASCII
		for (int i = 0; i < s.size(); i++)
		{
			a = s[i];//读取字符的ASCII
			int j;//
			for (j = 0; j < codeList[a].size(); j++)
				code[j] = (codeList[a])[j];//按序读入，存进code中
			code[j] = '\0'; //最后一位存入换行符
			BitCompress(fout, code);
		}
		a='\n';//读取换行符ASCII
		int j;
		for (j = 0; j < codeList[a].size(); j++)
			code[j] = (codeList[a])[j];//按序读入，存入code
		code[j] = '\0'; //最后一位存入换行符
		BitCompress(fout, code);
	}
	inFile.close();//输入文件关闭
}
//对文本进行编码
void Decode()
{
	fstream inFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Frequency of Characters.txt", ios::in);
	if (!inFile)
		cout << "Frequency of Characters.txt open failed" << endl;
	int n;
	inFile >> n;//用于读入不同的字符个数
	if (n <= 1)
	{
		return;
	}//不同字符数小于1，读取错误，返回
	MinHeap* H;//建立堆变量
	HuffmanTree* T;//建立HuffmanTree变量
	H = Create(2 * n);//以最大容量初始化堆，注意0号单元不使用
	for (int i = 1; i <= n; i++) {
		H->Elements[i]->Index = i;//初始化Index
		inFile >> H->Elements[i]->Ascii >> H->Elements[i]->Weight;//从文件读入Ascii和Weight
		H->Size++;//堆容量+1
	}
	inFile.close();//读入文件关闭
	T = CreateHuffman(H);//将生成的树传入T
	char code[24]{};//用于进行解码操作
	HuffmanTree* temp;//用作位移指针
	temp = T;//temp指向根节点
	int depth;//用于记录解码进度
	inFile.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\code.dat", ios::in | ios::binary);//打开编码文件
	if (!inFile)
		cout << "code.dat open failed." << endl;//打开失败，输出错误信息
	unsigned char b = 0;
	unsigned int cod;
	fstream outFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\recode.txt", ios::out);//打开输出文件
	if (!outFile)
		cout << "recode.txt open failed." << endl;//打开失败，输出错误信息
	while (T)
	{
		inFile.read((char*)b,sizeof(unsigned char));
		if (!inFile)
			break;//读取完毕退出解码
		if (T) 
		{
			for (int i = 0; i < 8; i++) {
				cod = b & 128;//取第一位数
				b = b << 1;//左移一位
				if (cod == 0)
					temp = temp->Left;//为0则向左遍历;//从根开始一一对应查找
				else
					temp = temp->Right;
				if ((temp->Left == NULL) && (temp->Right == NULL))
				{
					char cht = temp->Ascii;//输出解码后对应结点的字符 
						outFile << cht;//输出对应字符
						temp = T;
						break;//此字节内编码读取完毕，继续获取下一个字节
				}
				outFile.close();//输出文件关闭
			}
		}
	}
}
//对文本进行编码
/* --------------------------------- EXTREA ----------------------------- */
void Analysis()
{
char Tmp1, Tmp2;//用于遍历字符
	ifstream inFile1, inFile2;//用于遍历源文件
	int n = 0;//用于统计错误字符数目
	int inLength = 0;//用于统计文件总长
	inFile1.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\source.txt", ios::in);//读取源文件
	if (!inFile1)
		cout << "C:\\Users\\Lucid-X\\Desktop\\DS Design\\source.txt open failed." << endl;//读取失败，输出错误信息
	inFile2.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\recode.txt", ios::in);//读取译码文件
	if(!inFile2)
		cout << "C:\\Users\\Lucid-X\\Desktop\\DS Design\\recode.txt open failed." << endl;//读取失败，输出错误信息
	while (inFile1.get(Tmp1) && inFile2.get(Tmp2))//按字符读取文件
	{
		if (inFile1)
			inLength++;//统计源文件长度
		if (Tmp1 != Tmp2)
		{
			cout <<"Unmatched Character." << endl;//找到不匹配字符
			n++;//错误字符增加
		}
	}
	inFile1.close();//文件关闭
	inFile2.close();//文件关闭
	if (inFile1.get(Tmp1))
		cout << "source.txt unfinished." << endl;//源文件未读取完，输出错误信息
	else if (inFile2.get(Tmp2))
		cout << "recode.txt unfinished." << endl;//解码文件未读取完，输出错误信息
	else
		cout << "No Character Unmatched." << endl;//完全正确，输出正确信息
	cout << "Correct Rate:" << (inLength - n) / inLength / 0.01 << "%" << endl;//输出正确率
}
//对文本进行对比分析，输出正确率
void Compresibility()
{
	fstream inFile("C:\\Users\\Lucid-X\\Desktop\\DS Design\\Huffman_Code.txt", ios::in);//读取文件
	if (!inFile)
		cout << "Huffman_Code.txt open failed" << endl;//读取失败，输出失败信息
	string s;//s用于读入编码
	int ch, w;//用于读入字符和权值
	double CodeLength = 0;//用于计算平均字符长
	char temp;
	ifstream inFile2;
	int inLength = 0;
	inFile2.open("C:\\Users\\Lucid-X\\Desktop\\DS Design\\source.txt", ios::in);
	while (inFile2.get(temp))
	{
		if (inFile2)
			inLength++;
	}
	while (true)
	{
		inFile >> ch >> w >> s;//按序读入
		if (!inFile)//读取结束出循环
			break;
		CodeLength += (w / (double)inLength) * s.length();//计算平均编码字符长
	}
	cout << "Compresibility:"<< CodeLength / 8.00 << endl;//计算根据等长编码计算压缩率
}
//计算编码压缩率
void BitCompress(FILE*& fb, char* s)
{
	int len = strlen(s);//用于统计01串长
	int i;
	unsigned char c = 0;//用作位操作单元
	while (len >= 8)//判断01串长是否超过最大限度，如果超过进行分割处理
	{
		for (i = 0; i < 8; i++)
		{
			if (s[i] == '1')
				c = (c << 1) | 1;//左移一位补零，与1取或添1
			else
				c = c << 1;//左移一位补零
		}
		fwrite(&c, sizeof(unsigned char), 1, fb);//以一个字节的形式写入文件
		s = s + 8;//01串向后位移8位
		len = strlen(s);//重新调整长度
	}
	// 当 k < 8 时，表示剩下的编码不足 8 个字符，需要补零
	if (len > 0)
	{
		memset(s,'0',8);//将s串全部置零保证填满八位
		for (i = 0; i < 8; i++) {
			if (s[i] == '1')
				c = (c << 1) | 1;
			else
				c = c << 1;//同上述操作不做赘述
		}
		fwrite(&c, sizeof(unsigned char), 1, fb);//以一个字节的形式写入文件
	}
}









