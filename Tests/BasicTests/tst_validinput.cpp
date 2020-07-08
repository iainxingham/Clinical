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
    void test_set_data();
    void test_rxr_valid();
    void test_nhs_valid();

private:
    DBObj *db;
};

ValidInput::ValidInput()
{
   // db = new DBObj();
}

ValidInput::~ValidInput()
{
    //delete db;
}

void ValidInput::initTestCase()
{
    db = new DBObj();
}

void ValidInput::cleanupTestCase()
{
    delete db;
}

void ValidInput::test_set_data()
{
    QTest::addColumn<QString>("Input - rxr");
    QTest::addColumn<QString>("Input - nhs");
    QTest::addColumn<bool>("Result");

    QTest::newRow("Leading whitespace") << "   RXR0000001" << "   111 222 3333" << true;
    QTest::newRow("Trailing whitespace") << "RXR0000001    " << "111 222 3333    " << true;
    QTest::newRow("Not digits") << "rxrabcdefg" << "aaa bbb cccc" << false;
    QTest::newRow("Too few digits") << "RXR123456" << "11 222 3333" << false;
    QTest::newRow("Weird whitespace") << " rxr1234567   " << "1112223333" << true;
    QTest::newRow("Incorrect characters") << "xrx1234567" << "a111 222 3333" << false;
}

void ValidInput::test_rxr_valid()
{
    QFETCH(QString, rxr);
    QFETCH(QString, nhs);
    QFETCH(bool, result);

    QCOMPARE(db->valid_rxr(rxr), result);
}

void ValidInput::test_nhs_valid()
{
    QFETCH(QString, rxr);
    QFETCH(QString, nhs);
    QFETCH(bool, result);

    QCOMPARE(db->valid_rxr(nhs), result);
}

QTEST_MAIN(ValidInput)

#include "tst_validinput.moc"
