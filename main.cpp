#include <gmock/gmock.h>

class DBConnection
{
public:
    virtual ~DBConnection() = default;
    virtual std::string open() = 0;
    virtual bool execQuery(int one, int two) = 0;
    virtual const char* close() = 0;
};

class MockClassThatUseDB : public DBConnection 
{
public:
    MOCK_METHOD(std::string, open, (), (override));
    MOCK_METHOD(bool, execQuery, (int one, int two), (override));
    MOCK_METHOD(const char*, close, (), (override));
};

class ClassThatUseDb : public DBConnection 
{
public:
    virtual std::string open() override final { return "open"; }
    virtual bool execQuery(int one, int two) override final { return (two == one * one * one); }
    virtual const char* close() override final { return "close"; }
};

TEST(DBCTest1, test1)
{
    ClassThatUseDb dbcTest1;
    EXPECT_EQ(dbcTest1.open(), "open");
    EXPECT_EQ(dbcTest1.open(), "opn");
}

TEST(DBCTest2, test2)
{
    ClassThatUseDb dbcTest2;
    EXPECT_EQ(dbcTest2.execQuery(2, 8), true);
    EXPECT_EQ(dbcTest2.execQuery(3, 30), true);
}

TEST(DBCTest3, test3)
{
    ClassThatUseDb dbcTest3;
    EXPECT_STREQ(dbcTest3.close(), "close");
    EXPECT_STREQ(dbcTest3.close(), "clse");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}