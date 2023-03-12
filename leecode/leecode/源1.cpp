#include<iostream>
using namespace std;
#include<string>
#include<vector>

class Solution {
public:
	string convert(string s, int numRows) {
		/*1.起始下标都是行号

		  2.第0层和第numRows - 1层的下标间距总是step 。

		  3.中间层的下标间距总是step - 2 * 行数，2 * 行数交替。

		  4.下标不能超过len(s) - 1*/
		//定义步距step等于行数乘2
		int step

	}
};


int main()
{
	string s = "LEETCODEISHIRING";
	int a=3;
	Solution s1;
	cout << s1.convert(s,a) << endl;
	return 0;
}