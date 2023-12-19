#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <boost/asio.hpp>

#include "Common.hpp"
#include "json.hpp"

class TcpClient : QObject
{
  Q_OBJECT
  
private:
  std::string buffer;
  boost::asio::io_service ioService;
  boost::asio::ip::tcp::socket socket;

  void StartRead();

public:
  TcpClient(QObject *parent = nullptr) : QObject(parent), socket(ioService) {};

public slots:
  void ConnectToServer(const std::string &adress);
  void SendData(const std::string& strUserId, const std::string& strRequestType, const std::string& strMessage);

signals:
  void Connected();
  void DataRecieved();
  void DataSent();
};
#endif //TCPCLIENT_H