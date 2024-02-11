#ifndef SRC_VIEW_MAINWINDOW_MAINWINDOW_H_
#define SRC_VIEW_MAINWINDOW_MAINWINDOW_H_

#include <QDateTime>
#include <QFileDialog>
#include <QImageWriter>
#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>
#include <QSettings>

#include "../widget/widgetfactory/positionfactory.h"
#include "../widget/widgetfactory/settingsfactory.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent, s21::Controller &controller);
  ~MainWindow();

 private:
  Ui::MainWindow *ui_;
  s21::Controller &controller_;
  glwidget *open_widget_;
  SettingsWidgetFactory *setings_widget_;
  PositionWidgetFactory *pos_widget_;
  SaveSettings save_;
  QString file_path_;
  QSettings settings_save_;
  void SettingsRead();
  void SaveSettingsOnExit();

 private slots:
  void OpenFile();
  void createAndShowWidget(WidgetFactory *factory);
  void DeleteWidget(WidgetFactory *factory);
  void SettingsAddWidget();
  void PositionAddWidget();
  void PictureOn();
  void ConnectFunc();
  void ModelInfo();
};
#endif  // SRC_VIEW_MAINWINDOW_MAINWINDOW_H_
