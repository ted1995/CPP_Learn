#include<iostream>
using namespace std;
#include<string>
#include<deque>

class Solution {
public:
	string longestPalindrome(string s) {
		//һ���������ظ�����aa��һ�������ĵ�������a
		//�����������ظ��ģ���n-1�����ģ������ǵ����ģ���n������
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