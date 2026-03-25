#include<iostream>
#include "pe-vector.hpp"

using zinoviev::Vector;

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

	test_t tests[] = {
		test_Constract_and_Destract,
		test_Default_Vec_is_empty
	};

	constexpr size_t count = sizeof(tests) / sizeof(test_t);
	for (size_t i = 0; i < count; ++i)
	{
		const char* teastName = nullptr;
		bool r = tests[i](&teastName);

		if (!r)
			std::cout << "Error:" << teastName << "\n";
	}
}
