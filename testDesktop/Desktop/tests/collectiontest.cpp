#include "collectiontest.h"

CollectionTest::CollectionTest(QObject *parent) :
    QObject(parent)
{
}


void CollectionTest::testNullConstructor(){
    QVERIFY(col = new Collection(NULL));
}

void CollectionTest::testCreateUser(){
    delete col;
    db = new TaskDatabase();
    col = new Collection(db);
    QVERIFY(db->createUser("qtestuser","password"));
}

void CollectionTest::testDeleteUser(){
    QVERIFY(db->deleteUser("qtestuser"));
}

void CollectionTest::testLogin(){
    QVERIFY(db->login("qtestuser","password"));
    QVERIFY(col->login("qtestuser","password"));
}

void CollectionTest::testCreateTaskLocally(){
    local = new Task(0,0,0,"local","local",0);
    col->addItem(local);
    if(col->get(0) == local && db->getTask(0) == NULL){
        QVERIFY(true);
    } else {
        QVERIFY(false);
    }
}

void CollectionTest::testCreateTaskPermanently(){
    permanent = col->addItem("remote",0,0,"remote",0);
    if(col->get(permanent->getId()) == permanent && db->getTask(permanent->getId()) != NULL){
        QVERIFY(true);
    } else {
        QVERIFY(false);
    }
}

void CollectionTest::testDestruction(){
    try{
        delete col;
        QVERIFY(true);
    } catch (...){
        QVERIFY(false);
    }
}

void CollectionTest::clean(){
    delete local, permanent;
}
