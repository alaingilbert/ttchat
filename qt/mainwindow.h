#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include "Server.h"

class MainWindow : public QWidget
{
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    ServerExample * myServer;
};

#endif // MAINWINDOW_H
