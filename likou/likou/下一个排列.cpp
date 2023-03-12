#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size() - 1;
		//先从后往前找出不满足升序的那一个元素a
		for (; i >= 1; i--)
		{
			if (nums[i] > nums[i - 1])
			{
				break;
			}
		}
		//如果没找到，即当前即为最大排列
		if (i == 0)
		{
			//反转，变成最小排列
			reverse(nums.begin(), nums.end());
			return;
		}

		//找到了这个不满足的元素a，则此时此元素后面的所有元素都满足升序，再从最后一个找起，找到第一个大于此元素a的元素b
		int j = nums.size() - 1;
		for (; j >= 0; j--)
		{
			if (nums[j] > nums[i - 1])
			{
				break;
			}
		}
		//交换
		swap(nums[i - 1], nums[j]);
		//反转a之后的所有元素
		reverse(nums.begin() + i , nums.end());
	}
};

