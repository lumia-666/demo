#pragma once
#include<format>
#include<iostream>
#include<ranges>
#include<map>
#include<vector>
#include<filesystem>

template < typename... Args>
void print(const std::string_view fmt_str, Args&&... args) {
	auto fmt_args{ std::make_format_args(args...) };
	std::string outstr{ std::vformat(fmt_str, fmt_args) };
	fputs(outstr.c_str(), stdout);
}

template <typename Container>
concept ContainerChecker = requires (const Container & c) {//��std::ranges::range�ȼ�
	std::ranges::begin(c);
	std::ranges::end(c);
};

template <ContainerChecker Ranges, typename CharT>
struct std::formatter<Ranges, CharT> {
	constexpr auto format(const Ranges& rg, auto& format_context) {
		auto iter = std::format_to(format_context.out(), "{}", '[');//�൱������format_context����һ��'['��ʹ�õ�{}��ʽ���ķ�ʽ�����һ᷵��ĩβ�����������涼��������
		auto begin = std::ranges::begin(rg);
		auto end = std::ranges::end(rg);
		std::basic_string_view<CharT> fmt(m_fmt, m_fmt + m_buffer_len);//ʹ�����ݳ�Ա�ַ�����������һ��string_view��ʹ��ӵ�к��ַ�����һ��������
		for (auto vec_iter = begin; vec_iter != end; ++vec_iter) {
			if (vec_iter != begin) {//��һ����==begin�ģ�����ִ�У������ִ��
				iter = ',', iter = ' ';//�����Ǹ�iter�ظ���ֵ��ʵ���������Լ��������ӣ��൱�������������������','��' '
			}
			iter = std::vformat_to(format_context.out(), fmt, std::make_format_args(*vec_iter));//��һ��Ԫ�ز��뵽format_context������ĩβ������
		}
		iter = ']';//�൱���ٲ�����һ��']'
		return iter;
	}
	constexpr auto parse(auto& context) {//�����ȵ���parse��Ա�������õ���ȷ�ĸ�ʽ���ַ�������formatʹ��
		m_fmt[m_buffer_len++] = '{';//�ȷ���һ��'{'
		auto iter = context.begin();
		if (iter == context.end() || *iter == '}') {
			m_fmt[m_buffer_len++] = '}';
			return iter;
		}
		m_fmt[m_buffer_len++] = ':';//�����һ��ûreturn �˳���Ҳ���ǲ��ǵ�����{}����ô����Ҫ��һ��:���������൱���Ѿ�������{:
		for (; iter != context.end() && *iter != '}'; ++iter) {
			m_fmt[m_buffer_len++] = *iter;
		}
		m_fmt[m_buffer_len++] = '}';//������'}'
		return iter;
	}
private:
	CharT m_fmt[16]{};  //�洢��ʽ���ַ����Ļ�����
	size_t m_buffer_len = 0;
};

template<typename T>
concept Tuple = requires (T v) {
	[] <typename... T2>(const std::tuple<T2...>&tup) {}(v);
};

template<Tuple T, typename CharT>
struct std::formatter<T, CharT> {
	using fmt_str_t = std::basic_string<CharT>;

	constexpr auto parse(auto& ctx) {
		auto ictx = std::begin(ctx);//ֵ��ע�����ctx��������ǰ���{��:֮��ģ�ֱ�Ӿ��Ǹ�ʽ�ַ�����Ҳ���������ڹ���string_view��ԭ��
		auto ectx = std::end(ctx);
		while (true) {
			auto rbra = std::find_if(ictx, ectx, [](auto v) {return v == '}' | v == '|'; });
			auto viewt = std::vector<std::basic_string_view<CharT>>{ "{:", {ictx, rbra}, "}" } | std::views::join;
			m_fmt.push_back(fmt_str_t(std::begin(viewt), std::end(viewt))); // wish for std::ranges::to
			if (rbra != ectx && *rbra != '}') ictx = rbra + 1;
			else { return rbra; }
		}
	}
	constexpr auto format(Tuple auto& rg, auto& ctx) const {
		constexpr int N = std::tuple_size_v<std::remove_reference_t<decltype(rg)>>;
		auto iter = std::format_to(ctx.out(), "{}", '[');
		auto fmt_iter = std::begin(m_fmt);
		auto fmt_end = std::end(m_fmt);
		const auto empty = std::string{ "{}" };
		[&] <Tuple TupleType>(const TupleType & rg) {
			[&] <size_t... I>(std::index_sequence<I...>) {
				(..., (
					iter = std::vformat_to(ctx.out(),
						fmt_iter != fmt_end ? *(fmt_iter++) : empty, // if there is more tuple elements than fmt args, use "{}" for those missing fmt
						std::make_format_args(std::get<I>(rg))
					), I + 1 != N ? iter = ' ' : iter = ']'));
			}(std::make_index_sequence<N>());
		}(rg);
		return iter;
	}
private:
	std::vector<fmt_str_t> m_fmt;
};

namespace fs = std::filesystem;
template<>
struct std::formatter<fs::path> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext& ctx) {
		return ctx.begin();
	}
	template<typename FormatContext>
	auto format(const fs::path& p, FormatContext& ctx) {
		return std::format_to(ctx.out(), "{}", p.string());
	}
};

void print(std::ranges::range auto v) {
	print("size: {}  ", v.size());
	print("[ ");
	for (const auto& i : v)print("{} ", i);
	print("]\n");
}

template<class T, class T2>
void print(const std::map<T, T2>& map) {
	print("size: {} ", map.size());
	print("[ ");
	for (auto& [k, v] : map)print("{}:{} ", k, v);
	print("]\n");
}

template<class T, class T2>
void rprint(std::multimap<T, T2>& todo) {
	for (const auto& i : todo | std::views::reverse) {
		print("{}: {}\n", i.first, i.second);
	}
	print("\n");
}

void printc(const std::ranges::range auto& v, std::string_view s = "") {
	if (s.size())print("{}: ", s);
	for (const auto& i : v)print("[{}] ", i);
	print("\n");
}

void printr(const auto& r, std::string_view s = "") {
	auto rbegin = std::rbegin(r);
	auto rend = std::rend(r);
	for (auto it = rbegin; it != rend; ++it) {
		print("{} ", *it);
	}
	print("\n");
}