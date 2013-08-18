#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("pworwag");
    QCoreApplication::setOrganizationDomain("pworwag.com.pl");
    QCoreApplication::setApplicationName("metryki");
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    
    return a.exec();
}
