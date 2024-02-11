#include <OpenGL/gl.h>

#include <QApplication>

#include "mainwindow/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Parser &parser = s21::Parser::GetInstance();
  s21::AffineTransformations afin;
  s21::Controller controller(afin, parser);
  MainWindow w(nullptr, controller);
  w.show();
  return a.exec();
}
