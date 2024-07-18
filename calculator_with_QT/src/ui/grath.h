#ifndef GRATH_H
#define GRATH_H

#include "ui_grath.h"
namespace Ui {
class Grath;
}

class MainWindow;

class Grath : public QDialog {
  Q_OBJECT

 public:
  explicit Grath(QWidget *parent = nullptr);
  ~Grath();

 signals:
  void getY(double X, int grath);

 public slots:
  void takeY(double Y);

 private slots:
  void grath();

 private:
  QPushButton *button = NULL;
  Ui::Grath *ui;
  MainWindow *window;
  Grath *windowGrath;
  QVector<double> x, y;
  double resultY = 0;
};

#endif  // GRATH_H
