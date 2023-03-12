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
		//当双指针重合时，容器面积为0，结束求取面积
		while (left < right)
		{
			//求出容器的面积
			area = (right - left)*min(height[left], height[right]);
			//求最大的面积
			maxarea = max(maxarea, area);
			//移动容器最短的柱子,计算新的容器面积，因为移动最长的柱子永远只会让容器的面积变小，找不到最大的容器面积
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
