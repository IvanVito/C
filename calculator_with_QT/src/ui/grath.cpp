#include "grath.h"

Grath::Grath(QWidget *parent) : QDialog(parent), ui(new Ui::Grath) {
  ui->setupUi(this);
  connect(ui->buildGrath, SIGNAL(clicked()), this, SLOT(grath()));
}

Grath::~Grath() { delete ui; }

void Grath::takeY(double Y) { resultY = Y; }

void Grath::grath() {
  setlocale(LC_ALL, "C");
  long double xMin = 0, xMax = 0, yMin = 0, yMax = 0, X = 0, h = 0;
  int err = 0;
  xMin = ui->grathXMin->text().toDouble();
  xMax = ui->grathXMax->text().toDouble();
  yMin = ui->grathYMin->text().toDouble();
  yMax = ui->grathYMax->text().toDouble();
  if (qPow(10, 6) < qFabs(xMin))
    err = 1;
  else if (qPow(10, 6) < qFabs(xMax))
    err = 1;
  else if (qPow(10, 6) < qFabs(yMin))
    err = 1;
  else if (qPow(10, 6) < qFabs(yMax))
    err = 1;
  if (err == 0) {
    X = xMin;
    ui->Grathic->xAxis->setRange(xMin, xMax);
    ui->Grathic->yAxis->setRange(yMin, yMax);
    if (qFabs((xMax - xMin) > 1000))
      h = qSqrt(qFabs(xMax - xMin) / 100);
    else if (qFabs((xMax - xMin) > 1))
      h = 0.001;
    else
      h = 0.00001;
    while (X < xMax) {
      emit getY(X, 1);
      if (resultY > yMax) {
        x.push_back(X);
        y.push_back(NAN);
      } else {
        x.push_back(X);
        y.push_back(resultY);
      }
      X = X + h;
    }
    ui->Grathic->addGraph();
    ui->Grathic->graph(0)->addData(x, y);
    ui->Grathic->replot();
    ui->Grathic->clearGraphs();
    x.clear();
    y.clear();
  }
}
