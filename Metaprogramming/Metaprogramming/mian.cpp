﻿// Metaprogramming.cpp: определяет точку входа для приложения.
//
#include <iostream>
#include <type_traits>
#include <string>
#include <vector>
#include <list>
#include <tuple>


template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void print_ip(T value) {

	uint8_t* ptr = (uint8_t*)&value;

	for (int i = sizeof(T)-1; i >= 0; --i) {
		std::cout << (uint32_t)*(ptr+i);
		if (i) {
			std::cout << ".";
		}
	}
	std::cout << "\n";
}

template<bool = true>
void print_ip(std::string string) {
	std::cout << string << std::endl;
}

template<typename T>
concept Iterable = requires(T x) {
	{ std::begin(x) } -> std::convertible_to<typename T::iterator>;
	{ std::end(x) } -> std::convertible_to<typename T::iterator>;
};

template<Iterable T>
struct is_iterable: std::true_type {};

template<typename T, std::enable_if_t<is_iterable<T>::value, bool> = true>
void print_ip(const T& value) {
	auto it = value.begin();
	for (size_t i = value.size(); i > 0; --i, it++) {
		std::cout << *it;
		if (i != 1) {
			std::cout << ".";
		}
	}
	std::cout << "\n";
}


int main()
{

	print_ip(2); // 255 
	print_ip(int8_t{ -1 }); // 255 
	print_ip(int16_t{ 0 }); // 0.0 
	print_ip(int32_t{ 2130706433 }); // 127.0.0.1 
	print_ip(int64_t{ 8875824491850138409 });// 123.45.67.89.101.112.131.41 
	print_ip(std::string{ "Hello, World!"}); // Hello, World! 
	print_ip(std::vector<int>{100, 200, 300, 400}); // 100.200.300.400 
	print_ip(std::list<short>{400, 300, 200, 100}); // 400.300.200.100 
	//print_ip(std::make_tuple(123, 456, 789, 0)); // 123.456.789.0 

	return 0;
}
