#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  windowGrath = new Grath(this);
  windowGrath->setWindowTitle("Graphic");
  ui->setupUi(this);
  ui->MainWindow_2->setCurrentWidget(ui->Calculate);
  ui->screen->setFocus();
  connect(ui->creditCalcule, SIGNAL(clicked()), this, SLOT(creditCalcule()));
  connect(ui->num_one, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_two, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_three, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_four, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_five, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_six, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_seven, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_eight, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_nine, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->num_null, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->point, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->sin, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->cos, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->tan, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->asin, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->acos, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->atan, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->ln, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->log, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->sqrt, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->degree, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->lbreacket, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->rbreacket, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->xx, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->plus, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->minus, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->mod, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->mult, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->divider, SIGNAL(clicked()), this, SLOT(textButton()));
  connect(ui->pi, SIGNAL(clicked()), this, SLOT(specificButton()));
  connect(ui->pi2, SIGNAL(clicked()), this, SLOT(specificButton()));
  connect(ui->ee, SIGNAL(clicked()), this, SLOT(specificButton()));
  connect(ui->cc, SIGNAL(clicked()), this, SLOT(specificButton()));
  connect(ui->ac, SIGNAL(clicked()), this, SLOT(specificButton()));
  connect(ui->equal, SIGNAL(clicked()), this, SLOT(qSmartCalc()));
  connect(ui->grath, SIGNAL(clicked()), this, SLOT(showGrath()));
  QObject::connect(windowGrath, SIGNAL(getY(double, int)), this,
                   SLOT(xButton(double, int)));
  QObject::connect(this, SIGNAL(giveY(double)), windowGrath,
                   SLOT(takeY(double)));
}

MainWindow::~MainWindow() {
  delete ui;
  delete windowGrath;
}

void MainWindow::textButton() {
  button = (QPushButton*)sender();
  QPointer<QLineEdit> activeLineEdit =
      qobject_cast<QLineEdit*>(QApplication::focusWidget());
  QString newScreen = activeLineEdit->text(), arithm = "* / ^ + - mod",
          function = "cos sin tan acos asin atan sqrt ln log";
  if (newScreen == "ERROR") activeLineEdit->setText("");
  if ((newScreen == "0" || newScreen == "") && button->text() == ".")
    newScreen = "0.";
  if (newScreen != "0" && calcule == 1 && arithm.indexOf(button->text()) == -1)
    if (function.indexOf(button->text()) == -1)
      newScreen = button->text();
    else
      newScreen = button->text() + "(";
  else if (function.indexOf(button->text()) != -1)
    if (activeLineEdit->text() != "0" && activeLineEdit->text() != "." &&
        activeLineEdit->text().indexOf("=") == -1)
      newScreen = activeLineEdit->text() + button->text() + '(';
    else
      newScreen = button->text() + '(';
  else if (newScreen != "0" && activeLineEdit->text().indexOf("=") == -1)
    newScreen = (activeLineEdit->text() + button->text());
  else if (newScreen == "0" && (arithm.indexOf(button->text()) != -1))
    newScreen = (activeLineEdit->text() + button->text());
  else
    newScreen = button->text();
  calcule = 0;
  activeLineEdit->setText(newScreen);
}

void MainWindow::specificButton() {
  setlocale(LC_ALL, "C");
  QPointer<QLineEdit> activeLineEdit =
      qobject_cast<QLineEdit*>(QApplication::focusWidget());
  button = (QPushButton*)sender();
  QString newScreen = activeLineEdit->text();
  if (newScreen == "ERROR" || newScreen == "0" ||
      (calcule == 1 && button->text() != "C")) {
    newScreen = "";
    calcule = 0;
  }
  if (button->text() == "C" && newScreen != "")
    newScreen.chop(1);
  else if (button->text() == "AC")
    newScreen = "0";
  else if (button->text() == "π")
    newScreen += "3.14159265";
  else if (button->text() == "π/2")
    newScreen += "1.57079632";
  else if (button->text() == "e")
    newScreen += "2.71828183";
  if (newScreen == "") newScreen = "0";
  activeLineEdit->setText(newScreen);
}

void MainWindow::qSmartCalc() {
  setlocale(LC_ALL, "C");
  int err = OK;
  char input[256] = {'\0'};
  QString newScreen = ui->screen->text() + "\n";
  long double answer = 0;
  if (newScreen.indexOf("x") != -1) {
    xButton(0, 0);
  } else {
    massForC(newScreen, input);
    err = error(input, &answer);
    if (err == OK) {
      newScreen = QString::number(answer, 'f', 7);
      if (newScreen == "0.0000000") newScreen = "0";
      ui->screen->setText(newScreen);
    } else {
      ui->screen->setText("ERROR");
    }
  }
}

