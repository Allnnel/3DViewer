#ifndef SRC_VIEW_WIDGET_SETTINGSWIDGET_H_
#define SRC_VIEW_WIDGET_SETTINGSWIDGET_H_

#include <QColorDialog>
#include <QWidget>

#include "../../back/rendering/opengl.h"
#include "../struct/nodesave.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget {
  Q_OBJECT

 public:
  explicit SettingsWidget(QWidget* parent, SaveSettings& save, glwidget& gl);
  ~SettingsWidget();

 private:
  SaveSettings& save_;
  glwidget& gl_;
  Ui::SettingsWidget* ui_;
  void ConnectButton();
  void CheckEdge();
  void CheckVertex();
  void CheckTypeEdge();
  void CheckTypeVertex();
  void CheckTypeProjection();
  void CheckSizeEdge();
  void CheckSizeVertex();
  void CheckColorVertex();
  void CheckColorEdge();
  void CheckColorBack();
  void SaveSetting();
};

#endif  // SRC_VIEW_WIDGET_SETTINGSWIDGET_H_
