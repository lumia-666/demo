#pragma once
#include <string>
#include <deque>
#include <queue>
#include <vector>
using namespace std;
//ά��һ�����ȶ��У��ж϶Ѷ�Ԫ���Ƿ��ڴ����У������ڴ�����˵���Ѿ��ڴ��������
//��ʱ���������Ƴ���ֱ���Ѷ��ڴ�����λ�ã���ʱ�Ѷ����Ǵ��ڵ����ֵ
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> ans;
	if (n < k || k < 1)
	{
		return ans;
	}
	priority_queue<pair<int, int>> q;
	for (int i = 0; i < k; ++i) {
		q.emplace(nums[i], i);
	}
	ans = { q.top().first };
	for (int i = k; i < n; ++i) {
		q.emplace(nums[i], i);
		while (q.top().second <= i - k) {
			q.pop();
		}
		ans.push_back(q.top().first);
	}
	return ans;
}
//����������һ��˫�˶���,�����ŵ����±�,������еĴ�С���ǹ̶��Ļ�һֱ�仯
//��Ԫ�ؽ�����ʱ��ӵײ���ʼ�Ƚϣ��ȵײ�Ԫ�ش�������ӵײ�����
vector<int> dandiaoQueue(vector<int>& nums, int k) {
	int n = nums.size();
	vector<int> res;
	if (n < k || k < 1)
	{
		return res;
	}
	deque<int> q;
	for (int i = 0; i < k; ++i) {
		while (!q.empty()&&nums[i] >= nums[q.back()])
		{
			q.pop_back();
		}
		q.push_back(i);
	}
	vector<int> ans = { nums[q.front()]};
	for (int i = k; i < n; ++i) {
		while (!q.empty() && nums[i] >= nums[q.back()])
		{
			q.pop_back();
		}
		q.push_back(i);
		while (q.front() <= i - k) {
			q.pop_front();
		}
		ans.push_back(nums[q.front()]);
	}
	return ans;
}