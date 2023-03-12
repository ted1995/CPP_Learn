#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


//选择排序
void sel_sort(vector<int> &v)
{
	int size = v.size();
	for (int i = 0; i < size; i++)
	{
		//找到所有元素中最小的，交换到最前面
		//比较的起始位置就是要交换的位置
		//逐步缩小范围
		int min = i;
		for (int j = i + 1; j < size; j++)
		{
			if (v[j] < v[min])
			{
				min = j;
			}
		}
		int temp = v[min];
		v[min] = v[i];
		v[i] = temp;
	}
}

//合并两个有序的数组
void myunion(vector<int> &v1,vector<int> &v2,vector<int> &v)
{
	typedef vector<int>::iterator it;
	it first1 = v1.begin();
	it last1 = v1.end();
	it first2 = v2.begin();
	it last2 = v2.end();
	while (first1 != last1 && first2 != last2)
	{
		if (*first1 < *first2)
		{
			v.push_back(*first1);
			++first1;
		}
		else if (*first1 > *first2)
		{
			v.push_back(*first2);
			first2++;
		}
		else
		{
			v.push_back(*first1);
			v.push_back(*first2);
			first1++;
			first2++;
		}
	}
	if (first1 == last1)
	{
		v.insert(v.end(),first2, last2 );
	}
	else if(first2 == last2)
	{
		v.insert(v.end(),first1, last1 );
	}
}


//仿函数
class gen
{
public:
	int operator()()
	{
		return x += 1;
	}
private:
	static int x;
};
//静态变量类外初始化
int gen::x = 0;

//生成算法
void mygenerate(vector<int> &v, gen g)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		*it = g();
	}
}

//打印
void myprint(vector<int> &v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

//是否是子序列
int mysearch(vector<int> &v1, vector<int> &v2)
{
	typedef vector<int>::iterator it;
	it first1 = v1.begin();
	it last1 = v1.end();
	it first2 = v2.begin();
	it last2 = v2.end();
	it current1 = first1;
	it current2 = first2;
	if (v1.size() < v2.size())
	{
		return -1;
	}
	int d1 = v1.size();
	int d2 = v2.size();
	while (current2 != last2)
	{
		if (*current1 == *current2)
		{
			//找到相同的，找下一个
			++current1;
			++current2;
		}
		else
		{
			if (d1 == d2)
			{
				return -1;
			}
			else
			{
				current1=++first1;
				current2 = first2;
				d1--;
			}
		}
	}
	return 1;
}

//插入排序
void myinsertsort(vector<int> &v)
{
	if (v.size() == 1)
	{
		return;
	}
	//外循环扩大
	for (int i = 1; i < v.size(); i++)
	{
		//内循环缩小
		for (int j = i; j > 0; j--)
		{
			//相邻元素比较
			if (v[j] < v[j - 1])
			{
				int temp = v[j];
				v[j] = v[j - 1];
				v[j - 1] = temp;
			}
		}
	}
}


int main()
{
	/*int a[] = { 1,4,5,3,8 };
	vector<int> v(a, a + 5);
	sel_sort(v);
	myprint(v);*/

	/*
	int a1[] = { 1,3,5,7 };
	int a2[] = { 2,4,6,8 };
	vector<int> v1(a1, a1 + 4);
	vector<int> v2(a2, a2 + 4);
	vector<int> v;
	myunion(v1, v2, v);
	myprint(v);
	*/

	/*int a[] = { 2,4,6,8 };
	vector<int> v1(a, a + 4);
	gen g;
	mygenerate(v1,g);
	myprint(v1);*/

	/*int a1[] = { 1,3,5,7,3};
	int a2[] = { 5,7 };
	vector<int> v1(a1, a1 + 5);
	vector<int> v2(a2, a2 + 2);
	cout << mysearch(v1, v2) << endl;*/

	/*int a1[] = { 1,3,5,7,3 };
	vector<int> v1(a1, a1 + 5);
	sort(v1.begin(), v1.end());
	myprint(v1);
	vector<int>::iterator  new_end=unique(v1.begin(), v1.end());*/


	int a1[] = { 8,3,5,7,10 };
	vector<int> v1(a1, a1 + 5);
	myinsertsort(v1);
	myprint(v1);

	return 0;

}