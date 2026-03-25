#ifndef PE_VECTOR_HPP
#define PE_VECTOR_HPP

namespace zinoviev
{
	template <class T>
	struct Vector
	{
		T* data;
		size_t size, capasity;
	};
}

#endif
