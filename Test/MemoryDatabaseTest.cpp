#include "pch.h"
#include "../GreenLight/MemoryDatabase.cpp"

using namespace std;

class DatabaseTest : public testing::Test
{
protected:
	void SetUp(void) override{

	}
	void TearDown(void) override {

	}	

	void Add(DataBaseMap map, const EmployeeInfo person) {
		map.mainDB_.insert({ person.num, person });
		map.fullName_Map_.insert({ person.fullName, person.num });
		map.firstName_Map_.insert({person.firstName, person.num});
		map.lastName_Map_.insert({ person.lastName, person.num });
		map.fullPhone_Map_.insert({ person.fullPhoneNum, person.num });
		map.midPhone_Map_.insert({ person.midPhoneNum, person.num });
		map.lastPhone_Map_.insert({ person.lastPhoneNum, person.num });
		map.birth_Map_.insert({ person.birth, person.num });
		map.birthYear_Map_.insert({ person.birthYear, person.num });
		map.birthMonth_Map_.insert({ person.birthMonth, person.num });
		map.birthDay_Map_.insert({ person.birthDay, person.num });
		map.career_Map_.insert({ person.cl, person.num });
		map.cert_Map_.insert({ person.certi, person.num });
	}
};

//=======================================================
TEST_F(DatabaseTest, test_create_01)
{
	EXPECT_EQ(1, 1);
}

//=======================================================
TEST_F(DatabaseTest, test_read_01)
{
	DataBaseMap map;
	EmployeeInfo person01 = {
		2015123099,
		string("VXIHXOTH JHOP"), string("VXIHXOTH"), string("JHOP"),
		CareerLevel::CL3,
		string("3112 2609"), string("3112"),	string("2609"),
		19771211, 1977, 12, 11,
		CertLevel::ADV
	};
	Add(map, person01);

	MemoryDatabase db(map);

	enum class FilterOption {
		FirstName,
		LastName,
		MiddlePhoneNum,
		LastPhoneNum,
		BirthdayYear,
		BirthdayMonth,
		BirthdayDay,
		None
	};

	// vector<EmployeeInfo> result = db.ReadDB(FilterOption::FirstName, );
	
	

	


	MemoryDatabase db(map);

	EXPECT_EQ(1, 1);
}

//=======================================================
TEST_F(DatabaseTest, test_update_01)
{
	EXPECT_EQ(1, 1);
}

//=======================================================
TEST_F(DatabaseTest, test_delete_01)
{
	EXPECT_EQ(1, 1);
}
