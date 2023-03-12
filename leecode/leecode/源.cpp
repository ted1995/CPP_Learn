#include<iostream>
using namespace std;
#include<string>
#include<deque>

class Solution {
public:
	string longestPalindrome(string s) {
		//一种是中心重复的如aa，一种是中心单个的如a
		//对于中心是重复的，有n-1的中心，中心是单个的，有n个中心
		string s1;
		for (int i=0;i<s.size();i++){
			if (s[i] != s[i + 1]) {
				s1.push_back(s[i]);
				while (i > 0){
					if (s[i - 1] == s[i + 1]){
						s1.insert(*s[i], s[i - 1]);
						s1.push_back(s[i + 1]);
						i--;
					}
					else
					{
						break;
					}
				}
			}
		}
		

	}
};

int main()
{
	string s = "abba";
	Solution s1;
	cout << s1.longestPalindrome(s) << endl;
	return 0;
}