#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include "Server.h"

class MainWindow : public QWidget
{
   Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTextEdit *txtChat;
    QLineEdit *txtMsg;
private:
    ServerExample * myServer;
private slots:
    void returnPressed();
};

#endif // MAINWINDOW_H
