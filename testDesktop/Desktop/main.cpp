#include "widget.h"
#include "task.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
