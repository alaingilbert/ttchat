#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[]) {
   QApplication app(argc, argv);
   MainWindow w;
   w.show();
   //connect(txtMsg, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
   return app.exec();
}
