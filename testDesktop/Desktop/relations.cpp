#include "relations.h"
#include "ui_relations.h"

Relations::Relations(QWidget *parent, Collection* coll) :
    QDialog(parent),
    ui(new Ui::Relations)
{
    ui->setupUi(this);
    this->coll = coll;

    //Let's fill the "depends on" combobox

    toDoList = this->coll->getTodoList();

        //first let's insert an empty string in the comboboxes
    ui->comboBox->addItem("");
    ui->comboBox_2->addItem("");
    ui->comboBox_3->addItem("");
    ui->comboBox_4->addItem("");
    ui->comboBox_5->addItem("");
    ui->comboBox_6->addItem("");

        //now let's fill up the comboboxes
    for (Task* t : toDoList){

        ui->comboBox->addItem(t->getName());
        ui->comboBox_2->addItem(t->getName());
        ui->comboBox_3->addItem(t->getName());
        ui->comboBox_4->addItem(t->getName());
        ui->comboBox_5->addItem(t->getName());
        ui->comboBox_6->addItem(t->getName());
    }
}

Relations::~Relations()
{
    delete ui;
}

void Relations::on_pushButton_3_clicked()//CANCEL
{
this->close();
}

void Relations::on_pushButton_2_clicked()//OK
{
    //Creation of a list where the selected predecessors will be stored
    QList<Task*> f = QList<Task*>();

    //We get all the selected tasks and add each one of them to the list
    Task* t = toDoList.at(ui->comboBox->currentIndex()-1);
    if(ui->comboBox_2->currentIndex()!=0){
    Task* t2 = toDoList.at(ui->comboBox_2->currentIndex()-1);f<<t2;}
    if(ui->comboBox_3->currentIndex()!=0){
    Task* t3= toDoList.at(ui->comboBox_3->currentIndex()-1);f<<t3;}
    if(ui->comboBox_4->currentIndex()!=0){
    Task* t4 = toDoList.at(ui->comboBox_4->currentIndex()-1);f<<t4;}
    if(ui->comboBox_5->currentIndex()!=0){
    Task* t5 = toDoList.at(ui->comboBox_5->currentIndex()-1);f<<t5;}
    if(ui->comboBox_6->currentIndex()!=0){
    Task* t6 = toDoList.at(ui->comboBox_6->currentIndex()-1);f<<t6;}


    //This loop checks that there are no doubles in the selected tasks
    int counter = 0;
    foreach(Task *a, f){
        foreach(Task *b, f){
            if(a->getId()==b->getId()){
                counter++;
            }
        }
    }
    //Se va tutto bene
    if (counter==f.size()){
         foreach(Task *o, f){
            if(coll->relate(o,t,true)){
                cout<<"NEW RELATION_";
                cout<<o->getId();

            }else{
                QMessageBox msg;
                msg.setText("The relation cannot be added because causes a loop.");
                msg.exec();

            }
        }
         QMessageBox msg;
         msg.setText("Relation updated!");
         msg.exec();
         this->close();
    } else {
        QMessageBox msg;
        msg.setText("ERROR - Two of the tasks selected are the same. Please change them");
        msg.exec();}

}
