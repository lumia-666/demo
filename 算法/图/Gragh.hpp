#pragma once
#include <iostream>
using namespace std;
#define MAX 20 //���峣��ֵΪ20 

struct Edge {
	int weight;
	int aimNode;//ָ��Ľڵ�
	Edge* nextEdge;
};
typedef struct Node {
	char data; //���� 
	Edge *firstEdge; //�Ӹõ��ȥ�ĵ�һ���ߣ��õ��ȥ�������ıߴ��ں���
};
//����ͼ���ڽӱ�洢�ṹ 
typedef struct {
	Node nodeList[127]; //�ڵ����� 
	int n; //ͼ�Ķ�����
	int e; //ͼ�ı��� 
}Graph;

//����ͼ���ڽӱ�
void createGraph(Graph &G) {
	int i, j, k, w; //�������� 
	cout << "����ͼ�Ķ�����:";
	cin >> G.n;
	cout << "����ͼ�ı���:";
	cin >> G.e;
	cout << endl; //���� 
	cout << "����ͼ�ĸ�����(�洢��Ŵ�0��ʼ)��" << endl;
	for (i = 0; i < G.n; i++) {  //������n������Ķ����
		cout << "��" << i << "��������Ϣ��";
		cin >> G.nodeList[i].data; //�������ݴ����ͷ 
		G.nodeList[i].firstEdge = NULL; //�߱�ͷָ������Ϊ�� 
	}
	cout << endl; //���� 
	cout << "����ͼ�еıߣ�������Ŵ�0��ʼ:" << endl;
	Edge* tempEdge;
	for (k = 0; k < G.e; k++) {
		cout << endl; //���� 
		cout << "�����" << k + 1 << "����:" << endl;
		cout << "��������������ţ�";
		cin >> i;
		cout << "����ָ�򶥵�����:";
		cin >> j;
		cout << "����Ȩֵ:";
		cin >> w;
		//�ڽӱ�洢���� 
		tempEdge = new Edge; //����洢�ռ� 
		tempEdge->weight = w;
		tempEdge->aimNode = j;
		//ָ�����ͷ����������ԭ����ͷ�ڵ��Ϊ�½ڵ�Ķ��ӣ������µĽڵ��Ϊͷ
		tempEdge->nextEdge = G.nodeList[i].firstEdge; //�µĽ���ָ������Ϊ�� 
		G.nodeList[i].firstEdge = tempEdge; //�½����Ϣ���δ����ڽӱ��� 
	}
}

//����ڽӱ�
void printGraph(Graph G) {
	int i; //�������� 
	Edge *edge; //������� 
	cout << "�ڽӱ��еĴ洢����������ʾ��" << endl;
	for (i = 0; i < G.n; i++) {
		cout << i << ' ' << G.nodeList[i].data; //�����ͷ�������� 
		edge = G.nodeList[i].firstEdge; //ָ����һ��� 
		while (edge != NULL) {
			cout << "--->" << edge->aimNode << ' '; //˳����������Ϣ 
			edge = edge->nextEdge;
		}
		cout << endl; //���� 
	}
}