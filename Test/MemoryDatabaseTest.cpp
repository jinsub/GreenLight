#include "pch.h"
#include "../GreenLight/MemoryDatabase.cpp"

using namespace std;

EmployeeInfo person01 = {
		2015123099,
		string("VXIHXOTH"), string("JHOP"),
		"CL3",
		string("3112"), string("2609"),
		"1977", "12", "11",
		"ADV"
};
EmployeeInfo person02 = {
		2017112609,
		string("VXIHXOTH"), string("NTAWR"),
		"CL4",
		string("5645"), string("6122"),
		"1986", "12", "03",
		"PRO"
};
EmployeeInfo person03 = {
		1988114052,
		string("NQ"), string("LVARW"),
		"CL4",
		string("4528"), string("3059"),
		"1991", "10", "21",
		"PRO"
};
EmployeeInfo person04 = {
	2011263288,
	string("KYUNGSOO"), string("OH"),
	"CL3",
	 string("9263"), string("8644"),
	"1985", "03", "29",
	"PRO"
};

class DatabaseTest : public testing::Test
{
protected:
	void SetUp(void) override{

	}
	void TearDown(void) override {

	}

	MemoryDatabase SetUpForReadTest() {
		DataBaseMap map;

		Add(map, person01);
		Add(map, person02);
		Add(map, person03);

		MemoryDatabase db(map);
		return db;
	}
	MemoryDatabase SetUpForDeleteTest() {
		DataBaseMap map;

		Add(map, person01);
		Add(map, person02);
		Add(map, person03);

		MemoryDatabase db(map);
		return db;
	}

	void Add(DataBaseMap& map, const EmployeeInfo person) {
		map.mainDB_.insert({ person.num_, person });
		map.fullName_Map_.insert({ person.GetFullName(), person.num_});
		map.firstName_Map_.insert({person.firstName_, person.num_ });
		map.lastName_Map_.insert({ person.lastName_, person.num_ });
		map.fullPhone_Map_.insert({ person.GetFullPhoneNum(), person.num_});
		map.midPhone_Map_.insert({ person.midPhoneNum_, person.num_ });
		map.lastPhone_Map_.insert({ person.lastPhoneNum_, person.num_ });
		map.birth_Map_.insert({ person.GetFullBirthday(), person.num_});
		map.birthYear_Map_.insert({ person.birthYear_, person.num_ });
		map.birthMonth_Map_.insert({ person.birthMonth_, person.num_ });
		map.birthDay_Map_.insert({ person.birthDay_, person.num_ });
		map.career_Map_.insert({ person.cl_, person.num_ });
		map.cert_Map_.insert({ person.certi_, person.num_ });
	}
};

//=======================================================
TEST_F(DatabaseTest, test_create_01){
	DataBaseMap map;
	MemoryDatabase db(map);
	vector<EmployeeInfo> result;
	result = db.CreateDB(person01);
	EXPECT_EQ(result.size(), 1);
}

//=======================================================
TEST_F(DatabaseTest, test_read_num) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::EmployeeNum, to_string(person01.num_) });
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_num_invalid) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::EmployeeNum, to_string(0) });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_read_fullName) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::Name, person01.GetFullName()});
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_firstName){
	MemoryDatabase db = SetUpForReadTest(); 
	vector<EmployeeInfo> result = db.ReadDB({ Column::FirstName, person01.firstName_ });
	EXPECT_EQ(result.size(), 2);
}
TEST_F(DatabaseTest, test_read_lastName) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::LastName, person01.lastName_ });
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_birth) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::Birthday, person01.GetFullBirthday()});
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_birthYear) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::BirthdayYear, person01.birthYear_ });
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_birthMonth) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::BirthdayMonth, person01.birthMonth_ });
	EXPECT_EQ(result.size(), 2);
}
TEST_F(DatabaseTest, test_read_birthDay) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::BirthdayDay, person01.birthDay_});
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_phone) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::PhoneNumber, person01.GetFullPhoneNum()});
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_phoneMiddle) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::MiddlePhoneNum, person01.midPhoneNum_ });
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_phoneLast) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::LastPhoneNum, person01.lastPhoneNum_ });
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_certi) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::Certi, person01.certi_ });
	EXPECT_EQ(result.size(), 1);
}
TEST_F(DatabaseTest, test_read_career) {
	MemoryDatabase db = SetUpForReadTest();
	vector<EmployeeInfo> result = db.ReadDB({ Column::CareerLevel, person01.cl_ });
	EXPECT_EQ(result.size(), 1);
}

