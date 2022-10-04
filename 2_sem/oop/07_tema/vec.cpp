#include <gsl/gsl_assert>
#include <iostream>
#include <algorithm>
#include <memory>

#include "./vec.hpp"

VecException::VecException(const std::string &msg) : msg(msg) { }

void test_vec() {
	Vec<int> vec;
	
	// push_back
	for (int i = 0; i < 1000; ++i) {
		vec.push_back(i);
	}
	
	// operatori de acces
	for (int i = 0; i < 1000; ++i) {
		Ensures(vec[i] == i);
	}
	for (int i = 0; i < 1000; ++i) {
		vec[i] = i*7+12;
	}
	try { vec[1234]; Ensures(false); }
	catch(VecException &ex) { }
	
	// constructor de copiere
	Vec<int> copy = Vec<int>(vec);
	
	// iterator
	{
		int i = 0;
		for (const auto &elem : vec) {
			Ensures(elem == i*7+12);
			i++;
		}
	}
	
	{
		int i = 0;
		for (auto it = vec.begin(); it < vec.end(); ++it) {
			const auto &const_it = it;
			Ensures(*const_it == i*7+12);
			i++;
		}
	}
	
	{
		int i = vec.size()-5;
		for (auto it = vec.end()-5; it < vec.end(); ++it) {
			const auto &const_it = it;
			Ensures(*const_it == i*7+12);
			i++;
		}
	}
	
	auto it_end = vec.end();
	try { *it_end; Ensures(false); }
	catch(VecException &ex) { }
	
	const auto const_it_end = vec.end();
	try { *const_it_end; Ensures(false); }
	catch(VecException &ex) { }
	
	// dealocare de elemente
	Vec<std::string> strvec;
	strvec.push_back("asdas");
	strvec.push_back("asdasfdafdfafa");
	strvec.push_back("asf afadfad faffd");
	strvec.push_back("as fasf dagd dafsds");
	
	// sort
	Vec<int> test_numbers = { 1, 2, 3, 4, 5, 6, 7, 8 };
	Vec<int> numbers = { 7, 2, 8, 6, 3, 5, 1, 4 };
	std::sort(numbers.begin(), numbers.end());
	Ensures(numbers == test_numbers);
}
