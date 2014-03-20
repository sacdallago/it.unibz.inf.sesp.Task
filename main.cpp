#include <QApplication>
#include "html5applicationviewer.h"
#include "Task.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Task t;

    t.Name = "Some Task";

    Html5ApplicationViewer viewer;
    viewer.setOrientation(Html5ApplicationViewer::ScreenOrientationAuto);
    viewer.showExpanded();
    viewer.loadFile(QLatin1String("html/index.html"));

    return app.exec();
}
