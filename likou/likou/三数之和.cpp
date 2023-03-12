#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

class Solution {
public:
	vector<vector<int>> threeSum(vector<int>& nums) {
		//先排序
		sort(nums.begin(), nums.end());
		//确定一个量，使用双指针，遍历另外两个
		int l = 0;
		int r = 0;
		vector<vector<int>> res;
		if (nums.empty())
		{
			return res;
		}
		//遍历选定一个变量
		for (int i = 0; i < nums.size(); i++)
		{
			//排序后最小的大于0，则和不可能为0
			if (nums[i] > 0)
			{
				return res;
			}
			//大变量去重，新的变量如果和旧的一样，那么最终和为0,另外两个变量也一样
			if (i > 0 && nums[i] == nums[i - 1])
			{
				continue;
			}
			//确定双指针的位置
			l = i + 1;
			r = nums.size() - 1;
			//双指针循环
			while (l < r)
			{
				if (nums[l] + nums[r] + nums[i] == 0)
				{
					//找到了和为0的三元组
					res.push_back(vector<int>{nums[i], nums[l], nums[r]});
					//缩小范围继续找
					l++;
					r--;
					//小三元组去重，如果新的左或右指针和原本的相同，则构成的三元组与相同
					while(l<r && nums[l] == nums[l - 1])
						l++;
					while(l<r && nums[r] == nums[r + 1])
						r--;
				}
				//太大，右指针左移
				else if (nums[l] + nums[r] + nums[i] > 0)
				{
					r--;
				}
				//太小，左指针右移
				else
				{
					l++;
				}
			}
		}
		return res;
	}
};


