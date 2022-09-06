#include <gmock/gmock.h>
#include <gtest/gtest.h>

class DBConnection
{
public:
    virtual ~DBConnection() = default;
    virtual void open() = 0;
    virtual void execQuery() = 0;
    virtual void close() = 0;
};

class MockDBConnection : public DBConnection
{
public:
    MOCK_METHOD0(open, void());
    MOCK_METHOD0(execQuery, void());
    MOCK_METHOD0(close, void());
};

class ClassThatUseDb
{
    DBConnection* _dataBase;
public:
    explicit ClassThatUseDb(DBConnection* dataBase) : _dataBase(dataBase) {};

    const char* openConnection(const char* cmdOpen)
    {
        if (cmdOpen == "open")
        {
            _dataBase->open();
            return "start";
        }
        else
            return "error";
    };

    int useConnection(int one, int two)
    {
        if (two == one * one)
        {
            _dataBase->execQuery();
            return two * one;
        }
        else
            return -1;
    };

    bool closeConnection(const char* cmdOpen)
    {
        if (cmdOpen == "close")
        {
            _dataBase->close();
            return true;
        }
        else
            false;
    };
};

TEST(DBCTest1, test1)
{
    MockDBConnection dbcTest1_mock;
    ClassThatUseDb dbcTest1(&dbcTest1_mock);
    
    EXPECT_CALL(dbcTest1_mock, open()).Times(1);
    EXPECT_EQ(dbcTest1.openConnection("open"), "start");
    EXPECT_EQ(dbcTest1.openConnection("opn"), "error");
}

TEST(DBCTest2, test2)
{
    MockDBConnection dbcTest2_mock;
    ClassThatUseDb dbcTest2(&dbcTest2_mock);
    
    EXPECT_CALL(dbcTest2_mock, execQuery()).Times(1);
    EXPECT_EQ(dbcTest2.useConnection(2, 4), 8);
    EXPECT_EQ(dbcTest2.useConnection(3, 10), -1);
}

TEST(DBCTest3, test3)
{
    MockDBConnection dbcTest3_mock;
    ClassThatUseDb dbcTest3(&dbcTest3_mock);
    
    EXPECT_CALL(dbcTest3_mock, close()).Times(1);
    EXPECT_EQ(dbcTest3.closeConnection("close"), true);
    EXPECT_EQ(dbcTest3.closeConnection("clse"), false);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}