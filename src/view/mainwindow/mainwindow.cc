#include "mainwindow.h"

#include <QCoreApplication>
#include <cstdlib>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, s21::Controller &controller)
    : QMainWindow(parent),
      ui_(new Ui::MainWindow),
      controller_(controller),
      open_widget_(nullptr),
      setings_widget_(new SettingsWidgetFactory(save_)),
      pos_widget_(new PositionWidgetFactory) {
  ui_->setupUi(this);
  QMovie *movie = new QMovie(":/img/blender.gif");
  ui_->label_gif->setMovie(movie);
  movie->start();
  SettingsRead();
  ui_->stackedWidget_settings->setCurrentIndex(0);
  ConnectFunc();
}

MainWindow::~MainWindow() {
  SaveSettingsOnExit();
  ui_->label_gif->movie()->deleteLater();
  delete ui_;
  delete open_widget_;
  delete setings_widget_;
  delete pos_widget_;
}

void MainWindow::ConnectFunc() {
  connect(ui_->open_file, &QPushButton::clicked, this, &MainWindow::OpenFile);
  connect(ui_->settings, &QPushButton::clicked, this,
          &MainWindow::SettingsAddWidget);
  connect(ui_->position, &QPushButton::clicked, this,
          &MainWindow::PositionAddWidget);
  connect(ui_->new_file, &QPushButton::clicked, this, &MainWindow::OpenFile);
  connect(ui_->render, &QPushButton::clicked, this, &MainWindow::PictureOn);
}

void MainWindow::OpenFile() {
  file_path_ = QFileDialog::getOpenFileName(0, "Открыть файл", "", " *.obj");
  controller_.ReadFile(file_path_.toStdString());
  if (!controller_.GetError()) {
    if (open_widget_ != nullptr) {
      delete open_widget_;
      open_widget_ = nullptr;
      DeleteWidget(setings_widget_);
      DeleteWidget(pos_widget_);
    }
    ModelInfo();
    pos_widget_->InitPosSave();
    controller_.Centralization();
    ui_->stackedWidget_settings->setCurrentIndex(1);
    open_widget_ = new glwidget(nullptr, controller_, save_);
    setings_widget_->SetGl(open_widget_);
    pos_widget_->SetGl(open_widget_);
    pos_widget_->SetController(controller_);
    open_widget_->setMaximumSize(1400, 1102);
    open_widget_->setMinimumSize(1400, 1102);
    ui_->horizontalLayout->addWidget(open_widget_);
  }
}

void MainWindow::ModelInfo() {
  ui_->info_path->setText(file_path_);
  QString StrEdges = QString("Edges: %1")
                         .arg(QString::fromStdString(
                             std::to_string(controller_.GetCountEdges())));
  ui_->info_edg->setText(StrEdges);
  QString StrVertex = QString("Vertex: %1")
                          .arg(QString::fromStdString(std::to_string(
                              controller_.GetVertices().size())));
  ui_->info_vertex->setText(StrVertex);
}

void MainWindow::PictureOn() {
  QString filePath = QFileDialog::getSaveFileName(
      this, tr("Save File"), "",
      tr("JPEG Files (*.jpeg);;BMP Files (*.bmp);;All Files (*)"));
  if (filePath.isEmpty()) {
    QMessageBox::warning(this, tr("Error"), tr("Could not save the file."));
    return;
  }
  QFile file(filePath);
  QPixmap pixmap = open_widget_->grab();
  QImage img = pixmap.toImage();
  if (!img.save(filePath))
    QMessageBox::warning(this, tr("Error"), tr("Could not save the image."));
  file.close();
}

void MainWindow::SettingsAddWidget() {
  if (setings_widget_->isEmpty())
    createAndShowWidget(setings_widget_);
  else
    DeleteWidget(setings_widget_);
}

void MainWindow::PositionAddWidget() {
  if (pos_widget_->isEmpty())
    createAndShowWidget(pos_widget_);
  else
    DeleteWidget(pos_widget_);
}

void MainWindow::createAndShowWidget(WidgetFactory *factory) {
  QWidget *widget = factory->createWidget();
  ui_->verticalLayout_3->insertWidget(4, widget);
}

void MainWindow::DeleteWidget(WidgetFactory *factory) {
  factory->DeleteWidget();
}

void MainWindow::SaveSettingsOnExit() {
  settings_save_.setValue("color_back_red", save_.color_back.red());
  settings_save_.setValue("color_back_blue", save_.color_back.blue());
  settings_save_.setValue("color_back_green", save_.color_back.green());
  settings_save_.setValue("color_edge_red", save_.color_edge.red());
  settings_save_.setValue("color_edge_blue", save_.color_edge.blue());
  settings_save_.setValue("color_edge_green", save_.color_edge.green());
  settings_save_.setValue("color_vertex_red", save_.color_vertex.red());
  settings_save_.setValue("color_vertex_blue", save_.color_vertex.blue());
  settings_save_.setValue("color_vertex_green", save_.color_vertex.green());
  settings_save_.setValue("edge_type", save_.edge_type);
  settings_save_.setValue("vertex_type", save_.vertex_type);
  settings_save_.setValue("is_on_edge", save_.is_on_edge);
  settings_save_.setValue("is_on_vertex", save_.is_on_vertex);
  settings_save_.setValue("size_edge", save_.size_edge);
  settings_save_.setValue("size_vertex", save_.size_vertex);
  settings_save_.setValue("projection_type", save_.projection_type);
}

void MainWindow::SettingsRead() {
  save_.color_back.setRed(settings_save_.value("color_back_red", 0).toInt());
  save_.color_back.setBlue(settings_save_.value("color_back_blue", 0).toInt());
  save_.color_back.setGreen(
      settings_save_.value("color_back_green", 0).toInt());

  save_.color_edge.setRed(settings_save_.value("color_edge_red", 255).toInt());
  save_.color_edge.setBlue(
      settings_save_.value("color_edge_blue", 255).toInt());
  save_.color_edge.setGreen(
      settings_save_.value("color_edge_green", 255).toInt());

  save_.color_vertex.setRed(
      settings_save_.value("color_vertex_red", 255).toInt());
  save_.color_vertex.setBlue(
      settings_save_.value("color_vertex_blue", 255).toInt());
  save_.color_vertex.setGreen(
      settings_save_.value("color_vertex_green", 255).toInt());

  save_.edge_type = settings_save_.value("edge_type", 0).toDouble();
  save_.vertex_type = settings_save_.value("vertex_type", 0).toDouble();
  save_.is_on_edge = settings_save_.value("is_on_edge", 1).toBool();
  save_.is_on_vertex = settings_save_.value("is_on_vertex", 1).toBool();
  save_.size_edge = settings_save_.value("size_edge", 1).toDouble();
  save_.size_vertex = settings_save_.value("size_vertex", 1).toDouble();
  save_.projection_type = settings_save_.value("projection_type", 0).toDouble();
}
