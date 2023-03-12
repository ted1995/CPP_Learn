#include<iostream>
using namespace std;
#include<vector>

class Solution {
public:
	//
	int search(vector<int>& nums, int target)
	{
		int n = nums.size();
		//空集合
		if (n == 0)
		{
			return -1;
		}
		//只有一个元素
		if (n == 1)
		{
			return nums[0] == target ? 0 : -1;
		}
		//升序数组，先使用二分，判断target在哪边的数组中
		int l = 0, r = n - 1;
		int mid = 0;
		while (l <= r)
		{
			mid = (l + r) / 2;
			//如果中间数正好等于目标，直接返回
			if (nums[mid] == target)
			{
				return mid;
			}
			//判断二分之后哪边是有序的
			if (nums[l] <= nums[mid])
			{
				//左边是有序的，且目标正好在左边
				if (nums[l] <= target && target < nums[mid])
				{
					//重新设定右边界
					r = mid - 1;
				}
				else
				{
					//重新设定左边界
					l = mid + 1;
				}
			}
			else
			{
				//右边是有序的，且目标正好在右边
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

