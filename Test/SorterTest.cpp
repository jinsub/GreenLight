#include "pch.h"
#include "gmock/gmock.h"
#include "../GreenLight/AscendingEmployeeNumber.cpp"
#include <vector>

class SorterTest : public ::testing::Test {
protected:
	void SetUp(void) override
	{
		employee_1 = {
			19018054,
			string("CHANGHYUN"), string("HYUN"),
			string("CL2"),
			string("6606"), string("4404"),
			string("1995"), string("02"), string("14"),
			string("PRO")
		};

		employee_2 = {
			17018052,
			string("HYELIN"), string("JANG"),
			string("CL2"),
			string("4932"), string("1423"),
			string("1991"), string("05"), string("14"),
			string("PRO")
		};

		employee_3 = {
			12043212,
			string("GILDONG"), string("HONG"),
			string("CL4"),
			string("3214"), string("5677"),
			string("1985"), string("12"), string("14"),
			string("PRO")
		};
	}

	void TearDown(void) override
	{

	}

	AscendingEmployeeNumber sort_;
	EmployeeInfo employee_1;
	EmployeeInfo employee_2;
	EmployeeInfo employee_3;
};

TEST_F(SorterTest, AscendingEmployeeNumberTest)
{
	vector<EmployeeInfo> input;
	input.push_back(employee_2);
	input.push_back(employee_1);
	input.push_back(employee_3);

	vector<EmployeeInfo> result = sort_.Sort(input);

	EXPECT_EQ(employee_3, result[0]);
	EXPECT_EQ(employee_2, result[1]);
	EXPECT_EQ(employee_1, result[2]);
}