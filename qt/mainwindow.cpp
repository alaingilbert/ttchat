#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
   setWindowFlags(Qt::WindowStaysOnTopHint);

   QTextEdit *txtChat = new QTextEdit;
   QLineEdit *txtMsg = new QLineEdit;
   myServer = new ServerExample(txtChat);

   txtChat->setReadOnly(true);

   QVBoxLayout *layout = new QVBoxLayout;
   layout->addWidget(txtChat);
   layout->addWidget(txtMsg);

   setLayout(layout);

   txtMsg->setFocus();
}

MainWindow::~MainWindow() {
   delete myServer;
}
