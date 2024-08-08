#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
//��һλ���ҿ���ȡ�����±꣬��������±��Ӧ����ĸ�����Ҫ��ʣ����ĸ��ȥ����Ȼ���һλ���Ķ���ӡ����
//�ڶ�λ��ֻ��ȡn-1���±���
void process(std::string str, std::string& curStr)
{
	if (str.empty())
	{
		cout << curStr << endl;
		return;
	}
	cout << curStr << endl;
	for (int i = 0; i < str.size(); ++i)
	{
		std::string tmpStr = curStr + str[i];
		std::string restStr = str;
		restStr.erase(std::remove(restStr.begin(), restStr.end(), restStr[i]), restStr.end());
		process(restStr, tmpStr);
	}
}

void PrintAllPermutations(std::string str)
{
	std::string res;
	process(str, res);
}