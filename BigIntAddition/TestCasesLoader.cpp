#include "BigIntAddition.h"
#include "TestCasesLoader.h"
#include <sstream>
#include <fstream>

using namespace std;
using namespace BigIntAddition;

test_cases_loader::test_cases_loader()
{
}

test_cases_loader::~test_cases_loader()
{
}

void test_cases_loader::load_test_cases(const string& testCasesFile)
{
	ifstream testFileStream(testCasesFile, std::ios::in);
	if (!testFileStream.is_open())
	{
		throw runtime_error("Can't open test cases file " + testCasesFile);
	}

	while (testFileStream)
	{
		string testCaseLine;
		getline(testFileStream, testCaseLine);

		stringstream tempString(testCaseLine);
		string a, b, c;
		tempString >> a >> b >> c;

		if (a.length() == 0 || b.length() == 0 || c.length() == 0)
			continue;

		auto a_int64 = convert_stringvalue(a);
		auto b_int64 = convert_stringvalue(b);

		auto vec = tuple<int64_t, int64_t, string>{ a_int64, b_int64, c };
		testCases.push_back(vec);
	}

	testFileStream.close();
}

int64_t test_cases_loader::convert_stringvalue(string val)
{
	if (val.compare("Max") == 0) return _MAX_INT64;
	if (val.compare("Min") == 0) return _MIN_INT64;

	return stoll(val);
}

const vector<tuple<int64_t, int64_t, string>>& test_cases_loader::get_test_cases() const
{
	return testCases;
}