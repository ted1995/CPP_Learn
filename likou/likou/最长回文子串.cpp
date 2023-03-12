#include<iostream>
using namespace std;
#include<string>
#include<algorithm>

int expandFromCentern(string s, int left, int right);

string longestPalindrome(string s)
{
	if (s.length() < 1)
	{
		return "";
	}
	int start = 0, end = 0;
	int maxlen = 0, maxi = 0, maxrecord1 = 0, maxrecord2 = 0;
	for (int i = 0; i < s.length(); i++)
	{
		//��˫������չ������һ���������ĵ�һ�αȽϱ���ȣ�������������չҪ��һ
		//�������һ��Ĵ�
		int return1=expandFromCentern(s, i, i);
		int record1 = return1 - 1;
		int len1 = record1 * 2 + 1;
		//˫������չ���൱�ڴ�0��չ����һ�αȽ�������൱����չ��һ��
		//˫�����һ��Ĵ�
		int return2=expandFromCentern(s, i, i + 1);
		int record2 = return2;
		int len2 = record2 * 2;
		int len = max(len1, len2);
		if (maxlen < len)
		{
			maxi = i;
			maxlen = len;
			maxrecord1 = record1;
			maxrecord2 = record2;
		}
	}
	if (maxlen%2)
	{

		start = maxi - maxrecord1;
		end = maxi + maxrecord1;
	}
	else
	{
		start = maxi - maxrecord2-1;
		end = maxi  + maxrecord2;
	}
	return s.substr(start, end - start + 1);
}

//������ͷ��ʼ��ÿһ��Ԫ�ض���Ϊ����Ԫ�أ���������չ��
//ÿ��������չһ�Σ��ͱȽ϶Գ�λ�õ�Ԫ���Ƿ���ȣ�
//��ȼ�����չ�Ƚϣ������ֹͣ�Ƚϣ���¼����չ����
int expandFromCentern(string s, int left, int right)
{
	int l = left, r = right;
	int record = 0;
	//������
	while (l >= 0 && r <= s.length() && s[l] == s[r])
	{
		l--;
		r++;
		record++;
	}
	return record;
}




