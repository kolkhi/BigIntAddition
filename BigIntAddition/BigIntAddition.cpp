#include "BigIntAddition.h"
	
using namespace std;
using namespace BigIntAddition;

big_integer_addition::big_integer_addition()
{
}

big_integer_addition::~big_integer_addition()
{
}

int64_t big_integer_addition::add(int64_t a, int64_t b) const
{
	auto bothPositive = (a > 0) && (b > 0);
	auto bothNegative = (a < 0) && (b < 0);

	int64_t calculated_result = 0;
	int64_t carry_bit = 0;
	for (auto i = 0; i < _INT64_BITS_COUNT; i++)
	{
		// shift to the right by i postiions to get the next bits to add
		auto last_bit_a = (a >> i) & 1;
		auto last_bit_b = (b >> i) & 1;

		// get result of the 2 bits addition
		auto xor_res = last_bit_a ^ last_bit_b;

		// detect carry on bit from the bits to add, or from the carry on bit from the previous step
		auto local_carry_bit = (last_bit_a & last_bit_b) | (xor_res & carry_bit);

		// add carry on bit from the previous step to the result
		xor_res ^= carry_bit;

		// save carry on bit of this step
		carry_bit = local_carry_bit;

		// shift result bit back to the original position
		auto shifted_xor_res = xor_res << i;

		// add result bit of the current step to the result sum
		calculated_result |= shifted_xor_res;
	}

	// if both values to add are positive, but the result is negative or 0, there is an overflow
	if (bothPositive && calculated_result <= 0)
		throw overflow_error("Overflow");

	// if both values to add are negative, but the result is positive or 0, there is an underflow
	if (bothNegative && calculated_result >= 0)
		throw underflow_error("Underflow");

	return calculated_result;
}
