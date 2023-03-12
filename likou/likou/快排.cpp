#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

void quicksort(int left, int right, vector<int> &v)
{
	//递归结束条件
	if (left > right)
	{
		return;
	}

	//先选中基准
	int base = v[left];
	//开始交换数据已保证左边小于基准，右边大于基准
	int l = left;
	int r = right;
	while (l < r)
	{
		//先找右边小于基准的数
		while (v[r] >= base && l!=r)
		{
			r--;
		}
		//再找左边大于基准的数
		while (v[l] <= base && l != r)
		{
			l++;
		}
		//两个数都找到后，交换
		if (l < r)
		{
			swap(v[l], v[r]);
		}
	}
	//左右迟早会相遇，遇到后就说明交换结束，此时基准归位,将此时相遇的位置值与基准值交换
	v[left] = v[l];
	v[l] = base;
	quicksort(left, l - 1, v);
	quicksort(l + 1, right, v);
}


