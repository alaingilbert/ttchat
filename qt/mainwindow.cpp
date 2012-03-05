#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
   setWindowFlags(Qt::WindowStaysOnTopHint);

   txtChat = new QTextEdit;
   txtMsg = new QLineEdit;
   connect(txtMsg, SIGNAL(returnPressed()), this, SLOT(returnPressed()));
   myServer = new ServerExample(txtChat);

   txtChat->setReadOnly(true);

   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(txtChat);
   layout->addWidget(txtMsg);

   setLayout(layout);

   txtMsg->setFocus();
}

void MainWindow::returnPressed() {
   txtMsg->clear();
}

MainWindow::~MainWindow() {
   delete myServer;
}
