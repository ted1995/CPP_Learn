#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	//
	int search(vector<int>& nums, int target)
	{
		int n = nums.size();
		//�ռ���
		if (n == 0)
		{
			return -1;
		}
		//ֻ��һ��Ԫ��
		if (n == 1)
		{
			return nums[0] == target ? 0 : -1;
		}
		//�������飬��ʹ�ö��֣��ж�target���ıߵ�������
		int l = 0, r = n - 1;
		int mid = 0;
		while (l <= r)
		{
			mid = (l + r) / 2;
			//����м������õ���Ŀ�ֱ꣬�ӷ���
			if (nums[mid] == target)
			{
				return mid;
			}
			//�ж϶���֮���ı��������
			if (nums[l] <= nums[mid])
			{
				//���������ģ���Ŀ�����������
				if (nums[l] <= target && target < nums[mid])
				{
					//�����趨�ұ߽�
					r = mid - 1;
				}
				else
				{
					//�����趨��߽�
					l = mid + 1;
				}
			}
			else
			{
				//�ұ�������ģ���Ŀ���������ұ�
				if (nums[mid] < target&&target <= nums[n - 1])
				{
					l = mid + 1;
				}
				else
				{
					r = mid - 1;
				}
			}
		}
		return -1;
	}
};

