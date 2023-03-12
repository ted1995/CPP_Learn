#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& T) {
		//使用一个递减栈，
		//小于当前栈顶的元素,入栈，找与其最近的最大值
		//大于当前栈顶的元素说明找到了最近的最大值，计算下标差值，移除栈顶元素
		int n = T.size();
		
	}
};