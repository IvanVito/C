#ifndef MAINWINDOW_H
#define MAINWINDOW_H

extern "C" {
#include "../s21_smart_calc.h"
}

#include <QDate>
#include <QDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QPointer>
#include <QString>
#include <QTabWidget>
#include <QVector>
#include <QtCore>
#include <QtGlobal>
#include <QtMath>

#include "grath.h"
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void giveY(double X);

 public slots:
  void xButton(double X, int grath);

 private slots:
  void textButton();
  void specificButton();
  void qSmartCalc();
  void showGrath();
  void creditCalcule();
  void createRow(int ind, QString str1, QString str2);
  void massForC(QString str, char *input);
  int findError(QString n, QString s, QString i);

 private:
  Ui::MainWindow *ui;
  Grath *windowGrath;
  QPushButton *button = NULL;
  int calcule = 0;
  int error(char *input, long double *answer);
  void printError();
};
#endif  // MAINWINDOW_H