void MainWindow::xButton(double X, int grath) {
  setlocale(LC_ALL, "C");
  char input[256] = {'\0'};
  int err = OK;
  QString newScreen = ui->screen->text() + "\n", answerX, newScreenX,
          x = ui->screen_x->text(), arithm = "* / ^ + -";
  if (grath) x = QString::number(X, 'f', 7);
  long double answer = 0;
  newScreenX = QString(newScreen);
  while (newScreen.indexOf("x") != -1) {
    int index_x = newScreen.indexOf("x");
    if (newScreen[index_x + 1] != 'm' && newScreen[index_x + 1] != ')' &&
        arithm.indexOf(newScreen[index_x + 1]) == -1 &&
        newScreen[index_x + 1] != '\n')
      err = ERROR;
    if (index_x != 0 && arithm.indexOf(newScreen[index_x - 1]) == -1 &&
        newScreen[index_x - 1] != 'd' && newScreen[index_x - 1] != '(')
      err = ERROR;
    newScreen = newScreen.mid(index_x + 1);
  }
  newScreen = newScreenX;
  if (err == OK) {
    if (x[0] == '-') {
      x.prepend('(');
      x.append(')');
    }
    if (newScreen.indexOf("=") != -1) newScreen = newScreen.section("=", 0, 0);
    newScreenX = newScreen;
    newScreenX.replace("x", x);
    massForC(newScreenX, input);
    err = error(input, &answer);
    if (err == OK) {
      answerX = QString::number(answer, 'f', 7);
      if (newScreen.indexOf("=") != -1) {
        if (grath == 0) ui->screen->setText(newScreen + "= " + answerX);
      } else {
        newScreen = newScreen.section("=", 0, 0);
        if (grath == 0) ui->screen->setText(newScreen + "= " + answerX);
      }
    } else {
      if (grath == 0) ui->screen->setText("ERROR");
    }
  } else {
    if (grath == 0) ui->screen->setText("ERROR");
  }
  if (grath && err == OK)
    emit giveY(answerX.toDouble());
  else if (grath && err == ERROR)
    emit giveY(NAN);
}

int MainWindow::error(char* input, long double* answer) {
  setlocale(LC_ALL, "C");
  int err = OK;
  if (strlen(input) >= 256) {
    err = ERROR;
  } else {
    err = s21_smart_calc(input, answer);
    if ((qAbs((*answer)) > MAX_VALUE || qAbs((*answer)) < MIN_VALUE) &&
        qAbs((*answer)) != 0)
      err = ERROR;
  }
  return err;
}

void MainWindow::showGrath() {
  windowGrath->show();
  windowGrath->exec();
}

void MainWindow::creditCalcule() {
  setlocale(LC_ALL, "C");
  ui->table->setRowCount(0);
  char input[256] = {'\0'};
  QString s = ui->mainSum->text().remove(" "),
          i = ui->percent->text().remove(" ") + "/1200",
          n = ui->validity->text().remove(" "), mainP, d, m, copyS = s, k;
  QDate curDate = QDate::currentDate();
  int err = 0, year = curDate.year(), month = curDate.month();
  err = findError(s, n, ui->percent->text().remove(" "));
  long double monthly = 0, mainPay = 0, numS,
              consS = s.toDouble() / n.toDouble();
  if (ui->annuitent->isChecked() && err == 0) {
    k = i + "*" + "(1+" + i + ")^" + n + "/((1+" + i + ")^" + n + "-1)";
    massForC(k + "*" + s, input);
    err = error(input, &monthly);
    if (err == 0) {
      mainP = QString::number(monthly, 'f', 2) + "*" + n;
      massForC(mainP, input);
      error(input, &mainPay);
      QString monthPer = QString::number((month + n.toInt() - 1) % 12, 'g', 2);
      QString monthI = QString::number(year + (month + n.toInt()) / 12, 'g', 4);
      createRow(0, "...-" + monthPer + ". " + monthI,
                QString::number(monthly, 'f', 2));
    }
  } else if (ui->different->isChecked() && err == 0) {
    for (int months = 1; (months <= n.toInt()) && err == 0; months++) {
      if (month == 0) month = 12;
      if (month == 1 && months > 1) year++;
      m = QString::number(months, 'g', 3);
      d = s + "/" + n + "+(" + s + "-(" + m + "-1)*(" + s + "/" + n + "))*" + i;
      massForC(d, input);
      err = error(input, &monthly);
      if (err == 0) {
        mainPay += monthly;
        numS = copyS.toDouble() - consS;
        copyS = QString::number(numS, 'f', 2);
        QString monthStr = QString::number(month, 'g', 2);
        QString yearStr = QString::number(year, 'g', 4);
        QString monthlyStr = QString::number(monthly, 'f', 2);
        createRow(months - 1, monthStr + ". " + yearStr, monthlyStr);
        month = (month + 1) % 12;
      }
    }
  }
  ui->mainPay->setText(QString::number(mainPay, 'f', 2));
  ui->overPay->setText(
      QString::number((ui->mainPay->text().toDouble() - s.toDouble()), 'f', 2));
  if (err) printError();
}

void MainWindow::massForC(QString str, char* input) {
  setlocale(LC_ALL, "C");
  QByteArray byteArray = str.toUtf8();
  strncpy(input, byteArray.constData(), 256 - 1);
}

void MainWindow::createRow(int ind, QString str1, QString str2) {
  ui->table->insertRow(ind);
  ui->table->setItem(ind, 0, new QTableWidgetItem(str1));
  ui->table->setItem(ind, 1, new QTableWidgetItem(str2));
}

void MainWindow::printError() {
  ui->mainPay->setText("ERROR");
  ui->overPay->setText("ERROR");
  createRow(0, "-", "ERROR");
}

int MainWindow::findError(QString sStr, QString nStr, QString iStr) {
  setlocale(LC_ALL, "C");
  int err = OK, n = nStr.toInt();
  long double s = sStr.toDouble(), i = iStr.toDouble();
  if ((n > 600) || (s > 99999999999999) || (i > 1000) || (i <= 0) || (n <= 0) ||
      (s <= 0)) {
    err = ERROR;
  }
  return err;
}
