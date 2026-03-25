#include "pe-vector.hpp"

using zinoviev::Vector;

bool test1()
{
	Vector< int > v;
	return true;
}

bool test2()
{
	Vector< int > v;
	return v.is_empty();
}


int main()
{
	using test_t = bool(*)();

	test_t tests[] = {
		test1
	};

	constexpr size_t count = sizeof(tests) / sizeof(test_t);
	for (size_t i = 0; i < count; ++i)
	{
		bool r = tests[i];
		if (!r)
			return 1;
	}
}
