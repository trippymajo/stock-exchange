#include <QApplication>

#include "TcpClient.h"
#include "Register.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  RegisterWidget regWidget;
  regWidget.show();
  return app.exec();
}