//=======================================================
TEST_F(DatabaseTest, test_update_Name){
	DataBaseMap map;
	MemoryDatabase db(map);
	vector<EmployeeInfo> result;
	db.CreateDB(person01);
	db.CreateDB(person02);
	db.CreateDB(person03);
	db.CreateDB(person04);

	TargetParam oldParam, newParam;
	oldParam.column = Column::Name;
	oldParam.value = "KYUNGSOO OH";
	newParam.column = Column::Name;
	newParam.value = "KYUNGJOO KIM";
	result = db.UpdateDB(oldParam, newParam);

	EXPECT_EQ(result[0].GetFullName(), "KYUNGSOO OH");
	
}
TEST_F(DatabaseTest, test_update_firstName) {
	DataBaseMap map;
	MemoryDatabase db(map);
	vector<EmployeeInfo> result;
	db.CreateDB(person01);
	db.CreateDB(person02);
	db.CreateDB(person03);
	db.CreateDB(person04);

	TargetParam oldParam, newParam;

	oldParam.column = Column::FirstName;
	oldParam.value = "KYUNGSOO";
	newParam.column = Column::LastName;
	newParam.value = "KIM";
	result = db.UpdateDB(oldParam, newParam);

	EXPECT_EQ(result[0].GetFullName(), "KYUNGSOO OH");

}

//=======================================================
TEST_F(DatabaseTest, test_delete_num){
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::EmployeeNum, to_string(person01.num_) });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::EmployeeNum, to_string(person01.num_) });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_num_invalid) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::EmployeeNum, to_string(0) });
	EXPECT_EQ(result.size(), 0);	
}
TEST_F(DatabaseTest, test_delete_fullName) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::Name, person01.GetFullName()});
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::Name, person01.GetFullName() });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_fullName_invalid) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::Name, string("invlaid")});
	EXPECT_EQ(result.size(), 0);	
}
TEST_F(DatabaseTest, test_delete_firstName) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::FirstName, person01.firstName_ });
	EXPECT_EQ(result.size(), 2);
	result = db.DeleteDB({ Column::FirstName, person01.firstName_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_lastName) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::LastName, person01.lastName_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::LastName, person01.lastName_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_birth) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::Birthday, person01.GetFullBirthday()});
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::Birthday, person01.GetFullBirthday()});
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_birthYear) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::BirthdayYear, person01.birthYear_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::BirthdayYear, person01.birthYear_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_birthMonth) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::BirthdayMonth, person01.birthMonth_ });
	EXPECT_EQ(result.size(), 2);
	result = db.DeleteDB({ Column::BirthdayMonth, person01.birthMonth_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_birthDay) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::BirthdayDay, person01.birthDay_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::BirthdayDay, person01.birthDay_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_phone) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::PhoneNumber, person01.GetFullPhoneNum()});
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::PhoneNumber, person01.GetFullPhoneNum()});
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_phoneMiddle) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::MiddlePhoneNum, person01.midPhoneNum_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::MiddlePhoneNum, person01.midPhoneNum_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_phoneLast) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::LastPhoneNum, person01.lastPhoneNum_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::LastPhoneNum, person01.lastPhoneNum_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_certi) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::Certi, person01.certi_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::Certi, person01.certi_ });
	EXPECT_EQ(result.size(), 0);
}
TEST_F(DatabaseTest, test_delete_career) {
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::CareerLevel, person01.cl_ });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::CareerLevel, person01.cl_ });
	EXPECT_EQ(result.size(), 0);
}