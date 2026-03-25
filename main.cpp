#include "pe-vector.hpp"

bool test1()
{
	zinoviev::Vector< int > v;
	return true;
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
		if (!tests[i])
			return 1;
	}
}
