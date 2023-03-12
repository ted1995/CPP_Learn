#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Solution {
public:
	int maxArea(vector<int>& height) {
		int left = 0;
		int right = height.size()-1;
		int area = 0;
		int maxarea = 0;
		//��˫ָ���غ�ʱ���������Ϊ0��������ȡ���
		while (left < right)
		{
			//������������
			area = (right - left)*min(height[left], height[right]);
			//���������
			maxarea = max(maxarea, area);
			//�ƶ�������̵�����,�����µ������������Ϊ�ƶ����������Զֻ���������������С���Ҳ��������������
			if (height[left] < height[right])
			{
				left++;
			}
			else
			{
				right--;
			}
		}
		return maxarea;
	}
};
