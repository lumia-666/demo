#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Bitmap { 
	int data_;
};
class Widget {
public:

private:
	Bitmap * pb;  //ָ�룬ָ��һ����heap������õĶ���
};

//���ܵ�һ�ۿ�ûʲô���⣬���������Ĳ���rhs���������أ���ͻᵼ��delete����*this�Լ�����Դ�ͷŵ���
//ͬʱҲ�ͷŵ���rhs����Դ����󣬷��ص�*this������һ���𻵵����ݣ��㲻�ܷ��ʲ����޸ģ�
//��������ͨ��delete��Ϊ���ͷ���Դ������˵����ڴ�ռ��ƾ����ʧ�ˡ����ԣ���δ��벻���Ը�ֵ��ȫ��
Widget& Widget::operator=(const Widget& rhs) //һ�ݲ���ȫ��operator=ʵ�ְ汾
{
	//�������ָ���Ա����Ҫʹ�����
	delete pb;   //ֹͣʹ�õ�ǰ��bitmap
	pb = new Bitmap(*rhs.pb); //ʹ��rhs's bitmap�ĸ���
	return *this;
}

//���Ҹ�ֵ��⣺��ʽһ
//����������ǵ������Ҹ�ֵ�İ�ȫ�����⣬����Ȼ�����쳣��ȫ�ġ����ִ����delete����
//��ִ�������new���ʱ�׳����쳣(�����ڴ治�㡢�������캯���׳��쳣)�����Ҳ�ᵼ��*this������һ���𻵵�����
Widget& Widget::operator=(const Widget& rhs)
{
	if (this == &rhs) return *this; //֤ͬ���ԣ���������Ҹ�ֵ�����κ���

	delete pb;   //ֹͣʹ�õ�ǰ��bitmap
	pb = new Bitmap(*rhs.pb); //ʹ��rhs's bitmap�ĸ���
	return *this;
}

//���Ҹ�ֵ��⣺��ʽ��
//���ڣ������new Bitmap���׳��쳣��pb����ԭ״�����ᱻdelete��
Widget& Widget::operator=(const Widget& rhs)
{
	Bitmap* pOrig = pb;   //��סԭ�ȵ�pb
	pb = new Bitmap(*rhs.pb); //��pbָ��һ��*pb��һ������
	delete pOrig;      //ɾ��ԭ�ȵ�pb
	return *this;
}


int main() 
{

	system("pause");
	return 0;
}