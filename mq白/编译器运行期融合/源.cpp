
//#define LOGDEBUG(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::debug,__VA_ARGS__);
//#define LOGERR(...) SPDLOG_LOGGER_CALL(m_logger,spdlog::level::level_enum::err,__VA_ARGS__);
#define For(n) for(int index = 0;index < n;++index)
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<vector>
#include<tuple>
#include<time.h>
//#include<output_Container.h>
//#include<spdlog/spdlog.h>
//#include<spdlog/logger.h>
//#include<spdlog/sinks/daily_file_sink.h>
using namespace std;
//template<typename T>
//struct type_wrapper {
//	using type = T;
//};
//
//template<typename T>
////����ģ��
////C++14�Ժ󣬱���Ҳ���Բ�����Ϊ�ض������ͣ����Ϊ����ģ�塣
//type_wrapper<T>type;

template<int s> struct Wow;
struct foo {
	int a, b;
};

//��θ���һ�������ڵ�ֵ����һ��������ģ�庯��
template<size_t N>
void fun() {
	//���ڲ�ͬ��N����ͬ�Ĵ���
	cout << N << endl;
}

namespace detail {
	template<class Tuple, class F, std::size_t...ls>
	//��һ�����б���
	auto tuple_switch(const std::size_t i, Tuple&& t, F&& f, std::index_sequence<ls...>) {
		(void)std::initializer_list<int>{
			//���i!=ls,��ô�����lambda����ִ��
			//����������ʱif(a&&b)��aΪ��������b�Ͳ���ִ�У�ʵ����switch�Ĺ���
			(i == ls && ((void)f(std::integral_constant<size_t, ls>{}), 0))...
		};
	}
}

template<class Tuple, class F>
inline void tuple_switch(const std::size_t i, Tuple&& t, F&& f) {
	constexpr auto N = std::tuple_size<std::remove_reference_t<Tuple>>::value;
	detail::tuple_switch(i, std::forward<Tuple>(t), std::forward<F>(f), std::make_index_sequence<N>{});
}

template<size_t ...ls>
auto make_tuple_from_sequence(std::index_sequence<ls...>)->decltype(std::make_tuple(ls...)) {
	return std::make_tuple(ls...);
}

template<size_t N>
constexpr auto make_tuple_from_sequence()->decltype(make_tuple_from_sequence(std::make_index_sequence<N>{})) {
	return make_tuple_from_sequence(std::make_index_sequence<N>{});
}

void foo1(int n) {
	//fun<n>();//����һ�����⣬�޷���һ�������ڵ�ֵ��Ϊ�����ڵĲ�����������ν���ת���أ�
	std::tuple<int, int, int, int, int> tp;//fun�ж���switch��֧,��д���ٸ�int
	tuple_switch(n, tp, [](auto item) {
		constexpr auto l = decltype(item)::value;
		fun<l>();
	});
}

//void foo2(int n) {
//	auto tp = make_tuple_from_sequence<10>();
//	tuple_switch(n, tp, [](auto item) {
//		constexpr auto l = decltype(item)::value;
//		Wow<l> wow;
//		fun<l>();
//	});
//}

int main() {
	//constexpr auto add_pointer = [](auto t) {
	//	using T = typename decltype(t)::type;
	//	//using add_pointer_t=typename add_pointer<T>::type;
	//	return type<std::add_pointer_t<T>>;//type to value
	//};
	//auto the_int_type = type<int>;//type to value �ӱ����ڵ�������
	//using the_real_int_type = decltype(the_int_type)::type;//value to type �������ڵ�������
	//constexpr auto intptr = add_pointer(type<int>);
	//static_assert(std::is_same_v<decltype(intptr)::type, int*>);
	srand(time(nullptr));
	int a = rand() % 10;
	cout << "a = " << a << endl;
	foo1(a);
	//auto b = std::forward(foo)(a);
	//(void)std::initializer_list<int>{(a==1&&(void)foo(1)),2};
	system("pause");
	return 0;
}