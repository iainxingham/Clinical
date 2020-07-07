#include <QtTest>
#include <QCoreApplication>

// Need to add sql to BasicTests.pro
#include "../../LungTrak/dbobj.h"

class ValidInput : public QObject
{
    Q_OBJECT

public:
    ValidInput();
    ~ValidInput();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

    // Test valid_rxr() and valid_nhs()
    void test_rxr_data();

private:
    DBObj *db;
};

ValidInput::ValidInput()
{
    db = new DBObj();
}

ValidInput::~ValidInput()
{
    delete db;
}

void ValidInput::initTestCase()
{

}

void ValidInput::cleanupTestCase()
{

}

void ValidInput::test_case1()
{

}

void ValidInput::test_rxr_data()
{

}

QTEST_MAIN(ValidInput)

//#include "tst_validinput.moc"
