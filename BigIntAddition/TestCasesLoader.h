#pragma once
#include <vector>
#include <string>

namespace BigIntAddition
{
	class test_cases_loader
	{
	public:
		test_cases_loader();
		~test_cases_loader();

		void load_test_cases(const std::string& testCasesFile);

		int64_t convert_stringvalue(std::string val);
	
		const std::vector<std::tuple<int64_t, int64_t, std::string>>& get_test_cases() const;

	private:
		std::vector<std::tuple<int64_t, int64_t, std::string>> testCases;
	};
}