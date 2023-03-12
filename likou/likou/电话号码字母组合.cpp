#include<iostream>
#include<map>
#include<string>
#include<vector>
using namespace std;



class Solution {
private:
	map<char, string> letterMap = {
		{'0',""},
		{'1',""},
		{'*',""},
		{'#',""},
		{'2',"abc"},
		{'3',"def"},
		{'4',"ghi"},
		{'5',"jkl"},
		{'6',"mno"},
		{'7',"pqrs"},
		{'8',"tuv"},
		{'9',"wxyz"}
	};
public:
	//存放组合结果
	vector<string> result;
	//存放单个组合
	string s;
	//回溯算法
	void backtrace(const string& digit, int index)
	{
		//所有拨号数字都遍历了，递归终止条件
		if (index == digit.size())
		{
			//将此字母组合放到结果中，保存下来，因为每一轮递归结束，都会
			result.push_back(s);
			return;
		}
		//通过整数取出对应的字母串
		string temp = letterMap[digit[index]];
		//对字母串进行遍历
		for (int i = 0; i < temp.size(); i++)
		{
			//将一个字母放进组合中
			s.push_back(temp[i]);
			//索引转到下一个拨号数字
			index++;
			//用递归将下一个拨号数字对应的字母串中的字母也放进组合中
			backtrace(digit, index);
			//将放进s组合中字母都删掉，供下一次使用
			s.pop_back();
			index--;
		}
	}

	vector<string> letterCombinations(string digits)
	{
		if (digits.size() == 0)
		{
			return result;
		}
		int index = 0;
		backtrace(digits, index);
		return result;
	}
};

