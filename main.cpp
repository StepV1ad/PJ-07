#include <gmock/gmock.h>

class DBConnection
{
public:
    DBConnection(){}
    virtual ~DBConnection(){}
    
    virtual void open() = 0;
    virtual void close() = 0;
    virtual void execQuery() = 0;

    virtual void checkBitRate(int bit, int rate) = 0;
};

void checkDBC1(DBConnection* dbc)
{
    dbc->open();
    dbc->execQuery();
    dbc->close();
}

void checkDBC2(DBConnection* dbc)
{
    dbc->open();
    dbc->checkBitRate(5, 25);
    dbc->checkBitRate(6, 36);
    dbc->checkBitRate(7, 47);
    dbc->checkBitRate(8, 58);
    dbc->close();
}

class ClassThatUseDB : public DBConnection {
public:
    MOCK_METHOD(void, open, (), (override));
    MOCK_METHOD(void, close, (), (override));
    MOCK_METHOD(void, execQuery, (), (override));
    MOCK_METHOD(void, checkBitRate, (int bit, int rate), (override));
};

TEST(DBCTest1, test1)
{
    ClassThatUseDB mdbc;
    
    EXPECT_CALL(mdbc, open).Times(::testing::AtLeast(1));
    EXPECT_CALL(mdbc, execQuery).Times(1);
    EXPECT_CALL(mdbc, close).Times(::testing::AtLeast(1));

    checkDBC1(&mdbc);
}

TEST(DBCTest2, test2)
{
    ClassThatUseDB mdbc;

    EXPECT_CALL(mdbc, open).Times(::testing::AtLeast(1));
    EXPECT_CALL(mdbc, execQuery).Times(1); // 0
    EXPECT_CALL(mdbc, checkBitRate).Times(5); // 4
    EXPECT_CALL(mdbc, close).Times(::testing::AtLeast(1));

    checkDBC2(&mdbc);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}