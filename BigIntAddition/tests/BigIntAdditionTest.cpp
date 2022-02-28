#include "..\BigIntAddition.h"
#include "..\TestCasesLoader.h"

#define BOOST_TEST_MODULE BigIntAddition
#include <boost/test/included/unit_test.hpp>

using namespace std;
using namespace BigIntAddition;

struct test_cases_fixture
{
	test_cases_loader loader;

	test_cases_fixture()
	{
		auto testCasesFile = "test.txt";

		// if test file name if passed as an argument to the testing executable, use it
		if (boost::unit_test::framework::master_test_suite().argc == 2)
		{
			testCasesFile = boost::unit_test::framework::master_test_suite().argv[1];
		}

		try
		{
			loader.load_test_cases(testCasesFile);
		}
		catch (std::exception& ex)
		{
			BOOST_ERROR("Error loading test cases: " + string(ex.what()));
		}
	}

	~test_cases_fixture()
	{
	}

	bool is_valid()
	{
		return loader.get_test_cases().size() > 0;
	}
};

BOOST_AUTO_TEST_SUITE(big_integer_addition_test)

BOOST_FIXTURE_TEST_CASE(test_cases, test_cases_fixture)
{
	BOOST_REQUIRE(is_valid());
	big_integer_addition big_int_adder;
	auto testCases = loader.get_test_cases();
	for each (auto& test in testCases)
	{
		auto [a, b, c] = test;
		if (c.compare("Overflow") == 0)
		{
			BOOST_CHECK_THROW(big_int_adder.add(a, b), std::overflow_error);
		}
		else if (c.compare("Underflow") == 0)
		{
			BOOST_CHECK_THROW(big_int_adder.add(a, b), std::underflow_error);
		}
		else
		{
			auto c_int64 = loader.convert_stringvalue(c);
			BOOST_REQUIRE(big_int_adder.add(a, b) == c_int64);
		}
	}
}

BOOST_AUTO_TEST_CASE(add_positive_numbers_test)
{
	big_integer_addition big_int_adder;

	BOOST_REQUIRE(big_int_adder.add(0, 0) == 0);

	BOOST_REQUIRE(big_int_adder.add(0, 123) == 123);

	BOOST_REQUIRE(big_int_adder.add(456, 0) == 456);

	BOOST_REQUIRE(big_int_adder.add(900'000, 200) == 900'200);

	BOOST_REQUIRE(big_int_adder.add(1, _MAX_INT64 - 1) == _MAX_INT64);
}

BOOST_AUTO_TEST_CASE(add_negative_numbers_test)
{
	big_integer_addition big_int_adder;

	BOOST_REQUIRE(big_int_adder.add(0, -123) == -123);

	BOOST_REQUIRE(big_int_adder.add(-456, 0) == -456);

	BOOST_REQUIRE(big_int_adder.add(-800'000, -300) == -800'300);

	BOOST_REQUIRE(big_int_adder.add(-1, _MIN_INT64 + 1) == _MIN_INT64);
}

BOOST_AUTO_TEST_CASE(add_positive_and_negative_numbers_test)
{
	big_integer_addition big_int_adder;

	BOOST_REQUIRE(big_int_adder.add(-1, 1) == 0);

	BOOST_REQUIRE(big_int_adder.add(-123, 123) == 0);

	BOOST_REQUIRE(big_int_adder.add(-50, 40) == -10);

	BOOST_REQUIRE(big_int_adder.add(100, -60) == 40);

	BOOST_REQUIRE(big_int_adder.add(900'000, -1'000'000) == -100'000);

	BOOST_REQUIRE(big_int_adder.add(_MAX_INT64, _MIN_INT64) == -1);
}

BOOST_AUTO_TEST_CASE(check_underflow_throws_test)
{
	big_integer_addition big_int_adder;

	BOOST_CHECK_THROW(big_int_adder.add(-1, _MIN_INT64), std::underflow_error);

	BOOST_CHECK_THROW(big_int_adder.add(_MIN_INT64, _MIN_INT64), std::underflow_error);
}

BOOST_AUTO_TEST_CASE(check_overflow_throws_test)
{
	big_integer_addition big_int_adder;

	BOOST_CHECK_THROW(big_int_adder.add(1, _MAX_INT64), std::overflow_error);

	BOOST_CHECK_THROW(big_int_adder.add(_MAX_INT64, _MAX_INT64), std::overflow_error);
}

BOOST_AUTO_TEST_SUITE_END()