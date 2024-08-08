#include <iostream>
#include <stack>
#include <vector>

using namespace std;

std::vector<int> findNextSmallerElements(const std::vector<int>& nums) {
	std::vector<int> result(nums.size(), -1); // Ĭ��Ϊ -1����ʾ�Ҳ�����С��Ԫ��
	std::stack<int> st; // ����ջ������Ԫ�ص��±�

	for (int i = 0; i < nums.size(); i++) {
		while (!st.empty() && nums[st.top()] > nums[i]) {
			result[st.top()] = i; // ����ջ��Ԫ�ص���һ����СԪ�ص��±�
			st.pop(); // ����ջ��Ԫ��
		}
		st.push(i); // ����ǰԪ�ص��±�ѹ��ջ��
	}

	return result;
}
//����������������������������±�
vector<pair<int, int>> monoStack(const std::vector<int>& arrs)
{
	int len = arrs.size();
	stack<int> s;
	vector<pair<int, int>> res;
	res.resize(len);
	for (int i = 0; i < len; ++i)
	{
		while (!s.empty() && arrs[i] > arrs[s.top()])
		{
			//��ʱ�����ڱ��������Ǹ�������߱�������������µģ��ұ߱�������Ǽ���������
			int curr = s.top();
			res[curr].second = i; //�ұ�
			s.pop();
			res[curr].first = s.empty() ? -1 : s.top(); //���
		}
		s.push(i);
	}
	while (!s.empty())
	{
		int curr = s.top();
		res[curr].second = -1; //�ұ�
		s.pop();
		res[curr].first = s.empty() ? -1 : s.top(); //���
	}
	return res;
}