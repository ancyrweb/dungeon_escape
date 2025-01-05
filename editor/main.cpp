#include <iostream>
#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QFont appFont = app.font();
  appFont.setPointSize(14);
  app.setFont(appFont);

  MainWindow window;
  window.show();

  return app.exec();
}
