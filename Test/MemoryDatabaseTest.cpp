#include "pch.h"
#include "../GreenLight/MemoryDatabase.cpp"

class DatabaseTest : public testing::Test
{
protected:
	void SetUp(void) override
	{

	}
	void TearDown(void) override
	{

	}
	MemoryDatabase db_;
};

//=======================================================
TEST_F(DatabaseTest, test_create_01)
{
	EXPECT_EQ(1, 1);
}

//=======================================================
TEST_F(DatabaseTest, test_read_01)
{
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
