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
		//先找最高的柱子
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
		//按最高柱子，分为左右两部分
		//先处理左边柱子，最左边的柱子为边，不考虑，从1开始
		//因为右边有一个最高的柱子，因此当前位置能存储水的高度仅取决于坐标的最高柱子。
		int lmax = height[0];
		for (int i = 1; i < index; i++)
		{
			//右边的柱子小于左边的柱子，可以接水
			if (height[i] <= lmax)
			{
				result += (lmax - height[i]);
			}
			//右边的柱子大于左边的柱子，记录下高度
			else
			{
				lmax = height[i];
			}
		}

		//同理处理右部分的柱子
		int rmax = height[n - 1];
		for (int i = n - 2; i > index; i--)
		{
			//左边的柱子小于右边的柱子，可以接水
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


