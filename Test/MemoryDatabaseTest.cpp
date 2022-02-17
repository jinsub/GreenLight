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

TEST_F(DatabaseTest, test_update_Change_Num) {
	DataBaseMap map;
	MemoryDatabase db(map);
	vector<EmployeeInfo> result;
	db.CreateDB(person01);
	db.CreateDB(person02);
	db.CreateDB(person03);
	db.CreateDB(person04);

	TargetParam oldParam, newParam;

	oldParam.column = Column::EmployeeNum;
	oldParam.value = "2011263288";
	newParam.column = Column::EmployeeNum;
	newParam.value = "2011273288";
	result = db.UpdateDB(oldParam, newParam);

	EXPECT_EQ(result[0].num_, 2011263288);

}

//=======================================================
TEST_F(DatabaseTest, test_delete_num){
	MemoryDatabase db = SetUpForDeleteTest();
	vector<EmployeeInfo> result;
	result = db.DeleteDB({ Column::EmployeeNum, to_string(person01.num_) });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::EmployeeNum, to_string(person02.num_) });
	EXPECT_EQ(result.size(), 1);
	result = db.DeleteDB({ Column::EmployeeNum, to_string(person03.num_) });
	EXPECT_EQ(result.size(), 1);
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

//=======================================================
TEST_F(DatabaseTest, test_20input) {
	DataBaseMap map;
	MemoryDatabase db(map);
	vector<EmployeeInfo> result;
	TargetParam oldParam, newParam;

	//ADD, , , , 15123099, VXIHXOTH JHOP, CL3, 010 - 3112 - 2609, 19771211, ADV
	result = db.CreateDB({
			2015123099,
			string("VXIHXOTH"), string("JHOP"),
			string("CL3"),
			string("3112"), string("2609"),
			string("1977"), string("12"), string("11"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 17112609, FB NTAWR, CL4, 010 - 5645 - 6122, 19861203, PRO
	result = db.CreateDB({
			2017112609,
			string("FB"), string("NTAWR"),
			string("CL4"),
			string("5645"), string("6122"),
			string("1986"), string("12"), string("03"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 18115040, TTETHU HBO, CL3, 010 - 4581 - 2050, 20080718, ADV
	result = db.CreateDB({
			2018115040,
			string("TTETHU"), string("HBO"),
			string("CL3"),
			string("4581"), string("2050"),
			string("2008"), string("07"), string("18"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 88114052, NQ LVARW, CL4, 010 - 4528 - 3059, 19911021, PRO
	result = db.CreateDB({
			1988114052,
			string("NQ"), string("LVARW"),
			string("CL4"),
			string("4528"), string("3059"),
			string("1991"), string("10"), string("21"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 19129568, SRERLALH HMEF, CL2, 010 - 3091 - 9521, 19640910, PRO
	result = db.CreateDB({
			2019129568,
			string("SRERLALH"), string("HMEF"),
			string("CL2"),
			string("3091"), string("9521"),
			string("1964"), string("09"), string("10"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 17111236, VSID TVO, CL1, 010 - 3669 - 1077, 20120718, PRO
	result = db.CreateDB({
			2017111236,
			string("VSID"), string("TVO"),
			string("CL1"),
			string("3669"), string("1077"),
			string("2012"), string("07"), string("18"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 18117906, TWU QSOLT, CL4, 010 - 6672 - 7186, 20030413, PRO
	result = db.CreateDB({
			2018117906,
			string("TWU"), string("QSOLT"),
			string("CL4"),
			string("6672"), string("7186"),
			string("2003"), string("04"), string("13"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 08123556, WN XV, CL1, 010 - 7986 - 5047, 20100614, PRO
	result = db.CreateDB({
			2008123556,
			string("WN"), string("XV"),
			string("CL1"),
			string("7986"), string("5047"),
			string("2010"), string("06"), string("14"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 02117175, SBILHUT LDEXRI, CL4, 010 - 2814 - 1699, 19950704, ADV
	result = db.CreateDB({
			2002117175,
			string("SBILHUT"), string("LDEXRI"),
			string("CL4"),
			string("2814"), string("1699"),
			string("1995"), string("07"), string("04"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 03113260, HH LTUPF, CL2, 010 - 5798 - 5383, 19791018, PRO	
	result = db.CreateDB({
			2003113260,
			string("HH"), string("LTUPF"),
			string("CL2"),
			string("5798"), string("5383"),
			string("1979"), string("10"), string("18"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 14130827, RPO JK, CL4, 010 - 3231 - 1698, 20090201, ADV
	result = db.CreateDB({
			2014130827,
			string("RPO"), string("JK"),
			string("CL4"),
			string("3231"), string("1698"),
			string("2009"), string("02"), string("01"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 01122329, DN WD, CL4, 010 - 7174 - 5680, 20071117, PRO
	result = db.CreateDB({
			2001122329,
			string("DN"), string("WD"),
			string("CL4"),
			string("7174"), string("5680"),
			string("2007"), string("11"), string("17"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 08108827, RTAH VNUP, CL4, 010 - 9031 - 2726, 19780417, ADV
	result = db.CreateDB({
			2008108827,
			string("RTAH"), string("VNUP"),
			string("CL4"),
			string("9031"), string("2726"),
			string("1978"), string("04"), string("17"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 85125741, FBAH RTIJ, CL1, 010 - 8900 - 1478, 19780228, ADV	
	result = db.CreateDB({
			1985125741,
			string("FBAH"), string("RTIJ"),
			string("CL1"),
			string("8900"), string("1478"),
			string("1978"), string("02"), string("08"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 08117441, BMU MPOSXU, CL3, 010 - 2703 - 3153, 20010215, ADV
	result = db.CreateDB({
			2008117441,
			string("BMU"), string("MPOSXU"),
			string("CL3"),
			string("2703"), string("3153"),
			string("2001"), string("02"), string("15"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 10127115, KBU MHU, CL3, 010 - 3284 - 4054, 19660814, ADV	
	result = db.CreateDB({
			2010127115,
			string("KBU"), string("MHU"),
			string("CL3"),
			string("3284"), string("4054"),
			string("1966"), string("08"), string("14"),
			string("ADV")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 12117017, LFIS JJIVL, CL1, 010 - 7914 - 4067, 20120812, PRO
		result = db.CreateDB({
			2012117017,
			string("LFIS"), string("JJIVL"),
			string("CL1"),
			string("7914"), string("4067"),
			string("2012"), string("08"), string("12"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 11125777, TKOQKIS HC, CL1, 010 - 6734 - 2289, 19991001, PRO	
	result = db.CreateDB({
			2011125777,
			string("TKOQKIS"), string("HC"),
			string("CL1"),
			string("6734"), string("2289"),
			string("1999"), string("10"), string("01"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 11109136, QKAHCEX LTODDO, CL4, 010 - 2627 - 8566, 19640130, PRO
	result = db.CreateDB({
			2011109136,
			string("QKAHCEX"), string("LTODDO"),
			string("CL4"),
			string("2627"), string("8566"),
			string("1964"), string("01"), string("30"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//ADD, , , , 05101762, VCUHLE HMU, CL4, 010 - 3988 - 9289, 20030819, PRO
	result = db.CreateDB({
			2005101762,
			string("VCUHLE"), string("HMU"),
			string("CL4"),
			string("3988"), string("9289"),
			string("2003"), string("08"), string("19"),
			string("PRO")
		});
	EXPECT_EQ(result.size(), 1);

	//SCH,-p,-d, ,birthday,04
	//SCH,02117175,SBILHUT LDEXRI,CL4,010-2814-1699,19950704,ADV
	result = db.ReadDB({ Column::BirthdayDay, string("04") });
	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].GetFullBirthday(), string("19950704"));

	/*
	//MOD,-p, , ,name,FB NTAWR,birthday,20050520
	//MOD,17112609,FB NTAWR,CL4,010-5645-6122,19861203,PRO
	oldParam.column = Column::Name;
	oldParam.value = "FB NTAWR";
	newParam.column = Column::Birthday;
	newParam.value = "20050520";
	result = db.UpdateDB(oldParam, newParam);
	EXPECT_EQ(result.size(), 1);
	EXPECT_EQ(result[0].GetFullBirthday(), "19861203");
	*/

	//SCH, , , ,employeeNum,79110836
	//SCH,NONE
	result = db.ReadDB({ Column::EmployeeNum, string("1979110836") });
	EXPECT_EQ(result.size(), 0);

	//DEL, , , ,employeeNum,18115040
	//DEL, 1
	result = db.DeleteDB({ Column::EmployeeNum, string("2018115040") });
	EXPECT_EQ(result.size(), 1);
}