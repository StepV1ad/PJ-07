#include <gmock/gmock.h>

class DBConnection
{
public:
    virtual ~DBConnection() = default;
    virtual std::string open() = 0;
    virtual bool execQuery(int one, int two) = 0;
    virtual const char* close() = 0;
};

class MockDBConnection : public DBConnection
{
public:
    MOCK_METHOD(std::string, open, (), (override));
    MOCK_METHOD(bool, execQuery, (int one, int two), (override));
    MOCK_METHOD(const char*, close, (), (override));
};

class ClassThatUseDb : public DBConnection 
{
    DBConnection* _dataBase;
public:
    explicit ClassThatUseDb(DBConnection* dataBase) : _dataBase(dataBase) {};
    virtual std::string open() override { return "open"; }
    virtual bool execQuery(int one, int two) override { return (two == one * one * one); }
    virtual const char* close() override { return "close"; }
};

TEST(DBCTest1, test1)
{
    MockDBConnection dbcTest1_mock;
    ClassThatUseDb dbcTest1(&dbcTest1_mock);
    EXPECT_EQ(dbcTest1.open(), "open");
    EXPECT_EQ(dbcTest1.open(), "opn");
}

TEST(DBCTest2, test2)
{
    MockDBConnection dbcTest2_mock;
    ClassThatUseDb dbcTest2(&dbcTest2_mock);
    EXPECT_EQ(dbcTest2.execQuery(2, 8), true);
    EXPECT_EQ(dbcTest2.execQuery(3, 30), true);
}

TEST(DBCTest3, test3)
{
    MockDBConnection dbcTest3_mock;
    ClassThatUseDb dbcTest3(&dbcTest3_mock);
    EXPECT_STREQ(dbcTest3.close(), "close");
    EXPECT_STREQ(dbcTest3.close(), "clse");
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}