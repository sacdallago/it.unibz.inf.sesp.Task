#include "task.h"
#include <QString>
#include <ctime>

QString printTask(Task a){
    QString result = "";
    result += "Task ID: " + QString::number(a.id) + "\n";
    result += "Task Name: " + a.name + "\n";
    result += "Task Description: " + a.description + "\n";
    result += "Task Importance: " + QString::number(a.importance) + "\n";
    result += "Task Duration (h): " + QString::number(a.durationInH) + "\n";
    result += "Child(1) or Root(0): " + QString::number(a.relatives) + "\n";
    result += "Done(-1), todo(0) or active(1): " + QString::number(a.status) + "\n";
    result += "Creation on: " + a.time + "\n";
    return result;
}

QString getTime(){
    char out[15];
    std::time_t t=std::time(NULL);
    std::strftime(out, sizeof(out), "%Y%m%d%H%M%S", std::localtime(&t));
    QString str(out);
    return str;
}
