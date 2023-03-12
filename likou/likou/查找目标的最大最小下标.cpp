#include<iostream>
#include<vector>
using namespace std;


class Solution {
public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		vector<int> res;
		int n = nums.size();
		if (n == 0)
		{
			res = { -1,-1 };
			return res;
		}
		if (n == 1)
		{
			return nums[0] == target ? res = { 0,0 } : res = { -1,-1 };
		}
		//二分，先查一个，升序数组，按顺序查找
		int l = 0, r = n - 1;
		vector<int> v;
		while (l <= r)
		{
			int mid = (l + r) / 2;
			if (nums[mid] == target)
			{
				v.push_back(mid);
				for (int i = mid - 1; i >= 0; i--)
				{
					if (nums[i] != target)
					{
						break;
					}
					if (nums[i] == target)
					{
						v.push_back(i);
					}
				}
				for (int j = mid + 1; j <= nums.size() - 1; j++)
				{
					if (nums[j] != target)
					{
						break;
					}
					if (nums[j] == target)
					{
						v.push_back(j);
					}
				}
				if (v.size() == 1)
				{
					res.push_back(v[0]);
					return res;
				}
				res.push_back(v.front());
				res.push_back(v.back());
				return res;
			}
			//目标数小于中位数
			if (target < nums[mid])
			{
				r = mid - 1;
			}
			else
			{
				l = mid + 1;
			}
		}
		res = { -1,-1 };
		return res;
	}
};
