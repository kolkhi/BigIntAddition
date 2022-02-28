#include "BigIntAddition.h"	
#include "TestCasesLoader.h"

using namespace std;
using namespace BigIntAddition;

void run_test_cases(const test_cases_loader& loader)
{
	big_integer_addition big_int_adder;
	auto testCases = loader.get_test_cases();
	for each (auto & test in testCases)
	{
		auto [a, b, c] = test;

		try
		{
			auto res = big_int_adder.add(a, b);
			cout << res;
		}
		catch (const overflow_error& ex)
		{
			cout << string(ex.what());
		}
		catch (const underflow_error& ex)
		{
			cout << string(ex.what());
		}

		cout << endl << endl;
	}
}

int main(int argc, char** argv)
{
	auto testCasesFile = "test.txt";

	// if test file name if passed as an argument to the testing executable, use it
	if (argc == 2)
	{
		testCasesFile = argv[1];
	}

	test_cases_loader loader;
	try
	{
		loader.load_test_cases(testCasesFile);
		run_test_cases(loader);
	}
	catch (std::exception& ex)
	{
		cout << "Error loading test cases: " + string(ex.what());
	}
}