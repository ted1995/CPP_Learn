#include<iostream>
using namespace std;
#include <iomanip>

int main1()
{
	//float占4个字节
	float a = 1.0;
	//取浮点数a的地址，char占一个字节，所以可以一个字节一个字节的取出float的值
	char *p = (char*)&a;
	for (int i = 0; i < 4; i++)
	{
		//打印当前字节
		printf("% ", *p);
		//指向下一个字节
		p++;
	}
	return 0;
}