/*
 * Doesn't build properly with IDE
 *
 * Run
 *      qmake
 *      make
 *      ./BasicTests
 * from command line
 *
 */

#include <QtTest>
#include <QCoreApplication>

#define TESTING

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
    void test_validate_rxr_data();
    void test_validate_rxr();
    void test_validate_nhs_data();
    void test_validate_nhs();
    void test_clean_nhs_data();
    void test_clean_nhs();

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

void ValidInput::test_validate_rxr_data()
{
    QTest::addColumn<QString>("rxr");
    QTest::addColumn<bool>("result");

    QTest::newRow("Leading whitespace") << "   RXR0000001"  << true;
    QTest::newRow("Trailing whitespace") << "RXR0000001    "  << true;
    QTest::newRow("Not digits") << "rxrabcdefg" << false;
    QTest::newRow("Too few digits") << "RXR123456"  << false;
    QTest::newRow("Lower case") << "rxr1234567" << true;
    QTest::newRow("Incorrect characters") << "xrx1234567" << false;
}

void ValidInput::test_validate_rxr()
{
    QFETCH(QString, rxr);
    QFETCH(bool, result);

    QCOMPARE(db->valid_rxr(rxr), result);
}

void ValidInput::test_validate_nhs_data()
{
    QTest::addColumn<QString>("nhs");
    QTest::addColumn<bool>("result");

    QTest::newRow("Leading whitespace") << "   111 222 3333" << true;
    QTest::newRow("Trailing whitespace") << "111 222 3333    " << true;
    QTest::newRow("Not digits") << "aaa bbb cccc" << false;
    QTest::newRow("Too few digits") << "11 222 3333" << false;
    QTest::newRow("Weird whitespace") << "1112223333" << true;
    QTest::newRow("Incorrect characters") << "a111 222 3333" << false;
}

void ValidInput::test_validate_nhs()
{
    QFETCH(QString, nhs);
    QFETCH(bool, result);

    QCOMPARE(db->valid_nhs(nhs), result);
}

void ValidInput::test_clean_nhs_data()
{
    QTest::addColumn<QString>("dirty");
    QTest::addColumn<QString>("clean");

    QTest::newRow("No spaces") << "1112223333" << "111 222 3333";
    QTest::newRow("Invalid nhs") << "x11 222 3333" << "NULL";
}

void ValidInput::test_clean_nhs()
{
    QFETCH(QString, dirty);
    QFETCH(QString, clean);

    QCOMPARE(db->clean_nhs(dirty), clean);
}

QTEST_MAIN(ValidInput)

#include "tst_validinput.moc"
