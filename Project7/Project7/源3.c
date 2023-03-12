#include<stdio.h>

int add(int a, int b)
{
	//位运算实现相加的本质就是将进位逐渐加到不考虑进位的相加数上
	//不考虑进位相加
	int pureadd = a ^ b;
	//进位标志
	int carry = a & b;
	//进位标志不为0，继续运算
	while (carry != 0)
	{
		//有进位，需要重新计算pureadd和carry<<1的和
		int p = pureadd;
		int c = carry << 1;
		//重复加法运算
		pureadd = p ^ c;
		carry = p & c;
	}
	return pureadd;
}


int main4()
{
	//
	int ans=add(15, 5);
	return 0;
}