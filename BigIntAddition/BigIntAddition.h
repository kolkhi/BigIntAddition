#pragma once

#include <iostream>
#include <cstdint>

namespace BigIntAddition
{
	const int64_t _MIN_INT64 = std::numeric_limits<int64_t>().min();
	const int64_t _MAX_INT64 = std::numeric_limits<int64_t>().max();
	const int _INT64_BITS_COUNT = sizeof(int64_t) * 8;

	class big_integer_addition
	{
	public:
		big_integer_addition();
		~big_integer_addition();

		int64_t add(int64_t a, int64_t b) const;
	};
}