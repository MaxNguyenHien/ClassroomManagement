#include "mainwindow.h"
#include "loginform.h"
#include "registerform.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginForm lf;
    //MainWindow m;
    lf.show();

    return a.exec();
}
