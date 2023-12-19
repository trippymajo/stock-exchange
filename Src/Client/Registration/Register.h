#ifndef REGISTER_H
#define REFISTER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
QT_END_NAMESPACE

class RegisterWidget : public QWidget
{
  Q_OBJECT

public:
  RegisterWidget(QWidget *parent = 0);
  ~RegisterWidget(){};
};

#endif //REGISTER_H