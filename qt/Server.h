#ifndef HEADER_WebSocketServer
#define HEADER_WebSocketServer

#include <QtNetwork>
#include <QTextEdit>
#include <QMessageBox>

#include "QWsServer.h"
#include "QWsSocket.h"

class ServerExample : public QObject
{
	Q_OBJECT

public:
   ServerExample(QTextEdit *txtChat);
   ~ServerExample();
   QTextEdit *txtChat;
   void send(QString msg);

public slots:
	void onClientConnection();
	void onDataReceived(QString data);
	void onPong(quint64 elapsedTime);
	void onClientDisconnection();

private:
	QWsServer * server;
	QList<QWsSocket*> clients;
};

#endif
