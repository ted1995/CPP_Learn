#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size() - 1;
		//�ȴӺ���ǰ�ҳ��������������һ��Ԫ��a
		for (; i >= 1; i--)
		{
			if (nums[i] > nums[i - 1])
			{
				break;
			}
		}
		//���û�ҵ�������ǰ��Ϊ�������
		if (i == 0)
		{
			//��ת�������С����
			reverse(nums.begin(), nums.end());
			return;
		}

		//�ҵ�������������Ԫ��a�����ʱ��Ԫ�غ��������Ԫ�ض����������ٴ����һ�������ҵ���һ�����ڴ�Ԫ��a��Ԫ��b
		int j = nums.size() - 1;
		for (; j >= 0; j--)
		{
			if (nums[j] > nums[i - 1])
			{
				break;
			}
		}
		//����
		swap(nums[i - 1], nums[j]);
		//��תa֮�������Ԫ��
		reverse(nums.begin() + i , nums.end());
	}
};

