#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

void quicksort(int left, int right, vector<int> &v)
{
	//�ݹ��������
	if (left > right)
	{
		return;
	}

	//��ѡ�л�׼
	int base = v[left];
	//��ʼ���������ѱ�֤���С�ڻ�׼���ұߴ��ڻ�׼
	int l = left;
	int r = right;
	while (l < r)
	{
		//�����ұ�С�ڻ�׼����
		while (v[r] >= base && l!=r)
		{
			r--;
		}
		//������ߴ��ڻ�׼����
		while (v[l] <= base && l != r)
		{
			l++;
		}
		//���������ҵ��󣬽���
		if (l < r)
		{
			swap(v[l], v[r]);
		}
	}
	//���ҳ�����������������˵��������������ʱ��׼��λ,����ʱ������λ��ֵ���׼ֵ����
	v[left] = v[l];
	v[l] = base;
	quicksort(left, l - 1, v);
	quicksort(l + 1, right, v);
}


