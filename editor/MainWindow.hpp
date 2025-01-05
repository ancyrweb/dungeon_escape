
#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QProcess>
#include <QDir>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget* parent = nullptr);

private slots:
  void buildAndLaunchGame(); // Slot to handle the button's action

private:
  QAction* runAction;
  QProcess* process; // To execute external commands

  void createMenus();
  void createToolbars();
  void createDockWidgets();
  void createCentralWidget();
};

#endif //MAINWINDOW_HPP
