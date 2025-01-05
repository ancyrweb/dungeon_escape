#include "MainWindow.hpp"
#include "../shared/GameConfig.hpp"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent), process(new QProcess(this)) {
  setWindowTitle("RPG Editor");
  resize(1600, 800);

  // Initialize UI components
  createMenus();
  createToolbars();
  createDockWidgets();
  createCentralWidget();

  // Set status bar
  statusBar()->showMessage("Ready");
}

void MainWindow::createMenus() {
  QMenu *fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction("Open", this, []() {
    // Open file logic
  });
  fileMenu->addAction("Save", this, []() {
    // Save file logic
  });

  runAction = new QAction("Run", this);
  fileMenu->addAction(runAction);

  connect(runAction, &QAction::triggered, this, &MainWindow::buildAndLaunchGame);

  fileMenu->addAction("Exit", this, &QMainWindow::close);

  QMenu *editMenu = menuBar()->addMenu("&Edit");
  editMenu->addAction("Undo", this, []() {
    // Undo logic
  });
  editMenu->addAction("Redo", this, []() {
    // Redo logic
  });

  QMenu *viewMenu = menuBar()->addMenu("&View");
  viewMenu->addAction("Toggle Grid", this, []() {
    // Toggle grid logic
  });
}

void MainWindow::createToolbars() {
  QToolBar *toolbar = addToolBar("Tools");
  toolbar->addAction("Select", this, []() {
    // Select tool logic
  });
  toolbar->addAction("Paint", this, []() {
    // Paint tool logic
  });
  toolbar->addSeparator();
  toolbar->addAction("Erase", this, []() {
    // Erase tool logic
  });
}

void MainWindow::createDockWidgets() {
  auto *layersDock = new QDockWidget("Layers", this);
  layersDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  layersDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  layersDock->setMinimumWidth(300);

  addDockWidget(Qt::LeftDockWidgetArea, layersDock);

  auto *propertiesDock = new QDockWidget("Properties", this);
  propertiesDock->setAllowedAreas(Qt::RightDockWidgetArea);
  propertiesDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
  propertiesDock->setMinimumWidth(300);

  addDockWidget(Qt::RightDockWidgetArea, propertiesDock);
}

void MainWindow::createCentralWidget() {
  auto *scene = new QGraphicsScene(this);
  auto *view = new QGraphicsView(scene, this);

  QPen pen(Qt::black);
  pen.setWidth(2);

  const int TILE_SIZE = GameConfig::getTileSize();

  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 20; j++) {
      scene->addRect(
        i * TILE_SIZE,
        j * TILE_SIZE,
        TILE_SIZE,
        TILE_SIZE,
        pen,
        QBrush(Qt::white));
    }
  }

  setCentralWidget(view);
}

void MainWindow::buildAndLaunchGame() {
  qDebug() << "Building the game...";

  QString buildCommand = "cmake --build ../ --target game";

  process->start(buildCommand);
  process->waitForFinished();

  if (process->exitStatus() == QProcess::NormalExit) {
    qDebug() << "Build completed. Launching the game...";

    QString gameExecutable = "../game/game"; // Path to game binary
    if (!QProcess::startDetached(gameExecutable)) {
      qDebug() << "Failed to launch the game executable.";
    }
  } else {
    qDebug() << "Build failed:" << process->readAllStandardError();
  }
}
