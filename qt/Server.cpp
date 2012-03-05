#include "Server.h"

ServerExample::ServerExample(QTextEdit *txtChat)
{
   this->txtChat = txtChat;
	int port = 1337;
    server = new QWsServer(this);
    if ( ! server->listen(QHostAddress::Any, port) ) {
      this->txtChat->append("Error: Can't launch server");
      QMessageBox::critical(0, "QWsServer error", server->errorString());
    } else {
      //this->txtChat->append("Server is listening port " + QString::number(port))
	}
	connect(server, SIGNAL(newConnection()), this, SLOT(onClientConnection()));
}

ServerExample::~ServerExample() {
}

void ServerExample::onClientConnection() {
	QWsSocket * clientSocket = server->nextPendingConnection();

	QObject * clientObject = qobject_cast<QObject*>(clientSocket);

	connect(clientObject, SIGNAL(frameReceived(QString)), this, SLOT(onDataReceived(QString)));
	connect(clientObject, SIGNAL(disconnected()), this, SLOT(onClientDisconnection()));
	connect(clientObject, SIGNAL(pong(quint64)), this, SLOT(onPong(quint64)));

	clients << clientSocket;
}

void ServerExample::onDataReceived(QString data) {
	QWsSocket * socket = qobject_cast<QWsSocket*>( sender() );
	if (socket == 0)
		return;

   this->txtChat->append(data);
	
	QWsSocket * client;
    foreach ( client, clients ) {
		client->write( data );
	}
}

void ServerExample::onPong(quint64 elapsedTime) {
}

void ServerExample::onClientDisconnection() {
	QWsSocket * socket = qobject_cast<QWsSocket*>(sender());
	if (socket == 0)
		return;

	clients.removeOne(socket);

	socket->deleteLater();
}
