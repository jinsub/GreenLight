#include "pch.h"
#include "../GreenLight/MemoryDatabase.cpp"

using namespace std;

EmployeeInfo person01 = {
		2015123099,
		string("VXIHXOTH JHOP"), string("VXIHXOTH"), string("JHOP"),
		CareerLevel::CL3,
		string("3112 2609"), string("3112"), string("2609"),
		19771211, 1977, 12, 11,
		CertLevel::ADV
};
EmployeeInfo person02 = {
		2017112609,
		string("VXIHXOTH NTAWR"), string("VXIHXOTH"), string("NTAWR"),
		CareerLevel::CL4,
		string("5645 6122"), string("5645"), string("6122"),
		19861203, 1986, 12, 03,
		CertLevel::PRO
};
EmployeeInfo person03 = {
		1988114052,
		string("NQ LVARW"), string("NQ"), string("LVARW"),
		CareerLevel::CL4,
		string("4528 3059"), string("4528"), string("3059"),
		19911021, 1991, 10, 21,
		CertLevel::PRO
};
class DatabaseTest : public testing::Test
{
protected:
	void SetUp(void) override{

	}
	void TearDown(void) override {

	}	

	void Add(DataBaseMap& map, const EmployeeInfo person) {
		map.mainDB_.insert({ person.num_, person });
		map.fullName_Map_.insert({ person.fullName_, person.num_ });
		map.firstName_Map_.insert({person.firstName_, person.num_ });
		map.lastName_Map_.insert({ person.lastName_, person.num_ });
		map.fullPhone_Map_.insert({ person.fullPhoneNum_, person.num_ });
		map.midPhone_Map_.insert({ person.midPhoneNum_, person.num_ });
		map.lastPhone_Map_.insert({ person.lastPhoneNum_, person.num_ });
		map.birth_Map_.insert({ person.birth_, person.num_ });
		map.birthYear_Map_.insert({ person.birthYear_, person.num_ });
		map.birthMonth_Map_.insert({ person.birthMonth_, person.num_ });
		map.birthDay_Map_.insert({ person.birthDay_, person.num_ });
		map.career_Map_.insert({ person.cl_, person.num_ });
		map.cert_Map_.insert({ person.certi_, person.num_ });
	}
};

//=======================================================
TEST_F(DatabaseTest, test_create_01){	
}

//=======================================================
TEST_F(DatabaseTest, test_read_firstName){
	DataBaseMap map;
	
	Add(map, person01);
	Add(map, person02);
	Add(map, person03);

	MemoryDatabase db(map);

	vector<EmployeeInfo> result = db.ReadDB({ Column::FirstName, string("VXIHXOTH") });
	EXPECT_EQ(result.size(), 2);
}

//=======================================================
TEST_F(DatabaseTest, test_update_01){
	
}

//=======================================================
TEST_F(DatabaseTest, test_delete_01){
	
}
