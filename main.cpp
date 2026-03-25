#include<iostream>
#include "pe_vector.hpp"
#include<cstddef>

using zinoviev::Vector;

bool test_getSie(const char** teastName)
{
	*teastName = __func__;
	Vector< int > v;
	return !v.getSize();
}

bool test_Non_mempty(const char** teastName)
{
	return false;
}

bool test_Constract_and_Destract(const char** teastName)
{
	*teastName = __func__;
	Vector< int > v;
	return true;
}

bool test_Default_Vec_is_empty(const char** teastName)
{
	*teastName = __func__;
	Vector< int > v;
	return v.is_empty();
}


int main()
{
	using test_t = bool(*)(const char**);
	using case_t = std::pair<test_t, const char*>;

	case_t tests[] = {
		{test_Constract_and_Destract, "Vect must be default"},
	    {test_Default_Vec_is_empty, "Defult Vector must be empty"},
		{test_getSie, "Size of empty vector must be 0"},
		{test_Non_mempty, "Size of non-empty vector must be !0"}
	};

	size_t f = 0;
	constexpr size_t count = sizeof(tests) / sizeof(test_t);
	for (size_t i = 0; i < count; ++i)
	{
		const char* teastName = nullptr;
		bool r = tests[i].first(&teastName);

		if (!r)
		{
			++f;
			std::cout << "Error:" << teastName << "\n";
			std::cout << "\t" << tests[i].second << "\n";
		}
	}

	std::cout << "Summer:\n\t" << (count - f) << "\n";
	std::cout << "Fail" << count << "total\n";
}
