#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
using namespace std;
int CALC = 0;
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() = default;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
struct ListNode
{
	int value = 0;
	ListNode* next = nullptr;
	ListNode() = default;
	ListNode(int val) :value(val) {};
	bool operator==(ListNode& node) {
		return (this->value == node.value && this->next == node.next);
	}
};
struct Edge {
	int weight;
	int aimNode;//ָ��Ľڵ�
	Edge* nextEdge;
};
typedef struct Node {
	char data; //���� 
	Edge* firstEdge; //�Ӹõ��ȥ�ĵ�һ���ߣ��õ��ȥ�������ıߴ��ں���
};
//����ͼ���ڽӱ�洢�ṹ 
typedef struct {
	Node nodeList[127]; //�ڵ����� 
	int n; //ͼ�Ķ�����
	int e; //ͼ�ı��� 
}Graph;

void process(string str, vector<string>& wordDict)
{

}

bool wordBreak(string s, vector<string>& wordDict) {
	if (s.empty())
	{
		++CALC;
		return true;
	}
	for (auto& word : wordDict)
	{
		if (word.size() <= s.size() && s.substr(0, word.size()) == word)
		{
			string temp{ s.substr(word.size(),s.size() - word.size()) };
			wordBreak(temp, wordDict);
		}
	}
}

int main() {
	vector<string> wordDict{ "car","ca","rs" };
	auto res = wordBreak("cars", wordDict);
	system("pause");
	return 0;
}