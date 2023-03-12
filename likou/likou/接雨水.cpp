#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
	int trap(vector<int>& height)
	{

		int result = 0;
		int n = height.size();
		if (n <= 2)
		{
			return 0;
		}
		//������ߵ�����
		int max = 0;
		int index = 0;
		for (int i = 0; i < n  ; i++)
		{
			if (height[i] > max)
			{
				max = height[i];
				index = i;
			}
		}
		//��������ӣ���Ϊ����������
		//�ȴ���������ӣ�����ߵ�����Ϊ�ߣ������ǣ���1��ʼ
		//��Ϊ�ұ���һ����ߵ����ӣ���˵�ǰλ���ܴ洢ˮ�ĸ߶Ƚ�ȡ���������������ӡ�
		int lmax = height[0];
		for (int i = 1; i < index; i++)
		{
			//�ұߵ�����С����ߵ����ӣ����Խ�ˮ
			if (height[i] <= lmax)
			{
				result += (lmax - height[i]);
			}
			//�ұߵ����Ӵ�����ߵ����ӣ���¼�¸߶�
			else
			{
				lmax = height[i];
			}
		}

		//ͬ�����Ҳ��ֵ�����
		int rmax = height[n - 1];
		for (int i = n - 2; i > index; i--)
		{
			//��ߵ�����С���ұߵ����ӣ����Խ�ˮ
			if (height[i] <= rmax)
			{
				result += rmax - height[i];
			}
			else
			{
				rmax = height[i];
			}
		}
		return result;
	}
};


