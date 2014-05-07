#ifndef COLLECTIONTEST_H
#define COLLECTIONTEST_H

#include <QObject>
#include <tests/AutoTest.h>
#include "collection.h"

class CollectionTest : public QObject
{
    Q_OBJECT
public:
    explicit CollectionTest(QObject *parent = 0);

private:
    Collection *col;
    TaskDatabase *db;
    Task *local, *permanent;
signals:

public slots:

private slots:
    void testNullConstructor();

    void testCreateUser();
    void testLogin();
    void testCreateTaskLocally();
    void testCreateTaskPermanently();
    void testDeleteUser();
    void testDestruction();
    void clean();

};

DECLARE_TEST(CollectionTest)

#endif // COLLECTIONTEST_H
