#include <iostream>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <iterator>
template <typename>
using void_t = void;

template <typename T, typename V = void>
struct has_push_back :std::false_type {};//�̳�std::false_type

//std::declval<T>()����T���͵���ֵ����
//decltype��ȡ���Ͳ����ú���
template <typename T>
//������Ļ���ģ������һ���ػ�
struct has_push_back<T, void_t<decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>> :std::true_type {};

int main() {
	//test<int,std::string>();
	//std::vector<const int> v{ 1,2,3 };
	//std::vector<const int>::iterator cIter = v.begin();
	//*cIter = 2;//ָ��ָ��Ķ����޷����޸�,�൱��value_type��һ��const����
	std::cout << has_push_back<std::list<int>>::value << std::endl;
	std::cout << has_push_back<std::map<int, int>>::value << std::endl;
	std::cout << has_push_back<std::set<int>>::value << std::endl;
	std::cout << has_push_back<std::string>::value << std::endl;
	std::cout << has_push_back<std::vector<int>>::value << std::endl;
	return 0;
}